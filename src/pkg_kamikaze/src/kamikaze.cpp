#include <rclcpp/rclcpp.hpp>
#include "std_msgs/msg/string.hpp"

#include <px4_msgs/msg/vehicle_local_position.hpp> 
#include <px4_msgs/msg/vehicle_attitude_setpoint.hpp>
#include <px4_msgs/msg/vehicle_global_position.hpp>
#include <px4_msgs/msg/vehicle_command.hpp>
#include <px4_msgs/msg/offboard_control_mode.hpp>
#include <px4_msgs/msg/vehicle_attitude.hpp> 
#include <px4_msgs/msg/vehicle_status.hpp> 
#include <px4_msgs/msg/trajectory_setpoint.hpp>

#include <tf2/LinearMath/Quaternion.h> /

#include <chrono>
#include <memory>

using std::placeholders::_1;
using namespace std::chrono_literals;

class KamikazeMod : public rclcpp::Node
{
    public:
     KamikazeMod() : Node("kamikaze_mod_node"), visual_timeout_duration_(0s)
     {
        /*
          mod_sub = this->create_subscription<std_msgs::msg::String>(
          "/success/lockon_success", 10, std::bind(&KamikazeMod::mod_sub_callback, this, _1);)
        */    

         auto qos_px4 = rclcpp::QoS(rclcpp::KeepLast(1)).best_effort();

        this->declare_parameter<double>("thrust", 0.6);
        this->declare_parameter<double>("airspeed_mps", 15.0);
        this->declare_parameter<double>("max_roll_rad", 0.785);
        this->declare_parameter<double>("max_pitch_rad", 0.785);
        this->declare_parameter<int>("instance_id", 1);
	this->declare_parameter<double>("visual_timeout_sec", 0.5);

        double visual_timeout_sec = this->get_parameter("visual_timeout_sec").as_double();
        visual_timeout_duration_ = std::chrono::duration<double>(visual_timeout_sec);
        airspeed_mps_ = this->get_parameter("airspeed_mps").as_double();
        instance_id_ = this->get_parameter("instance_id").as_int();

        std::string prefix = (instance_id_ == 1) ? "/fmu/" : "/px4_" + std::to_string(instance_id_) + "/fmu/";

        RCLCPP_INFO(this->get_logger(), "Instance ID: %d | Prefix: %s | Airspeed: %.1f m/s",
                    instance_id_, prefix.c_str(), airspeed_mps_);

        //yükseklik enlem boylam değerlerini al (lat,lon,alt)
        gps_own_position_ = this->create_subscription<px4_msgs::msg::VehicleGlobalPosition>(
            prefix + "out/vehicle_global_position", qos_px4,
            std::bind(&KamikazeMod::gps_own_position_callback, this, _1));
        
        // x-> Yerel başlangıç noktasından Kuzey yönünde yer değiştirme.
        // y-> Yerel başlangıç noktasından Doğu yönünde yer değiştirme.
        // z-> aşağı/negatif irtifa (yerel hareketleri ve set noktalarını hesaplamak için kullanılır)
        // Yerel başlangıç noktasından Dünya merkezine doğru (aşağı) yer değiştirme.
        local_position_sub_ = this->create_subscription<px4_msgs::msg::VehicleLocalPosition>(
           prefix + "out/vehicle_local_position", qos_px4,
            std::bind(&KamikazeMod::local_position_callback,this,_1));

        //aracın roll (yatış), pitch (eğim) veya yaw (sapma) açısını bilmeniz gerekiyorsa
        //aracın şu anda nereye baktığını (yönelimini), küresel olarak Kuzey, Doğu ve Aşağı referansına göre
        vehicle_attitude_sub_ = this->create_subscription<px4_msgs::msg::VehicleAttitude>(
            prefix + "out/vehicle_attitude", qos_px4,
            std::bind(&KamikazeMod::vehicle_attitude_callback, this, _1));

        // aracı arm etmek için
        vehicle_status_sub_ = this->create_subscription<px4_msgs::msg::VehicleStatus>(
            prefix + "out/vehicle_status", qos_px4,
            std::bind(&KamikazeMod::vehicle_status_callback, this, _1));
  
         // --- px4 e attitude,offboard modunda olduğunu ve konum hedeflerini gönderir---

            //aracın roll pitch yaw değerlerni gönder (yönelim açısı)
        attitude_command_pub_ = this->create_publisher<px4_msgs::msg::VehicleAttitudeSetpoint>(
            prefix + "in/vehicle_attitude_setpoint", 10);

            //aracın genel komutları arming mod değişikliği,iniş,kalkış
            //offboarda geçmeden hemen önce gönder aracı arm etmek ve offbarda geçişi tetiklemek için
        vehicle_command_ = this->create_publisher<px4_msgs::msg::VehicleCommand>(
            prefix + "in/vehicle_command", 10);

            //offboard modunda hangi eksenlerin kontrol edileceği
        offboard_control_mode_pub_ = this->create_publisher<px4_msgs::msg::OffboardControlMode>(
            prefix + "in/offboard_control_mode", qos_px4);
        
            //Aracın Konum, Hız ve İvme Hedefleri (araç nereye gidecek hangi hızda hareket edecek)
        trajectory_setpoint_pub_ = this->create_publisher<px4_msgs::msg::TrajectorySetpoint>(
            prefix + "in/trajectory_setpoint", qos_px4);
        
        timer_ = this->create_wall_timer(50ms, std::bind(&KamikazeMod::kamikaze_, this));

        RCLCPP_INFO(this->get_logger(), "KAMIKAZE GÖREVİ BAŞLADI! px4_%d", instance_id_);
    
      }

