#ifndef TARGET_DETECTION_NODE_HPP
#define TARGET_DETECTION_NODE_HPP

#include "std_msgs/msg/string.hpp"
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.hpp>
#include <opencv2/opencv.hpp>
// ONNX Runtime C++ API
#include <onnxruntime_cxx_api.h>

#include <vector>
#include <string>
#include <memory>
#include <algorithm>

// Tespit edilen nesne yapısı
struct Detection {
    int class_id;
    float confidence;
    cv::Rect box;
};

class YoloNode : public rclcpp::Node {
public:
    explicit YoloNode();
    ~YoloNode() = default;

private:

    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr image_sub_;
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr image_pub_;


    std::string model_path_;
    double conf_threshold_;
    double nms_threshold_;
    

    Ort::Env ort_env_;
    std::unique_ptr<Ort::Session> ort_session_;
    

    std::vector<const char*> input_node_names_;
    std::vector<const char*> output_node_names_;
    

    std::vector<int64_t> input_node_dims_;
    std::vector<int64_t> output_node_dims_;
    

    std::vector<std::string> input_names_str_;
    std::vector<std::string> output_names_str_;

   
    void initialize_onnx();
    void image_callback(const sensor_msgs::msg::Image::SharedPtr msg);
    
    cv::Mat preprocess(const cv::Mat& img, float& scale_factor, cv::Point2f& shift);
    std::vector<Detection> postprocess(const float* output_data, 
                                     const std::vector<int64_t>& shape,
                                     float scale_factor,
                                     const cv::Point2f& shift);
    bool is_active_; // Modun aktif olup olmad???n? tutar
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr state_subscription_; // Modu dinleyen subscriber
    void state_callback(const std_msgs::msg::String::SharedPtr msg); // Callback fonksiyonu
};

#endif // TARGET_DETECTION_NODE_HPP
