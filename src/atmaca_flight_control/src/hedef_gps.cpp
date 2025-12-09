#include <rclcpp/rclcpp.hpp>
#include <memory>

// Girdi Mesajı: Hedef uçağın (px4_3) konumu
#include "px4_msgs/msg/vehicle_global_position.hpp"

#include "pars_msgs/msg/data.hpp"
using std::placeholders::_1;

class TestGpsPublisherNode : public rclcpp::Node
{
public:
    TestGpsPublisherNode() : Node("test_gps_publisher")
    {   
        rmw_qos_profile_t qos_profile = rmw_qos_profile_sensor_data;
        auto qos = rclcpp::QoS(rclcpp::QoSInitialization(qos_profile.history, 5), qos_profile);

        // Çıktı: Ana pilot node'umuzun dinlediği topic
        target_pub_ = this->create_publisher<pars_msgs::msg::Data>(
            "/target_gps_data", 10);

        px4_sub_ = this->create_subscription<px4_msgs::msg::VehicleGlobalPosition>(
            "/px4_4/fmu/out/vehicle_global_position",qos,
            std::bind(&TestGpsPublisherNode::px4_callback, this, _1));
        
        RCLCPP_INFO(this->get_logger(), "Test GPS Yayıncısı Başlatıldı.");
        RCLCPP_INFO(this->get_logger(), "/px4_4/fmu/out/vehicle_global_position dinleniyor...");
        RCLCPP_INFO(this->get_logger(), "/target_gps_data topic'ine yayın yapılacak.");
    }

private:
    void px4_callback(const px4_msgs::msg::VehicleGlobalPosition::SharedPtr msg)
    {
        // 1. Yeni bir 'TeamData' mesajı oluştur
        auto target_msg = pars_msgs::msg::Data();

        // 2. Gelen 'VehicleGlobalPosition' verisini 'TeamData' formatına çevir
        target_msg.iha_enlem = msg->lat;
        target_msg.iha_boylam = msg->lon;
        target_msg.iha_irtifa = msg->alt; // Deniz seviyesinden irtifa
        
        // Diğer önemli verileri de ekleyebiliriz
        target_msg.takim_numarasi = 4; // Bu uçağın 3 numara olduğunu biliyoruz

        // Gerekirse diğer alanları da doldurabilirsiniz (şimdilik 0 kalabilirler)
        // target_msg.iha_hizi = ... 
        
        // 3. Çevrilen mesajı yayınla
        target_pub_->publish(target_msg);
    }

    rclcpp::Publisher<pars_msgs::msg::Data>::SharedPtr target_pub_;
    rclcpp::Subscription<px4_msgs::msg::VehicleGlobalPosition>::SharedPtr px4_sub_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<TestGpsPublisherNode>());
    rclcpp::shutdown();
    return 0;
}