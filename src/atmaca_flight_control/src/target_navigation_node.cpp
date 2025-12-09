#include <chrono>
#include <memory>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp_lifecycle/lifecycle_node.hpp>
#include <lifecycle_msgs/msg/state.hpp>

#include <px4_msgs/msg/vehicle_local_position.hpp>
#include <px4_msgs/msg/vehicle_attitude_setpoint.hpp>
#include <px4_msgs/msg/vehicle_global_position.hpp>
#include <px4_msgs/msg/vehicle_command.hpp>
#include <px4_msgs/msg/offboard_control_mode.hpp>
#include <px4_msgs/msg/vehicle_attitude.hpp>
#include <px4_msgs/msg/vehicle_status.hpp>
#include <px4_msgs/msg/trajectory_setpoint.hpp>

//#include <std_msgs/msg/string.hpp>

#include <tf2/LinearMath/Quaternion.h>
#include <tf2/LinearMath/Matrix3x3.h>
#include <cmath>
#include "pars_msgs/msg/data.hpp"
#include "pars_msgs/msg/target.hpp"

using std::placeholders::_1;
using namespace std::chrono_literals;
using CallbackReturn = rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn;

enum class NavState {
    GPS_FOLLOW,
    VISUAL_LOCK
};

class TargetNavigatingNode : public rclcpp_lifecycle::LifecycleNode
{
public:
    explicit TargetNavigatingNode(const rclcpp::NodeOptions & options)
    : rclcpp_lifecycle::LifecycleNode("target_navigation_node", options),
    visual_timeout_duration_(0s)
    {
        this->declare_parameter<double>("thrust", 0.6);
        this->declare_parameter<double>("visual_timeout_sec", 1.0);
        this->declare_parameter<double>("airspeed_mps", 15.0);
        this->declare_parameter<double>("kp_roll", 0.0015);
        this->declare_parameter<double>("kp_pitch", -0.0015);
        this->declare_parameter<double>("max_roll_rad", 0.785);
        this->declare_parameter<double>("max_pitch_rad", 0.785);
        this->declare_parameter<int>("instance_id", 1);

        parameters_callback_handle_ = this->add_on_set_parameters_callback(
            std::bind(&TargetNavigatingNode::parametersCallback, this, _1));

        airspeed_mps_ = this->get_parameter("airspeed_mps").as_double();
        instance_id_ = this->get_parameter("instance_id").as_int();    

        RCLCPP_INFO(get_logger(), "Lifecycle node yaratildi. 'Unconfigured'durumunda bekliyor");
    }

