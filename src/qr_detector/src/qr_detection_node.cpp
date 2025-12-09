#include "qr_detector/qr_detection_node.hpp"
#include <memory>
#include <chrono>

QRDetectionNode::QRDetectionNode()
    : Node("qr_detection_node"), is_active_(false)
{
    // --- CONSTRUCTOR (YAPICI FONKS?YON) ---
    
    // Check CUDA availability
    cuda_available_ = (cv::cuda::getCudaEnabledDeviceCount() > 0);
    
    if (cuda_available_) {
        RCLCPP_INFO(this->get_logger(), "CUDA is available. GPU acceleration enabled.");
        RCLCPP_INFO(this->get_logger(), "CUDA Device Count: %d", cv::cuda::getCudaEnabledDeviceCount());
    } else {
        RCLCPP_WARN(this->get_logger(), "CUDA is not available. Falling back to CPU processing.");
    }
    
    // Normal Publisher'lar
    qr_data_publisher_ = this->create_publisher<std_msgs::msg::String>(
        "/vision/qr_data",
        10
    );
    
    RCLCPP_INFO(this->get_logger(), "Node created. Waiting for initialization...");
}

// --- INITIALIZE (BA?LATMA FONKS?YONU) ---
void QRDetectionNode::initialize()
{
    // Image transport'u ba?lat (Debug yay?nc?s? i?in hala laz?m)
    image_transport_ = std::make_shared<image_transport::ImageTransport>(shared_from_this());
    
    // --- QoS AYARLARI (Kritik B?l?m) ---
    
    // 1. Mission Control i?in QoS (Reliable + Transient Local)
    rclcpp::QoS state_qos_profile(1);
    state_qos_profile.reliable();
    state_qos_profile.transient_local(); 
    state_qos_profile.keep_last(1);

    // 2. KAMERA ABONEL??? ???N BEST EFFORT QoS (YEN? EKLEND?)
    // Bu ayar "SensorDataQoS" olarak ge?er ve Best Effort yay?n yapan kameralar? dinleyebilir.
    rclcpp::QoS camera_qos_profile = rclcpp::SensorDataQoS();

    // --- SUBSCRIPTION ---
    
    // Mission Control Subscription
    state_subscription_ = this->create_subscription<std_msgs::msg::String>(
        "/success/lockon_success", 
        state_qos_profile, 
        std::bind(&QRDetectionNode::state_callback, this, std::placeholders::_1)
    );
    
    // --- DE????KL?K BURADA: Image Subscriber (Kamera verisi) ---
    // image_transport yerine create_subscription kullan?yoruz ki QoS ayar?n? (Best Effort) verebilelim.
    image_subscriber_ = this->create_subscription<sensor_msgs::msg::Image>(
        "/image_raw",
        camera_qos_profile, // Best Effort ayar? burada veriliyor
        std::bind(&QRDetectionNode::image_callback, this, std::placeholders::_1)
    );
    
    // Image Publisher (Debug g?r?nt?s? - Bu Reliable kalabilir, sorun yok)
    debug_image_publisher_ = image_transport_->advertise("/vision/qr_debug_image", 1);
    
    RCLCPP_INFO(this->get_logger(), "QR Detection Node initialized (Camera Sub: BEST EFFORT).");
    RCLCPP_INFO(this->get_logger(), "Waiting for 'KAMIKAZE' mode on '/success/lockon_success' topic...");
}

QRDetectionNode::~QRDetectionNode()
{
    RCLCPP_INFO(this->get_logger(), "QR Detection Node shutting down");
}

void QRDetectionNode::state_callback(const std_msgs::msg::String::SharedPtr msg)
{
    std::string current_mode = msg->data;

    RCLCPP_INFO(this->get_logger(), "Mode data received: '%s'", current_mode.c_str());

    if (current_mode == "KAMIKAZE" || current_mode == "kamikaze") 
    {
        if (!is_active_) {
            is_active_ = true;
            RCLCPP_INFO(this->get_logger(), ">>> QR DETECTION ACTIVATED (Mode: %s) <<<", current_mode.c_str());
        }
    } 
    else 
    {
        if (is_active_) {
            is_active_ = false;
            RCLCPP_INFO(this->get_logger(), ">>> QR DETECTION STOPPED (Mode: %s) <<<", current_mode.c_str());
        }
    }
}

