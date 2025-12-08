#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <std_msgs/msg/string.hpp>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>

#include <memory>
#include <string>
#include <vector> 

class QrDetector : public rclcpp::Node
{
public:
    QrDetector() : Node("qr_detector_node")
    {
        subscription_ = image_transport::create_subscription(this, "image_raw", 
            std::bind(&QrDetector::image_callback, this, std::placeholders::_1), 
            "raw");

        qr_data_publisher_ = this->create_publisher<std_msgs::msg::String>("/qr_data", 10);
        debug_image_publisher_ = image_transport::create_publisher(this, "/qr_debug_image");
        qr_detector_ = cv::QRCodeDetector();

        RCLCPP_INFO(this->get_logger(), "QR tespit düğümü başlatıldı, '/image_raw' topic'i dinleniyor.");
    }

private:
    void image_callback(const sensor_msgs::msg::Image::ConstSharedPtr & msg)
    {
        try {
            cv::Mat frame = cv_bridge::toCvShare(msg, "bgr8")->image;
            
            std::vector<cv::Point> points;
            std::string qr_data = "";

            bool found = qr_detector_.detect(frame,points);

            if (found && !points.empty()) {
                qr_data = qr_detector_.decode(frame,points);
            }
            

            if (!qr_data.empty()) {

                RCLCPP_INFO(this->get_logger(), "QR Kodu Tespit Edildi! Veri: '%s'", qr_data.c_str());

                std_msgs::msg::String qr_msg;
                qr_msg.data = qr_data;
                qr_data_publisher_->publish(qr_msg);

                if (!points.empty()) { 
                    for(size_t i = 0; i < points.size(); ++i) {
                        cv::line(frame, points[i], points[(i + 1) % points.size()], cv::Scalar(0, 255, 0), 3);
                    }
                }
            }

            auto debug_msg = cv_bridge::CvImage(std_msgs::msg::Header(), "bgr8", frame).toImageMsg();
            debug_image_publisher_.publish(std::move(debug_msg));

        } catch (const cv_bridge::Exception& e) {
            RCLCPP_ERROR(this->get_logger(), "cv_bridge exception: %s", e.what());
        }
    }

    image_transport::Subscriber subscription_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr qr_data_publisher_;
    image_transport::Publisher debug_image_publisher_;
    cv::QRCodeDetector qr_detector_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<QrDetector>());
    rclcpp::shutdown();
    return 0;
}