    CallbackReturn on_configure(const rclcpp_lifecycle::State &)
    {
        RCLCPP_INFO(get_logger(), "Yapilandiriliyor(Configuring)...");

        auto qos_px4 = rclcpp::QoS(rclcpp::KeepLast(1)).best_effort();

        double visual_timeout_sec = this->get_parameter("visual_timeout_sec").as_double();
        visual_timeout_duration_ = std::chrono::duration<double>(visual_timeout_sec);
        airspeed_mps_ = this->get_parameter("airspeed_mps").as_double();
        instance_id_ = this->get_parameter("instance_id").as_int();

        std::string prefix = (instance_id_ == 1) ? "/fmu/" : "/px4_" + std::to_string(instance_id_) + "/fmu/";

        RCLCPP_INFO(this->get_logger(), "Instance ID: %d | Prefix: %s | Airspeed: %.1f m/s",
                    instance_id_, prefix.c_str(), airspeed_mps_);

        visual_target_sub_ = this->create_subscription<pars_msgs::msg::Target>(
            "/vision/detected_target", 10,
            std::bind(&TargetNavigatingNode::visual_target_callback, this, _1));

        gps_target_sub_ = this->create_subscription<pars_msgs::msg::Data>(
            "/target_gps_data", 10,
            std::bind(&TargetNavigatingNode::gps_target_callback, this, _1));

        gps_own_position_ = this->create_subscription<px4_msgs::msg::VehicleGlobalPosition>(
            prefix + "out/vehicle_global_position", qos_px4,
            std::bind(&TargetNavigatingNode::gps_own_position_callback, this, _1));

        local_position_sub_ = this->create_subscription<px4_msgs::msg::VehicleLocalPosition>(
            prefix + "out/vehicle_local_position", qos_px4,
            std::bind(&TargetNavigatingNode::local_position_callback,this,_1));

        vehicle_attitude_sub_ = this->create_subscription<px4_msgs::msg::VehicleAttitude>(
            prefix + "out/vehicle_attitude", qos_px4,
            std::bind(&TargetNavigatingNode::vehicle_attitude_callback, this, _1));

        vehicle_status_sub_ = this->create_subscription<px4_msgs::msg::VehicleStatus>(
            prefix + "out/vehicle_status", qos_px4,
            std::bind(&TargetNavigatingNode::vehicle_status_callback, this, _1));
        
        attitude_command_pub_ = this->create_publisher<px4_msgs::msg::VehicleAttitudeSetpoint>(
            prefix + "in/vehicle_attitude_setpoint", 10);

        vehicle_command_ = this->create_publisher<px4_msgs::msg::VehicleCommand>(
            prefix + "in/vehicle_command", 10);

        offboard_control_mode_pub_ = this->create_publisher<px4_msgs::msg::OffboardControlMode>(
            prefix + "in/offboard_control_mode", qos_px4);
        
            trajectory_setpoint_pub_ = this->create_publisher<px4_msgs::msg::TrajectorySetpoint>(
            prefix + "in/trajectory_setpoint", qos_px4);
        

        RCLCPP_INFO(get_logger(), "Yapilandirma tamamlandi. Inactive moda geciliyor");
        return CallbackReturn::SUCCESS;
    }

    CallbackReturn on_activate(const rclcpp_lifecycle::State & state)
    {
        RCLCPP_INFO(get_logger(), "Aktif Ediliyor ...");

        LifecycleNode::on_activate(state);

        timer_ = this->create_wall_timer(50ms, std::bind(&TargetNavigatingNode::ituatatampon, this));


        RCLCPP_INFO(get_logger(), "Sistem aktif.");
        return CallbackReturn::SUCCESS;
    }

    CallbackReturn on_deactivate(const rclcpp_lifecycle::State & state)
    {
        RCLCPP_INFO(get_logger(), "Pasife alınıyor...");
        
        timer_->cancel();

        LifecycleNode::on_deactivate(state);
        
        return CallbackReturn::SUCCESS;
    }

    CallbackReturn on_cleanup(const rclcpp_lifecycle::State &)
    {
        RCLCPP_INFO(get_logger(), "Temizleniyor...");

        timer_.reset();
        attitude_command_pub_.reset();
        vehicle_command_.reset();
        offboard_control_mode_pub_.reset();
        trajectory_setpoint_pub_.reset();
        
        visual_target_sub_.reset();
        gps_target_sub_.reset();
        gps_own_position_.reset();
        local_position_sub_.reset();
        vehicle_attitude_sub_.reset();
        vehicle_status_sub_.reset();

        return CallbackReturn::SUCCESS;
    }

    CallbackReturn on_shutdown(const rclcpp_lifecycle::State &)
    {
        timer_.reset();

        return CallbackReturn::SUCCESS;
    }

