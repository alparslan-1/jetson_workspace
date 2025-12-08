#include "target_detection_node.hpp"
#include <iostream>

using std::placeholders::_1;

YoloNode::YoloNode() 
    : Node("atmaca_vision_node"), 
      ort_env_(ORT_LOGGING_LEVEL_WARNING, "YoloV8_Atmaca") {

    this->declare_parameter("model_path", "/root/bridges/jetson_workspace/best.onnx");
    this->declare_parameter("conf_threshold", 0.5);
    this->declare_parameter("nms_threshold", 0.45);

    model_path_ = this->get_parameter("model_path").as_string();
    conf_threshold_ = this->get_parameter("conf_threshold").as_double();
    nms_threshold_ = this->get_parameter("nms_threshold").as_double();

    RCLCPP_INFO(this->get_logger(), "Model Yolu: %s", model_path_.c_str());

    try {
        initialize_onnx();
        RCLCPP_INFO(this->get_logger(), "ONNX Model Başarıyla Yüklendi!");
    } catch (const std::exception& e) {
        RCLCPP_FATAL(this->get_logger(), "ONNX Hatası: %s", e.what());
    }

    image_sub_ = this->create_subscription<sensor_msgs::msg::Image>(
        "/image_raw", rclcpp::SensorDataQoS(), 
        std::bind(&YoloNode::image_callback, this, _1));

    image_pub_ = this->create_publisher<sensor_msgs::msg::Image>(
        "/yolo/detections", 10);
}

void YoloNode::initialize_onnx() {
    Ort::SessionOptions session_options;
    //session_options.SetIntraOpNumThreads(1); 
    session_options.SetGraphOptimizationLevel(GraphOptimizationLevel::ORT_ENABLE_ALL);

    ort_session_ = std::make_unique<Ort::Session>(ort_env_, model_path_.c_str(), session_options);
    Ort::AllocatorWithDefaultOptions allocator;

    size_t num_input_nodes = ort_session_->GetInputCount();
    for(size_t i = 0; i < num_input_nodes; i++) {
        auto input_name = ort_session_->GetInputNameAllocated(i, allocator);
        input_names_str_.push_back(input_name.get());
        input_node_names_.push_back(input_names_str_.back().c_str());
        
        Ort::TypeInfo type_info = ort_session_->GetInputTypeInfo(i);
        auto tensor_info = type_info.GetTensorTypeAndShapeInfo();
        input_node_dims_ = tensor_info.GetShape();
        
        if (input_node_dims_.size() > 0 && input_node_dims_[0] == -1) {
            input_node_dims_[0] = 1;
        }
    }

    size_t num_output_nodes = ort_session_->GetOutputCount();
    for(size_t i = 0; i < num_output_nodes; i++) {
        auto output_name = ort_session_->GetOutputNameAllocated(i, allocator);
        output_names_str_.push_back(output_name.get());
        output_node_names_.push_back(output_names_str_.back().c_str());

        Ort::TypeInfo type_info = ort_session_->GetOutputTypeInfo(i);
        auto tensor_info = type_info.GetTensorTypeAndShapeInfo();
        output_node_dims_ = tensor_info.GetShape();
    }
}

cv::Mat YoloNode::preprocess(const cv::Mat& img, float& scale_factor, cv::Point2f& shift) {
    int target_w = 640;
    int target_h = 640;
    
    float scale_x = (float)target_w / img.cols;
    float scale_y = (float)target_h / img.rows;
    scale_factor = std::min(scale_x, scale_y);
    
    int new_w = std::round(img.cols * scale_factor);
    int new_h = std::round(img.rows * scale_factor);
    
    cv::Mat resized_img;
    cv::resize(img, resized_img, cv::Size(new_w, new_h));
    
    int pad_w = target_w - new_w;
    int pad_h = target_h - new_h;
    
    int top = pad_h / 2;
    int bottom = pad_h - top;
    int left = pad_w / 2;
    int right = pad_w - left;
    
    shift.x = left;
    shift.y = top;
    
    cv::Mat padded_img;
    cv::copyMakeBorder(resized_img, padded_img, top, bottom, left, right, 
                       cv::BORDER_CONSTANT, cv::Scalar(114, 114, 114));
    return padded_img;
}