     private:

     rcl_interfaces::msg::SetParametersResult parametersCallback(const std::vector<rclcpp::Parameter> & parameters)
    {
        rcl_interfaces::msg::SetParametersResult result;
        result.successful = true;
        result.reason = "success";

        for (const auto &param : parameters)
        {
            if (param.get_name() == "airspeed_mps")
            {
                if (param.get_type() == rclcpp::ParameterType::PARAMETER_DOUBLE)
                {
                    airspeed_mps_ = param.as_double();
                    RCLCPP_INFO(this->get_logger(), "⚡ Hız Güncellendi: %.1f m/s", airspeed_mps_);
                }
            }
        }
        return result;
    }

     void local_position_callback(const std::shared_ptr<const px4_msgs::msg::VehicleLocalPosition>& msg)
    {
        last_local_position_ = *msg;
        is_local_position_ready_=true;
    }

     void gps_own_position_callback(const std::shared_ptr<const px4_msgs::msg::VehicleGlobalPosition>& msg)
    {
        last_own_position_ = *msg;
        is_own_position_ready_ = true;
    }

    void vehicle_attitude_callback(const std::shared_ptr<const px4_msgs::msg::VehicleAttitude>& msg)
    {
        current_attitude_ = *msg;
    }

    void vehicle_status_callback(const std::shared_ptr<const px4_msgs::msg::VehicleStatus>& msg)
    {
        current_nav_state_ = msg->nav_state;
        //araç arm  oldu 
        is_armed_ = (msg->arming_state == px4_msgs::msg::VehicleStatus::ARMING_STATE_ARMED);
    }

    //ofboard için güvenli seçim 
    void publish_offboard_control_mode()
    {
        px4_msgs::msg::OffboardControlMode msg{};
        msg.position = true; // konum kontrolü
        msg.velocity = false;
        msg.acceleration = false;
        msg.attitude = true;
        msg.body_rate = false;
        msg.timestamp = this->get_clock()->now().nanoseconds() / 1000;
        offboard_control_mode_pub_->publish(msg);
    }

    void publish_airspeed_command()
    {
        //Hız ve/veya gaz ayar noktalarını değiştirir -> VEHICLE_CMD_DO_CHANGE_SPEED
        publish_vehicle_command(px4_msgs::msg::VehicleCommand::VEHICLE_CMD_DO_CHANGE_SPEED, 1.0f, airspeed_mps_);
    }

    void kamikaze_()
    {
    
        publish_offboard_control_mode();

        if (!is_armed_) {
            publish_vehicle_command(px4_msgs::msg::VehicleCommand::VEHICLE_CMD_COMPONENT_ARM_DISARM, 1.0f);
            RCLCPP_INFO_THROTTLE(this->get_logger(), *this->get_clock(), 2000, "ARM komutu gönderildi.");
            return;
        }

        if (current_nav_state_ != px4_msgs::msg::VehicleStatus::NAVIGATION_STATE_OFFBOARD) {
            offboard_setpoint_counter_++;
            publish_attitude_command(0.0f, 0.0f, 0.0f, 0.5f);
            px4_msgs::msg::TrajectorySetpoint msg{};
            msg.timestamp = this->get_clock()->now().nanoseconds() / 1000;
            
            msg.position[0] = NAN; msg.position[1] = NAN; msg.position[2] = NAN;
            msg.velocity[0] = NAN; msg.velocity[1] = NAN; msg.velocity[2] = NAN;
            msg.acceleration[0] = NAN; msg.acceleration[1] = NAN; msg.acceleration[2] = NAN;
            msg.jerk[0] = NAN; msg.jerk[1] = NAN; msg.jerk[2] = NAN;
            msg.yaw = NAN; 
            msg.yawspeed = NAN;

            trajectory_setpoint_pub_->publish(msg);

            if (offboard_setpoint_counter_ == 10) {
                publish_vehicle_command(px4_msgs::msg::VehicleCommand::VEHICLE_CMD_DO_SET_MODE, 1.0f, 6.0f);
                RCLCPP_WARN(this->get_logger(), "OFFBOARD MOD KOMUTU GÖNDERİLDİ");
            }
            RCLCPP_INFO_THROTTLE(this->get_logger(), *this->get_clock(), 1000,
                                 "Setpoint #%d → Offboard bekleniyor...", offboard_setpoint_counter_);
            return;
        }

        RCLCPP_INFO_ONCE(this->get_logger(), "OFFBOARD MODUNA GEÇİLDİ!");
      }


