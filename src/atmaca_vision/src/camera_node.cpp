#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <cv_bridge/cv_bridge.h> 
#include <image_transport/image_transport.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <chrono>
#include <string>
#include <memory>
#include <stdexcept>

std::string gstreamer_pipeline (int width, int height, int framerate) {

    return "v4l2src device=/dev/video0 ! image/jpeg,width=" + std::to_string(width) + ",height=" + std::to_string(height) + ",framerate=" + std::to_string(framerate) + "/1 ! jpegdec ! videoconvert ! queue ! appsink max-buffers=1 drop=true sync=false";
}

class CameraPublisher : public rclcpp::Node
{
public:
    CameraPublisher(): Node("camera_publisher_node")
    {
        int width = 1280;
        int height = 720;
        int framerate = 30;

        std::string pipeline = gstreamer_pipeline(width, height, framerate);
        RCLCPP_INFO(this->get_logger(), "Kullanılan GStreamer Pipeline: %s", pipeline.c_str());

        cap_.open(pipeline, cv::CAP_GSTREAMER);
        if(!cap_.isOpened()) {
            RCLCPP_ERROR(this->get_logger(), "Kamera açılamadı! GStreamer pipeline'ı başlatılamadı.");
            throw std::runtime_error("Kamera açılamadı!");
        }
        
        publisher_ = image_transport::create_publisher(this, "image_raw");
        
        auto timer_period = std::chrono::milliseconds(1000 / framerate);
        timer_ = this->create_wall_timer(timer_period, std::bind(&CameraPublisher::timer_callback, this));

        RCLCPP_INFO(this->get_logger(), "Kamera yayın düğümü başlatıldı, '/image_raw' topic'inde yayın yapılıyor.");
    }

private:
    void timer_callback()
    {
        cv::Mat frame;
        if (cap_.read(frame)) {
            if (!frame.empty()) {
                auto msg = cv_bridge::CvImage(std_msgs::msg::Header(), "bgr8", frame).toImageMsg();
                publisher_.publish(std::move(msg));
            } else {
                RCLCPP_WARN(this->get_logger(), "Kameradan boş görüntü çerçevesi okundu.");
            }
        } else {
            RCLCPP_WARN(this->get_logger(), "Kameradan çerçeve okunamadı.");
        }
    }

    rclcpp::TimerBase::SharedPtr timer_;
    cv::VideoCapture cap_;
    image_transport::Publisher publisher_;
};

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    try {
        rclcpp::spin(std::make_shared<CameraPublisher>());
    } catch (const std::runtime_error & e) {
        RCLCPP_FATAL(rclcpp::get_logger("camera_publisher_main"), "Düğüm başlatılamadı: %s", e.what());
    }
    rclcpp::shutdown();
    return 0;
}