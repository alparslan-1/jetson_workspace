#include "target_detection_node.hpp"
#include <iostream>
#include "std_msgs/msg/string.hpp" // EKLENDI: Mod mesajini okumak icin gerekli

using std::placeholders::_1;

YoloNode::YoloNode() 
    : Node("atmaca_vision_node"), 
      is_active_(false), // EKLENDI: Varsayilan olarak sistem PASIF baslar
      ort_env_(ORT_LOGGING_LEVEL_WARNING, "YoloV8_Atmaca") {

    // --- PARAMETRELER ---
    this->declare_parameter("model_path", "/root/bridges/jetson_workspace/best.onnx");
    this->declare_parameter("conf_threshold", 0.5);
    this->declare_parameter("nms_threshold", 0.45);

    model_path_ = this->get_parameter("model_path").as_string();
    conf_threshold_ = this->get_parameter("conf_threshold").as_double();
    nms_threshold_ = this->get_parameter("nms_threshold").as_double();

    RCLCPP_INFO(this->get_logger(), "Model Yolu: %s", model_path_.c_str());

    // --- ONNX BASLATMA ---
    try {
        initialize_onnx();
        RCLCPP_INFO(this->get_logger(), "ONNX Model Basariyla Yuklendi!");
    } catch (const std::exception& e) {
        RCLCPP_FATAL(this->get_logger(), "ONNX Hatasi: %s", e.what());
    }

    // --- EKLENDI: MODE SUBSCRIPTION (KAMIKAZE KONTROLU) ---
    // Mission Control node'u "transient_local" (kalici) yayin yaptigi icin
    // biz de ayni ayarlarla dinlemeliyiz. Aksi takdirde gecmis mesaji alamayiz.
    rclcpp::QoS qos_profile(1);
    qos_profile.reliable();
    qos_profile.transient_local(); 
    qos_profile.keep_last(1);

    state_subscription_ = this->create_subscription<std_msgs::msg::String>(
        "/success/lockon_success", 
        qos_profile, 
        std::bind(&YoloNode::state_callback, this, _1)
    );
    
    RCLCPP_INFO(this->get_logger(), "Mode dinleyici baslatildi. '/success/lockon_success' bekleniyor...");
    // ---------------------------------------------------------

    // --- GORUNTU SUBSCRIPTION ---
    image_sub_ = this->create_subscription<sensor_msgs::msg::Image>(
        "/image_raw", rclcpp::SensorDataQoS(), 
        std::bind(&YoloNode::image_callback, this, _1));

    // --- YOLO PUBLISHER ---
    image_pub_ = this->create_publisher<sensor_msgs::msg::Image>(
        "/yolo/detections", 10);
}

// --- EKLENDI: STATE CALLBACK ---
void YoloNode::state_callback(const std_msgs::msg::String::SharedPtr msg)
{
    std::string current_mode = msg->data;
    
    // Gelen modu terminalde gorelim (Opsiyonel, cok spam yaparsa silebilirsiniz)
    // RCLCPP_INFO(this->get_logger(), "Mode data received: '%s'", current_mode.c_str());

    // Hem BUYUK hem kucuk harf kontrolu (Garanti olmasi icin)
    if (current_mode == "KILITLENME") 
    {
        if (!is_active_) {
            is_active_ = true;
            RCLCPP_WARN(this->get_logger(), ">>> YOLO AKTIFLESTIRILDI (Mod: %s) <<<", current_mode.c_str());
        }
    } 
    else 
    {
        if (is_active_) {
            is_active_ = false;
            RCLCPP_INFO(this->get_logger(), ">>> YOLO DURDURULDU (Mod: %s) <<<", current_mode.c_str());
        }
    }
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
    // --- EKLENDI: GUVENLIK KONTROLU ---
    // Eger mod KAMIKAZE degilse, CPU/GPU yormamak icin islem yapmadan geri don.
    if (!is_active_) {
        return; 
    }
    // ----------------------------------

    cv_bridge::CvImagePtr cv_ptr;
    try {
        cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    } catch (cv_bridge::Exception& e) {
        RCLCPP_ERROR(this->get_logger(), "cv_bridge hatasi: %s", e.what());
        return;
    }

    float scale_factor;
    cv::Point2f shift;
    cv::Mat processed_img = preprocess(cv_ptr->image, scale_factor, shift);
    
    cv::Mat blob;
    // Not: blobFromImage, pikselleri 0-1 arasina normalize eder (1/255.0)
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
    
    if (shape.size() < 3) return {};

    int num_channels = shape[1]; 
    int num_anchors = shape[2];  

    std::vector<cv::Rect> boxes;
    std::vector<float> confidences;
    std::vector<int> class_ids;

    float max_score_found = 0.0f;
    int max_score_index = -1;

    for (int i = 0; i < num_anchors; ++i) {
        float score = output[4 * num_anchors + i];
        
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

    // --- DEBUG LOGLARI ---
    static int log_counter = 0;
    if (log_counter++ % 30 == 0) { // Saniyede yaklasik 1 kere bas
        if (max_score_found < 0.01) {
             RCLCPP_WARN(this->get_logger(), "UYARI: Model hicbir sey gormuyor! Max Skor: %.5f", max_score_found);
        } else if (max_score_found < conf_threshold_) {
            RCLCPP_INFO(this->get_logger(), "Tespit Var ama Esigin Altinda. Max: %.2f", max_score_found);
        } else {
            RCLCPP_INFO(this->get_logger(), "BASARILI: Tespit Yapildi! Max: %.2f", max_score_found);
        }
    }
    // --------------------
    
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