      void publish_attitude_command(float roll, float pitch, float yaw, float thrust)
    {
        px4_msgs::msg::VehicleAttitudeSetpoint msg{};
        tf2::Quaternion q;
        q.setRPY(roll, pitch, 0.0);
        q.normalize();
    
        msg.timestamp = this->get_clock()->now().nanoseconds() / 1000;
        
        msg.roll_body = roll;
        msg.pitch_body = pitch;
        msg.yaw_body = yaw;
        RCLCPP_INFO(this->get_logger(), "GONDERILEN KOMUT → ROLL:%.1f PITCH:%.1f ", msg.roll_body, msg.pitch_body);

        msg.q_d[0] = q.w();
        msg.q_d[1] = q.x();
        msg.q_d[2] = q.y();
        msg.q_d[3] = q.z();

        msg.thrust_body[0] = thrust;

        attitude_command_pub_->publish(std::move(msg));
    }

    void publish_vehicle_command(uint16_t command, float param1 = 0.0f, float param2 = 0.0f)
    {
        px4_msgs::msg::VehicleCommand msg{};
        msg.timestamp = this->get_clock()->now().nanoseconds() / 1000;
        msg.command = command;
        msg.param1 = param1;
        msg.param2 = param2;
        msg.target_system = 1;
        msg.target_component = 1;
        msg.source_system = 1;
        msg.source_component = 1;
        msg.from_external = true;
        vehicle_command_->publish(msg);
    }

    bool is_own_position_ready_ = false;
    bool is_local_position_ready_ = false;
    bool is_armed_ = false;

    rclcpp::Time last_visual_detection_time_{0, 0, RCL_ROS_TIME};
    rclcpp::Duration visual_timeout_duration_;

    px4_msgs::msg::VehicleAttitude current_attitude_;
    uint8_t current_nav_state_ = 0;

    px4_msgs::msg::VehicleLocalPosition last_local_position_;
    px4_msgs::msg::VehicleGlobalPosition last_own_position_;
  
    rclcpp::Subscription<px4_msgs::msg::VehicleLocalPosition>::SharedPtr local_position_sub_;
    rclcpp::Subscription<px4_msgs::msg::VehicleGlobalPosition>::SharedPtr gps_own_position_;
    rclcpp::Subscription<px4_msgs::msg::VehicleAttitude>::SharedPtr vehicle_attitude_sub_;
    rclcpp::Subscription<px4_msgs::msg::VehicleStatus>::SharedPtr vehicle_status_sub_;

    //rclcpp::Subscription<std_msgs::msg::String>::SharedPtr state_sub_;

    rclcpp::Publisher<px4_msgs::msg::VehicleAttitudeSetpoint>::SharedPtr attitude_command_pub_;
    rclcpp::Publisher<px4_msgs::msg::VehicleCommand>::SharedPtr vehicle_command_;
    rclcpp::Publisher<px4_msgs::msg::OffboardControlMode>::SharedPtr offboard_control_mode_pub_;
    rclcpp::Publisher<px4_msgs::msg::TrajectorySetpoint>::SharedPtr trajectory_setpoint_pub_;

    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Node::OnSetParametersCallbackHandle::SharedPtr parameters_callback_handle_;

    double airspeed_mps_ = 15.0;
    int instance_id_ = 1;
    int offboard_setpoint_counter_ = 0;  
     /*
     void mod_sub_callback(const std_msgs::msg::String & msg) const
      {
        if(msg == "KAMIKAZE")
        {
            RCLCPP_INFO(this->get_logger(), "KAMIKAZE BASLADI.");
        }

      }

      rclcpp::Subscription<std_msgs::msg::String>::SharedPtr mod_sub;
     
     */
      
};


int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<KamikazeMod>());
  rclcpp::shutdown();
  return 0;
}
