#ifndef QR_DETECTION_NODE_HPP
#define QR_DETECTION_NODE_HPP

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <std_msgs/msg/string.hpp>
#include <image_transport/image_transport.hpp>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include <opencv2/cudaimgproc.hpp>
#include <opencv2/cudawarping.hpp>
#include <opencv2/objdetect.hpp>
#include <memory>
#include <string>

class QRDetectionNode : public rclcpp::Node
{
public:
    QRDetectionNode();
    ~QRDetectionNode();
    void initialize();

private:
    // Callbacks
    void state_callback(const std_msgs::msg::String::SharedPtr msg);
    void image_callback(const sensor_msgs::msg::Image::ConstSharedPtr &msg);
    
    // QR Detection functions
    bool detect_qr_code(const cv::Mat &input_image, cv::Mat &output_image, std::string &decoded_text);
    void process_image_gpu(const cv::Mat &cpu_image, cv::Mat &processed_image);
    
    // ROS 2 members
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr state_subscription_;
    
    // --- DE????KL?K BURADA YAPILDI ---
    // Eski: image_transport::Subscriber image_subscriber_;
    // Yeni: Standart abonelik (Best Effort QoS desteklemesi i?in)
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr image_subscriber_;

    image_transport::Publisher debug_image_publisher_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr qr_data_publisher_;
    
    // Image transport
    std::shared_ptr<image_transport::ImageTransport> image_transport_;
    
    // State
    bool is_active_;
    bool cuda_available_;
    
    // OpenCV QR Detector
    cv::QRCodeDetector qr_detector_;
    
    // GPU memory for processing
    cv::cuda::GpuMat gpu_input_;
    cv::cuda::GpuMat gpu_processed_;
    cv::cuda::GpuMat gpu_gray_;
};

#endif // QR_DETECTION_NODE_HPP
