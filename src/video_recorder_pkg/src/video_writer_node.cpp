#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include <sys/stat.h> // Klas?r kontrol? ve olu?turma i?in gerekli

#ifndef CV_CAP_GSTREAMER
    #define CV_CAP_GSTREAMER 1
#endif

class VideoWriterNode : public rclcpp::Node
{
public:
    VideoWriterNode() : Node("video_writer")
    {
        is_recording_ = false;

        // G?NCELLEME: Hedef klas?r? tan?ml?yoruz
        target_directory_ = "/root/bridges/video/";

        // Klas?r kontrol?: E?er '/root/bridges/video' yoksa olu?tur.
        struct stat st = {0};
        if (stat(target_directory_.c_str(), &st) == -1) {
            // Klas?r yoksa olu?tur (0777 izinleriyle)
            int status = mkdir(target_directory_.c_str(), 0777);
            if(status == 0) {
                RCLCPP_INFO(this->get_logger(), "Klasor olusturuldu: %s", target_directory_.c_str());
            } else {
                RCLCPP_WARN(this->get_logger(), "Klasor olusturulamadi! Lutfen '/root/bridges' icinde 'video' klasoru oldugundan emin olun.");
            }
        }

        control_sub_ = this->create_subscription<std_msgs::msg::String>(
            "/kayit/kontrol",
            10,
            std::bind(&VideoWriterNode::controlCallback, this, std::placeholders::_1)
        );

        // --- D?ZELTME BURADA YAPILDI ---
        // QoS Profili 'rclcpp::SensorDataQoS()' olarak ayarland? (Best Effort)
        image_sub_ = this->create_subscription<sensor_msgs::msg::Image>(
            "/image_raw", 
            rclcpp::SensorDataQoS(), // Buras? '10' yerine 'SensorDataQoS()' yap?ld?
            std::bind(&VideoWriterNode::imageCallback, this, std::placeholders::_1)
        );

        RCLCPP_INFO(this->get_logger(), "Video Writer Hazir (QoS: Best Effort). Kayit Yeri: %s", target_directory_.c_str());
    }

private:
    bool is_recording_;
    cv::VideoWriter writer_;
    std::string output_file_;
    std::string target_directory_; // Klas?r yolunu tutan de?i?ken

    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr control_sub_;
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr image_sub_;

    void startRecording()
    {
        if (is_recording_) return;

        auto now = std::chrono::system_clock::now();
        std::time_t t = std::chrono::system_clock::to_time_t(now);
        char buffer[100];
        std::strftime(buffer, sizeof(buffer), "%Y%m%d_%H%M%S", std::localtime(&t));

        // ?STEK: Docker volume yoluna g?re dosya yolu ayarland?
        output_file_ = target_directory_ + "gorev_kaydi_" + std::string(buffer) + ".avi";

        int width  = 640;
        int height = 480;
        int fps    = 30;

        // GStreamer Pipeline (Jetson Donan?m H?zland?rma)
        std::string pipeline = (
            "appsrc ! videoconvert ! x264enc tune=zerolatency ! "
            "queue ! avimux ! filesink location=" + output_file_
        );

        // ?nce Gstreamer dene
        writer_.open(pipeline, cv::CAP_GSTREAMER, fps, cv::Size(width, height), true);

        // A??lmazsa CPU codec dene
        if (!writer_.isOpened())
        {
            RCLCPP_WARN(this->get_logger(), "GStreamer acilmadi, CPU (XVID) moduna geciliyor...");
            writer_.open(output_file_, cv::VideoWriter::fourcc('X','V','I','D'), fps, cv::Size(width, height));
            
            if (!writer_.isOpened()) {
                 RCLCPP_ERROR(this->get_logger(), "Video dosyasi olusturulamadi! Yol: %s", output_file_.c_str());
                 return;
            }
        }

        is_recording_ = true;
        RCLCPP_INFO(this->get_logger(), "KAYIT BASLADI: %s", output_file_.c_str());
    }

    void stopRecording()
    {
        if (!is_recording_) return;
        writer_.release();
        is_recording_ = false;
        RCLCPP_INFO(this->get_logger(), "KAYIT DURDURULDU. Dosya kapatildi.");
    }

    void controlCallback(const std_msgs::msg::String::SharedPtr msg)
    {
        std::string cmd = msg->data;
        if (cmd == "start") startRecording();
        else if (cmd == "stop") stopRecording();
    }

    void imageCallback(const sensor_msgs::msg::Image::SharedPtr msg)
    {
        if (!is_recording_) return;
        if (!writer_.isOpened()) { is_recording_ = false; return; }

        try {
            cv::Mat frame = cv_bridge::toCvCopy(msg, "bgr8")->image;
            writer_.write(frame);
        }
        catch (std::exception &e) {
            RCLCPP_ERROR(this->get_logger(), "Frame isleme hatasi: %s", e.what());
        }
    }
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<VideoWriterNode>());
    rclcpp::shutdown();
    return 0;
}
