#include "rclcpp/rclcpp.hpp"
#include "pars_msgs/msg/target.hpp"
#include<chrono>
#include<cmath>
#include<vector>

using namespace std::chrono_literals;

class DetectedTargetPublisher : public rclcpp::Node
{
public:
    DetectedTargetPublisher() : Node("detected_target_publisher")
    {
        publisher_ = this->create_publisher<pars_msgs::msg::Target>("/vision/detected_target", 10);

        timer_ = this->create_wall_timer(
            33ms, std::bind(&DetectedTargetPublisher::publish_message,this));

        RCLCPP_INFO(this->get_logger(),"Tespit node baslatildi");
        RCLCPP_INFO(this->get_logger(),"ITU ATA'yı BULDUM");
        start_time_ = this->get_clock()->now().seconds();
    }

private:
    void publish_message()
    {
        
        auto msg = pars_msgs::msg::Target();
        msg.image_width = 640.0f;
        msg.image_height = 480.0f;
        msg.target_detected = true;

        float image_center_x = msg.image_width / 2.0f;
        float image_center_y = msg.image_height / 2.0f;
        
        float amplitude = (msg.image_width - image_center_x) / 10.0f;

        double total_cycle_duration = 10.0;

        double current_time_sec = this->get_clock()->now().seconds();
        double omega = (2.0 *M_PI) / total_cycle_duration;

        float sin_wave_value = std::sin(omega * current_time_sec);

        msg.x_center = image_center_x + (amplitude * sin_wave_value);
        msg.y_center = image_center_y + (amplitude * sin_wave_value);
        
        std::vector<float> size_values = {32.0f, 120.0f, 220.0f, 350.0f};
        double elapsed_time = current_time_sec - start_time_;
        int index = (static_cast<int>(elapsed_time) / 10)% size_values.size();

        if (elapsed_time < 0) elapsed_time = 0; // Saat kaymalarına karşı önlem
        index = (static_cast<int>(elapsed_time) / 10) % size_values.size();
        
        msg.hedef_boyut = size_values[index];


        publisher_->publish(msg);

        RCLCPP_INFO_THROTTLE(
            this->get_logger(),
            *this->get_clock(),
            1000,
            "Sahte hedef yayınlandı: [x: %.1f, y: %.1f]",
            msg.x_center, msg.y_center
        );

    }

    rclcpp::Publisher<pars_msgs::msg::Target>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    double start_time_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<DetectedTargetPublisher>());
    rclcpp::shutdown();
    return 0;
}