    /* TargetNavigatingNode() : Node("target_navigating_node"), visual_timeout_duration_(0s)
    {
        auto qos_px4 = rclcpp::QoS(rclcpp::KeepLast(1)).best_effort();

        this->declare_parameter<double>("thrust", 0.6);
        this->declare_parameter<double>("visual_timeout_sec", 1.0);
        this->declare_parameter<double>("airspeed_mps", 15.0);
        this->declare_parameter<double>("kp_roll", 0.0015);
        this->declare_parameter<double>("kp_pitch", -0.0015);
        this->declare_parameter<double>("max_roll_rad", 0.785);
        this->declare_parameter<double>("max_pitch_rad", 0.785);
        this->declare_parameter<int>("instance_id", 1);

        double visual_timeout_sec = this->get_parameter("visual_timeout_sec").as_double();
        visual_timeout_duration_ = std::chrono::duration<double>(visual_timeout_sec);
        airspeed_mps_ = this->get_parameter("airspeed_mps").as_double();
        instance_id_ = this->get_parameter("instance_id").as_int();

        std::string prefix = (instance_id_ == 1) ? "/fmu/" : "/px4_" + std::to_string(instance_id_) + "/fmu/";

        RCLCPP_INFO(this->get_logger(), "Instance ID: %d | Prefix: %s | Airspeed: %.1f m/s",
                    instance_id_, prefix.c_str(), airspeed_mps_);

        visual_target_sub_ = this->create_subscription<pars_msgs::msg::Target>(
            "/vision/detected_target", 10,
            std::bind(&TargetNavigatingNode::visual_target_callback, this, _1));

        gps_target_sub_ = this->create_subscription<pars_msgs::msg::Data>(
            "/target_gps_data", 10,
            std::bind(&TargetNavigatingNode::gps_target_callback, this, _1));

        gps_own_position_ = this->create_subscription<px4_msgs::msg::VehicleGlobalPosition>(
            prefix + "out/vehicle_global_position", qos_px4,
            std::bind(&TargetNavigatingNode::gps_own_position_callback, this, _1));

        local_position_sub_ = this->create_subscription<px4_msgs::msg::VehicleLocalPosition>(
            prefix + "out/vehicle_local_position", qos_px4,
            std::bind(&TargetNavigatingNode::local_position_callback,this,_1));

        vehicle_attitude_sub_ = this->create_subscription<px4_msgs::msg::VehicleAttitude>(
            prefix + "out/vehicle_attitude", qos_px4,
            std::bind(&TargetNavigatingNode::vehicle_attitude_callback, this, _1));

        vehicle_status_sub_ = this->create_subscription<px4_msgs::msg::VehicleStatus>(
            prefix + "out/vehicle_status", qos_px4,
            std::bind(&TargetNavigatingNode::vehicle_status_callback, this, _1));

        state_sub_ = this->create_subscription<std_msgs::msg::String>(
            "/mission_state", 10,
            [this](const std_msgs::msg::String::SharedPtr msg) {
            if (msg->data == "TRACKING") {
                if (!is_tracking_active_) {
                    RCLCPP_INFO(this->get_logger(), "TAKİP MODU AKTİF EDİLDİ!");
                }
                is_tracking_active_ = true;
            } else {
                if (is_tracking_active_) {
                    RCLCPP_WARN(this->get_logger(), "TAKİP MODU DURDURULDU (BEKLEMEDE).");
                }
                is_tracking_active_ = false;
            }
        });

        attitude_command_pub_ = this->create_publisher<px4_msgs::msg::VehicleAttitudeSetpoint>(
            prefix + "in/vehicle_attitude_setpoint", 10);

        vehicle_command_ = this->create_publisher<px4_msgs::msg::VehicleCommand>(
            prefix + "in/vehicle_command", 10);

        offboard_control_mode_pub_ = this->create_publisher<px4_msgs::msg::OffboardControlMode>(
            prefix + "in/offboard_control_mode", qos_px4);
        
            trajectory_setpoint_pub_ = this->create_publisher<px4_msgs::msg::TrajectorySetpoint>(
            prefix + "in/trajectory_setpoint", qos_px4);
        
        timer_ = this->create_wall_timer(50ms, std::bind(&TargetNavigatingNode::ituatatampon, this));

        RCLCPP_INFO(this->get_logger(), "KILITLENME GÖREVİ BAŞLADI! px4_%d", instance_id_);
    }
    */
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
        if (this->get_current_state().id() != lifecycle_msgs::msg::State::PRIMARY_STATE_ACTIVE) return;
        last_local_position_ = *msg;
        is_local_position_ready_=true;
    }


    void visual_target_callback(const std::shared_ptr<const pars_msgs::msg::Target>& msg)
    {
        if (this->get_current_state().id() != lifecycle_msgs::msg::State::PRIMARY_STATE_ACTIVE) return;
        last_visual_target_ = *msg;
        if (msg->target_detected) {
            last_visual_detection_time_ = this->get_clock()->now();
        }
    }

    void gps_target_callback(const std::shared_ptr<const pars_msgs::msg::Data>& msg)
    {
        if (this->get_current_state().id() != lifecycle_msgs::msg::State::PRIMARY_STATE_ACTIVE) return;
        last_gps_target_ = *msg;
        is_gps_target_ready_ = true;
        RCLCPP_INFO(this->get_logger(), "GPS Hedef: %.6f, %.6f, %.2f",
                    msg->iha_enlem, msg->iha_boylam, msg->iha_irtifa);
    }

    void gps_own_position_callback(const std::shared_ptr<const px4_msgs::msg::VehicleGlobalPosition>& msg)
    {
        if (this->get_current_state().id() != lifecycle_msgs::msg::State::PRIMARY_STATE_ACTIVE) return;
        last_own_position_ = *msg;
        is_own_position_ready_ = true;
    }

    void vehicle_attitude_callback(const std::shared_ptr<const px4_msgs::msg::VehicleAttitude>& msg)
    {
       if (this->get_current_state().id() != lifecycle_msgs::msg::State::PRIMARY_STATE_ACTIVE) return;
        current_attitude_ = *msg;
    }

    void vehicle_status_callback(const std::shared_ptr<const px4_msgs::msg::VehicleStatus>& msg)
    {
        if (this->get_current_state().id() != lifecycle_msgs::msg::State::PRIMARY_STATE_ACTIVE) return;
        current_nav_state_ = msg->nav_state;
        is_armed_ = (msg->arming_state == px4_msgs::msg::VehicleStatus::ARMING_STATE_ARMED);
    }

    void publish_offboard_control_mode()
    {
        px4_msgs::msg::OffboardControlMode msg{};
        msg.position = true;
        msg.velocity = false;
        msg.acceleration = false;
        msg.attitude = true;
        msg.body_rate = false;
        msg.timestamp = this->get_clock()->now().nanoseconds() / 1000;
        offboard_control_mode_pub_->publish(msg);
    }

    void publish_airspeed_command()
    {
        publish_vehicle_command(px4_msgs::msg::VehicleCommand::VEHICLE_CMD_DO_CHANGE_SPEED, 1.0f, airspeed_mps_);
    }

    void ituatatampon()
    {
    /*    if (!is_tracking_active_){
            return;
        }
    */
        publish_offboard_control_mode();
        //publish_airspeed_command();

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

        auto time_since_last_visual = this->get_clock()->now() - last_visual_detection_time_;
        current_state_ = (time_since_last_visual < visual_timeout_duration_) ? NavState::VISUAL_LOCK : NavState::GPS_FOLLOW;

        if (current_state_ == NavState::VISUAL_LOCK) {
            run_visual_lock_control();
        } else {
            run_gps_follow_control();
        }
    }

    void run_gps_follow_control()
        {
        if (!is_gps_target_ready_ || !is_own_position_ready_ || !is_local_position_ready_) return;

        double current_lat = last_own_position_.lat;
        double current_lon = last_own_position_.lon;
        float current_alt = last_own_position_.alt;

        double target_lat = last_gps_target_.iha_enlem;
        double target_lon = last_gps_target_.iha_boylam;
        float target_alt = last_gps_target_.iha_irtifa;

        double distance = calculate_distance_meters(current_lat, current_lon, target_lat, target_lon);
        double bearing = calculate_bearing_rad(current_lat, current_lon, target_lat, target_lon);
        float alt_error = target_alt - current_alt;

        float current_local_x = last_local_position_.x;
        float current_local_y = last_local_position_.y;
        float current_local_z = last_local_position_.z;

    
        float target_local_x = current_local_x + (distance * cos(bearing));
        float target_local_y = current_local_y + (distance * sin(bearing));
        float target_local_z = current_local_z - alt_error;

        px4_msgs::msg::TrajectorySetpoint msg{};
        msg.timestamp = this->get_clock()->now().nanoseconds() / 1000;


        msg.position[0] = target_local_x;
        msg.position[1] = target_local_y;
        msg.position[2] = target_local_z;

        msg.velocity[0] = NAN; msg.velocity[1] = NAN; msg.velocity[2] = NAN;
        msg.acceleration[0] = NAN; msg.acceleration[1] = NAN; msg.acceleration[2] = NAN;
        msg.jerk[0] = NAN; msg.jerk[1] = NAN; msg.jerk[2] = NAN;
        msg.yaw = NAN; 
        msg.yawspeed = NAN;

        trajectory_setpoint_pub_->publish(msg);

        RCLCPP_INFO_THROTTLE(this->get_logger(), *this->get_clock(), 2000,
            "Hedef: %.0fm | Mod: Position | Hız Parametresi: %.1f", 
            distance, airspeed_mps_);
    }

    void run_visual_lock_control()
    {
        if (!last_visual_target_.target_detected) return;

        tf2::Quaternion q(current_attitude_.q[1], current_attitude_.q[2], current_attitude_.q[3], current_attitude_.q[0]);
        tf2::Matrix3x3 m(q);
        double roll, pitch, current_yaw;
        m.getRPY(roll, pitch, current_yaw);
        RCLCPP_INFO(this->get_logger(),
            "Mevcut ROLL PITCH: %.3f | %.3f", roll * 180/M_PI ,pitch * 180/M_PI);

        float image_center_x = last_visual_target_.image_width / 2.0f;
        float image_center_y = last_visual_target_.image_height / 2.0f;
        float error_x = last_visual_target_.x_center - image_center_x;
        float error_y = last_visual_target_.y_center - image_center_y;

        float hedef_boyut = last_visual_target_.hedef_boyut;
        double min_thrust = 0.2; 
        double max_thrust = 1.0;
        float target_thrust = 0.0;

        if (hedef_boyut >= image_center_x) 
        {
            target_thrust = min_thrust;
        } 
        else 
        {
            float ratio = hedef_boyut / image_center_x;
            
            target_thrust = min_thrust + ((1.0f - ratio) * (max_thrust - min_thrust));
        }
        double Kp_roll = this->get_parameter("kp_roll").as_double();
        double Kp_pitch = this->get_parameter("kp_pitch").as_double();
        float max_roll = this->get_parameter("max_roll_rad").as_double();
        float max_pitch = this->get_parameter("max_pitch_rad").as_double();

        float target_roll = std::clamp(static_cast<float>(roll + (Kp_roll * error_x)), -max_roll, max_roll);
        float target_pitch = std::clamp(static_cast<float>(pitch + (Kp_pitch * error_y)), -max_pitch, max_pitch);
        //float target_thrust = this->get_parameter("thrust").as_double();

        RCLCPP_INFO(this->get_logger(), "VISUAL → error_x:%.1f error_y:%.1f → Roll:%.3f Pitch:%.3f", error_x, error_y, target_roll, target_pitch);
        publish_attitude_command(target_roll, target_pitch, 0.0f, target_thrust);
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

    double calculate_distance_meters(double lat1, double lon1, double lat2, double lon2)
    {
        const double R = 6371000.0;
        double dlat = (lat2 - lat1) * M_PI / 180.0;
        double dlon = (lon2 - lon1) * M_PI / 180.0;
        double a = sin(dlat/2)*sin(dlat/2) + cos(lat1*M_PI/180.0)*cos(lat2*M_PI/180.0)*sin(dlon/2)*sin(dlon/2);
        double c = 2 * atan2(sqrt(a), sqrt(1-a));
        return R * c;
    }

    double calculate_bearing_rad(double lat1, double lon1, double lat2, double lon2)
    {
        
        double lat1_r = lat1 * M_PI / 180.0;
        double lon1_r = lon1 * M_PI / 180.0;
        double lat2_r = lat2 * M_PI / 180.0;
        double lon2_r = lon2 * M_PI / 180.0;

        double dLon = lon2_r - lon1_r;

        
        double y = sin(dLon) * cos(lat2_r);
        double x = cos(lat1_r) * sin(lat2_r) - sin(lat1_r) * cos(lat2_r) * cos(dLon);
        
        return atan2(y, x); // Sonuç -PI ile +PI arasında
    }

    double normalize_angle(double angle)
    {
        while (angle > M_PI) angle -= 2.0 * M_PI;
        while (angle < -M_PI) angle += 2.0 * M_PI;
        return angle;
    }

    // Member Variables
    bool is_gps_target_ready_ = false;
    bool is_own_position_ready_ = false;
    bool is_local_position_ready_ = false;
    bool is_armed_ = false;
    //bool is_tracking_active_ = false;

    NavState current_state_ = NavState::GPS_FOLLOW;
    rclcpp::Time last_visual_detection_time_{0, 0, RCL_ROS_TIME};
    rclcpp::Duration visual_timeout_duration_;

    px4_msgs::msg::VehicleAttitude current_attitude_;
    uint8_t current_nav_state_ = 0;

    px4_msgs::msg::VehicleLocalPosition last_local_position_;
    px4_msgs::msg::VehicleGlobalPosition last_own_position_;
    pars_msgs::msg::Target last_visual_target_;
    pars_msgs::msg::Data last_gps_target_;

    rclcpp::Subscription<pars_msgs::msg::Target>::SharedPtr visual_target_sub_;
    rclcpp::Subscription<pars_msgs::msg::Data>::SharedPtr gps_target_sub_;
    rclcpp::Subscription<px4_msgs::msg::VehicleLocalPosition>::SharedPtr local_position_sub_;
    rclcpp::Subscription<px4_msgs::msg::VehicleGlobalPosition>::SharedPtr gps_own_position_;
    rclcpp::Subscription<px4_msgs::msg::VehicleAttitude>::SharedPtr vehicle_attitude_sub_;
    rclcpp::Subscription<px4_msgs::msg::VehicleStatus>::SharedPtr vehicle_status_sub_;

    //rclcpp::Subscription<std_msgs::msg::String>::SharedPtr state_sub_;
    /*
    rclcpp::Publisher<px4_msgs::msg::VehicleAttitudeSetpoint>::SharedPtr attitude_command_pub_;
    rclcpp::Publisher<px4_msgs::msg::VehicleCommand>::SharedPtr vehicle_command_;
    rclcpp::Publisher<px4_msgs::msg::OffboardControlMode>::SharedPtr offboard_control_mode_pub_;
    rclcpp::Publisher<px4_msgs::msg::TrajectorySetpoint>::SharedPtr trajectory_setpoint_pub_;
    */
    rclcpp_lifecycle::LifecyclePublisher<px4_msgs::msg::VehicleAttitudeSetpoint>::SharedPtr attitude_command_pub_;
    rclcpp_lifecycle::LifecyclePublisher<px4_msgs::msg::VehicleCommand>::SharedPtr vehicle_command_;
    rclcpp_lifecycle::LifecyclePublisher<px4_msgs::msg::OffboardControlMode>::SharedPtr offboard_control_mode_pub_;
    rclcpp_lifecycle::LifecyclePublisher<px4_msgs::msg::TrajectorySetpoint>::SharedPtr trajectory_setpoint_pub_;

    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::node_interfaces::OnSetParametersCallbackHandle::SharedPtr parameters_callback_handle_;

    double airspeed_mps_ = 15.0;
    int instance_id_ = 1;
    int offboard_setpoint_counter_ = 0;  
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::NodeOptions options;
    auto node = std::make_shared<TargetNavigatingNode>(options);
    rclcpp::spin(node->get_node_base_interface());
    rclcpp::shutdown();
    return 0;
}