void YoloNode::image_callback(const sensor_msgs::msg::Image::SharedPtr msg) {
    cv_bridge::CvImagePtr cv_ptr;
    try {
        cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    } catch (cv_bridge::Exception& e) {
        RCLCPP_ERROR(this->get_logger(), "cv_bridge hatası: %s", e.what());
        return;
    }

    float scale_factor;
    cv::Point2f shift;
    cv::Mat processed_img = preprocess(cv_ptr->image, scale_factor, shift);
    
    cv::Mat blob;
    if (!blob.empty()) {
    // Blob'un merkezindeki piksel değerine erişelim
    // Blob shape:  varsayalım
    int c = 0; // 0. kanal (R veya B)
    int h = 320; // Yüksekliğin yarısı
    int w = 320; // Genişliğin yarısı
    
    // OpenCV Mat erişimi (N, C, H, W)
    // 4 boyutlu olduğu için ptr() kullanımı biraz karmaşık olabilir, 
    // ancak düzleştirilmiş indis ile erişebiliriz veya basitçe at<float> deneriz.
    // Güvenli erişim için:
    const float* blobPtr = blob.ptr<float>();
    int index = (0 * 3 * 640 * 640) + (0 * 640 * 640) + (320 * 640) + 320; 
    float sampleValue = blobPtr[index];
    
    std::cout << "\n --- GIRIS VERISI ANALIZI ---" << std::endl;
    std::cout << " Blob Boyutu: " << blob.size << std::endl;
    std::cout << " Ornek Piksel Degeri (Normalize): " << sampleValue << std::endl;
    
    if (sampleValue > 1.0f) {
        std::cerr << " Giris verisi normalize edilmemis! Deger > 1.0. (Beklenen: 0.0 - 1.0 arasi)" << std::endl;
        std::cerr << "[COZUM] cv::dnn::blobFromImage fonksiyonunda scalefactor parametresini 1/255.0 olarak ayarlayin." << std::endl;
    } else {
        std::cout << "[OK] Normalizasyon makul gorunuyor (Deger <= 1.0)." << std::endl;
    }
    }
    cv::dnn::blobFromImage(processed_img, blob, 1.0/255.0, cv::Size(), cv::Scalar(), true, false);
    
    size_t input_tensor_size = 1 * 3 * 640 * 640;
    Ort::MemoryInfo memory_info = Ort::MemoryInfo::CreateCpu(OrtArenaAllocator, OrtMemTypeDefault);
    
    Ort::Value input_tensor = Ort::Value::CreateTensor<float>(
        memory_info, blob.ptr<float>(), input_tensor_size, 
        input_node_dims_.data(), input_node_dims_.size());

    auto output_tensors = ort_session_->Run(
        Ort::RunOptions{nullptr}, 
        input_node_names_.data(), &input_tensor, 1, 
        output_node_names_.data(), 1);
    
    float* raw_output = output_tensors.front().GetTensorMutableData<float>();
    
    auto output_shape = output_tensors.front().GetTensorTypeAndShapeInfo().GetShape();

    std::vector<Detection> detections = postprocess(
        raw_output, output_shape, scale_factor, shift);
    

    for (const auto& det : detections) {
        cv::rectangle(cv_ptr->image, det.box, cv::Scalar(0, 255, 0), 2);
        std::string label = "Ucak " + std::to_string(det.confidence).substr(0, 4);
        cv::putText(cv_ptr->image, label, cv::Point(det.box.x, det.box.y - 5),
                   cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 255, 0), 2);
    }

    image_pub_->publish(*cv_ptr->toImageMsg());
}

std::vector<Detection> YoloNode::postprocess(const float* output, 
                                           const std::vector<int64_t>& shape,
                                           float scale_factor,
                                           const cv::Point2f& shift) {
    
    // Güvenlik kontrolü: Şekil bilgisi boşsa işlem yapma
    if (shape.size() < 3) return {};

    int num_channels = shape[1]; // Genellikle 5 (x,y,w,h,score)
    int num_anchors = shape[2];  // 8400

    std::vector<cv::Rect> boxes;
    std::vector<float> confidences;
    std::vector<int> class_ids;

    // DEBUG DEĞİŞKENLERİ (Sorunu bulmamızı sağlayacak kısım)
    float max_score_found = 0.0f;
    int max_score_index = -1;

    for (int i = 0; i < num_anchors; ++i) {
        // 4. indeks (5. eleman) skor değeridir
        float score = output[4 * num_anchors + i];
        
        // En yüksek skoru kaydet (Analiz için)
        if (score > max_score_found) {
            max_score_found = score;
            max_score_index = i;
        }

        if (score > conf_threshold_) {
            float cx = output[0 * num_anchors + i];
            float cy = output[1 * num_anchors + i];
            float w = output[2 * num_anchors + i];
            float h = output[3 * num_anchors + i];
            
            float x = (cx - (w / 2.0f) - shift.x) / scale_factor;
            float y = (cy - (h / 2.0f) - shift.y) / scale_factor;
            float width = w / scale_factor;
            float height = h / scale_factor;
            
            boxes.emplace_back(std::round(x), std::round(y), std::round(width), std::round(height));
            confidences.push_back(score);
            class_ids.push_back(0); 
        }
    }

    // --- KRİTİK DEBUG ÇIKTISI ---
    // Her 30 karede bir (yaklaşık saniyede 1) durumu rapor et
    static int log_counter = 0;
    if (log_counter++ % 30 == 0) {
        if (max_score_found < 0.01) {
            RCLCPP_WARN(this->get_logger(), "UYARI: Model hicbir sey gormuyor! Max Skor: %.5f (Cok Dusuk)", max_score_found);
            RCLCPP_WARN(this->get_logger(), "Olası Sebepler: 1) Resim cok karanlik/aydinlik 2) RGB/BGR hatasi 3) Normalizasyon hatasi");
        } else if (max_score_found < conf_threshold_) {
            RCLCPP_INFO(this->get_logger(), "Tespit Var ama Esigin Altinda. Max Skor: %.2f (Esik: %.2f)", max_score_found, conf_threshold_);
        } else {
            RCLCPP_INFO(this->get_logger(), "BASARILI: Tespit Yapildi! Max Skor: %.2f", max_score_found);
        }
    }
    // ----------------------------
    
    std::vector<int> indices;
    cv::dnn::NMSBoxes(boxes, confidences, conf_threshold_, nms_threshold_, indices);
    
    std::vector<Detection> final_detections;
    for (int idx : indices) {
        Detection det;
        det.box = boxes[idx];
        det.confidence = confidences[idx];
        det.class_id = class_ids[idx];
        final_detections.push_back(det);
    }
    
    return final_detections;
}

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<YoloNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