void QRDetectionNode::image_callback(const sensor_msgs::msg::Image::ConstSharedPtr &msg) // ConstSharedPtr olarak kalabilir
{
    if (!is_active_) {
        return; 
    }
    
    try {
        cv_bridge::CvImagePtr cv_ptr;
        cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
        
        cv::Mat input_image = cv_ptr->image;
        cv::Mat output_image = input_image.clone();
        std::string decoded_text;
        
        // Detect QR code
        bool qr_detected = detect_qr_code(input_image, output_image, decoded_text);
        
        // Publish debug image
        sensor_msgs::msg::Image::SharedPtr debug_msg = cv_bridge::CvImage(
            msg->header,
            sensor_msgs::image_encodings::BGR8,
            output_image
        ).toImageMsg();
        
        debug_image_publisher_.publish(debug_msg);
        
        // Publish QR data if detected
        if (qr_detected && !decoded_text.empty()) {
            auto qr_msg = std_msgs::msg::String();
            qr_msg.data = decoded_text;
            qr_data_publisher_->publish(qr_msg);
            RCLCPP_DEBUG(this->get_logger(), "QR Code detected: %s", decoded_text.c_str());
        }
        
    } catch (cv_bridge::Exception& e) {
        RCLCPP_ERROR(this->get_logger(), "cv_bridge exception: %s", e.what());
    } catch (const std::exception& e) {
        RCLCPP_ERROR(this->get_logger(), "Exception in image callback: %s", e.what());
    }
}

bool QRDetectionNode::detect_qr_code(const cv::Mat &input_image, cv::Mat &output_image, std::string &decoded_text)
{
    try {
        cv::Mat processed_image;
        
        if (cuda_available_) {
            process_image_gpu(input_image, processed_image);
        } else {
            cv::cvtColor(input_image, processed_image, cv::COLOR_BGR2GRAY);
        }
        
        std::vector<cv::Point2f> points;
        bool detected = qr_detector_.detect(processed_image, points);
        
        if (detected && points.size() >= 4) {
            decoded_text = qr_detector_.decode(processed_image, points);
            
            if (!decoded_text.empty()) {
                cv::Point2f pt1 = points[0];
                cv::Point2f pt2 = points[1];
                cv::Point2f pt3 = points[2];
                cv::Point2f pt4 = points[3];
                
                cv::line(output_image, pt1, pt2, cv::Scalar(0, 255, 0), 3);
                cv::line(output_image, pt2, pt3, cv::Scalar(0, 255, 0), 3);
                cv::line(output_image, pt3, pt4, cv::Scalar(0, 255, 0), 3);
                cv::line(output_image, pt4, pt1, cv::Scalar(0, 255, 0), 3);
                
                cv::circle(output_image, pt1, 5, cv::Scalar(0, 0, 255), -1);
                cv::circle(output_image, pt2, 5, cv::Scalar(0, 0, 255), -1);
                cv::circle(output_image, pt3, 5, cv::Scalar(0, 0, 255), -1);
                cv::circle(output_image, pt4, 5, cv::Scalar(0, 0, 255), -1);
                
                cv::putText(output_image, 
                           "QR: " + decoded_text, 
                           cv::Point(static_cast<int>(pt1.x), static_cast<int>(pt1.y) - 10),
                           cv::FONT_HERSHEY_SIMPLEX, 
                           0.6, 
                           cv::Scalar(0, 255, 0), 
                           2);
                
                return true;
            }
        }
        
        return false;
        
    } catch (const cv::Exception& e) {
        RCLCPP_ERROR(this->get_logger(), "OpenCV exception in QR detection: %s", e.what());
        return false;
    } catch (const std::exception& e) {
        RCLCPP_ERROR(this->get_logger(), "Exception in QR detection: %s", e.what());
        return false;
    }
}

void QRDetectionNode::process_image_gpu(const cv::Mat &cpu_image, cv::Mat &processed_image)
{
    try {
        gpu_input_.upload(cpu_image);
        cv::cuda::cvtColor(gpu_input_, gpu_gray_, cv::COLOR_BGR2GRAY);
        gpu_gray_.download(processed_image);
        
    } catch (const cv::Exception& e) {
        RCLCPP_WARN(this->get_logger(), "GPU processing failed, falling back to CPU: %s", e.what());
        cv::cvtColor(cpu_image, processed_image, cv::COLOR_BGR2GRAY);
    }
}

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<QRDetectionNode>();
    node->initialize();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
