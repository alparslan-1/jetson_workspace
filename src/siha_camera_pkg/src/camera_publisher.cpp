#include <rclcpp/rclcpp.hpp>
#include <image_transport/image_transport.hpp>
#include <opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/msg/image.hpp>
#include <std_msgs/msg/string.hpp> 
#include <px4_msgs/msg/sensor_combined.hpp> 
#include <algorithm> 

using namespace std::chrono_literals;

class CameraPublisher : public rclcpp::Node
{
public:
    CameraPublisher()
        : Node("camera_publisher")
    {
        // --- PARAMETRELER ---
        this->declare_parameter("video_device", "/dev/video0");
        this->declare_parameter("frame_width", 640);
        this->declare_parameter("frame_height", 480);
        this->declare_parameter("frame_rate", 30.0);
        this->declare_parameter("frame_id", "camera_link");

        device_path_ = this->get_parameter("video_device").as_string();
        width_ = this->get_parameter("frame_width").as_int();
        height_ = this->get_parameter("frame_height").as_int();
        fps_ = this->get_parameter("frame_rate").as_double();
        frame_id_ = this->get_parameter("frame_id").as_string();

        // --- QoS AYARLARI ---
        rclcpp::QoS px4_qos = rclcpp::SensorDataQoS(); 
        rmw_qos_profile_t camera_qos = rmw_qos_profile_sensor_data;

        // --- STATE QoS AYARLARI (Referans koddaki gibi g?ncellendi) ---
        // Mission Control (Durum) i?in Reliable + Transient Local ayar?
        rclcpp::QoS state_qos_profile(1);
        state_qos_profile.reliable();
        state_qos_profile.transient_local(); 
        state_qos_profile.keep_last(1);

        // --- PUBLISHER ---
        publisher_ = image_transport::create_publisher(this, "image_raw", camera_qos);

        // --- SUBSCRIPTIONS ---
        
        // 1. DURUM ABONEL??? (G?NCELLEND?)
        // Art?k /state yerine /success/lockon_success dinleniyor ve ?zel QoS kullan?l?yor.
        subscription_ = this->create_subscription<std_msgs::msg::String>(
            "/success/lockon_success", 
            state_qos_profile, 
            std::bind(&CameraPublisher::state_callback, this, std::placeholders::_1));

        // 2. IMU ABONEL???
        imu_sub_ = this->create_subscription<px4_msgs::msg::SensorCombined>(
            "/fmu/out/sensor_combined", 
            px4_qos, 
            std::bind(&CameraPublisher::imu_callback, this, std::placeholders::_1));
        
        // --- KAMERA BA?LATMA ---
        init_camera();
        
        frame_ = cv::Mat(height_, width_, CV_8UC3);
        gray_frame_ = cv::Mat(height_, width_, CV_8UC1);

        timer_ = this->create_wall_timer(
            std::chrono::duration<double>(1.0 / fps_),
            std::bind(&CameraPublisher::timer_callback, this));

        RCLCPP_INFO(this->get_logger(), "KAMERA BA?LATILDI... Durum bekleniyor: /success/lockon_success");
    }

private:
    void imu_callback(const px4_msgs::msg::SensorCombined::SharedPtr msg)
    {
        uint64_t time_usec = msg->timestamp;
        uint64_t total_seconds = time_usec / 1000000;

        hours_ = ((total_seconds / 3600) + 3) % 24;
        minutes_ = (total_seconds / 60) % 60;
        seconds_ = total_seconds % 60;
        millis_ = (time_usec % 1000000) / 1000;

        data_received_ = true;
    }

    // --- DURUM CALLBACK (G?NCELLEND?) ---
    void state_callback(const std_msgs::msg::String::SharedPtr msg)
    {
        std::string current_mode = msg->data;
        
        // Referans koddaki mant?k ile ayn? kontrol
        bool is_kamikaze = (current_mode == "KAMIKAZE" || current_mode == "kamikaze");

        if (is_kamikaze) {
            if (!kamikaze_mode_) {
                kamikaze_mode_ = true;
                RCLCPP_INFO(this->get_logger(), ">>> KAMERA MODU: KAMIKAZE (Aktif) <<<");
            }
        } 
        else {
            if (kamikaze_mode_) {
                kamikaze_mode_ = false;
                RCLCPP_INFO(this->get_logger(), ">>> KAMERA MODU: NORMAL (Kamikaze Pasif) <<<");
            }
        }
    }

    void init_camera()
    {
        if (cap_.isOpened()) cap_.release();
        bool is_number = !device_path_.empty() && std::all_of(device_path_.begin(), device_path_.end(), ::isdigit);
        
        if (is_number) cap_.open(std::stoi(device_path_), cv::CAP_V4L2);
        else cap_.open(device_path_, cv::CAP_V4L2);

        if (cap_.isOpened()) {
            cap_.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'));
            cap_.set(cv::CAP_PROP_FRAME_WIDTH, width_);
            cap_.set(cv::CAP_PROP_FRAME_HEIGHT, height_);
            cap_.set(cv::CAP_PROP_FPS, fps_);
        } else {
            RCLCPP_ERROR(this->get_logger(), "KAMERA BULUNAMADI: %s", device_path_.c_str());
        }
    }

    void timer_callback()
    {
        if (!cap_.isOpened()) {
            RCLCPP_ERROR_THROTTLE(this->get_logger(), *this->get_clock(), 2000, "KAMERA BULUNAMADI");
            init_camera(); 
            return; 
        }

        cap_ >> frame_;
        if (frame_.empty()) return;

        std_msgs::msg::Header header;
        header.stamp = this->now();
        header.frame_id = frame_id_;

        char buffer[100];
        
        if (data_received_) {
            sprintf(buffer, "%02d:%02d:%02d.%03d", 
                hours_, minutes_, seconds_, millis_);
        } else {
            sprintf(buffer, "--:--:--.---");
        }

        std::string time_text(buffer);
        
        // Kamikaze modunda yaz? rengi de?i?imi (Beyaz vs Ye?il)
        cv::Scalar text_color = kamikaze_mode_ ? cv::Scalar(255) : cv::Scalar(0, 255, 0);
        
        cv::putText(frame_, time_text, cv::Point(20, 50), cv::FONT_HERSHEY_SIMPLEX, 1.0, text_color, 2);

        sensor_msgs::msg::Image::SharedPtr msg;
        try {
            if (kamikaze_mode_) {
                // Kamikaze modunda gri tonlama
                cv::cvtColor(frame_, gray_frame_, cv::COLOR_BGR2GRAY);
                msg = cv_bridge::CvImage(header, "mono8", gray_frame_).toImageMsg();
            } else {
                // Normal mod
                msg = cv_bridge::CvImage(header, "bgr8", frame_).toImageMsg();
            }
            publisher_.publish(std::move(msg));
        } catch (cv_bridge::Exception& e) {}
    }

    image_transport::Publisher publisher_;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
    rclcpp::Subscription<px4_msgs::msg::SensorCombined>::SharedPtr imu_sub_;

    cv::VideoCapture cap_;
    rclcpp::TimerBase::SharedPtr timer_;
    cv::Mat frame_, gray_frame_;
    std::string device_path_;
    int width_, height_;
    double fps_;
    std::string frame_id_;
    bool kamikaze_mode_ = false;

    int hours_ = 0, minutes_ = 0, seconds_ = 0, millis_ = 0;
    bool data_received_ = false;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<CameraPublisher>());
    rclcpp::shutdown();
    return 0;
}
