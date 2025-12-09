#include <px4_msgs/msg/offboard_control_mode.hpp>
#include <px4_msgs/msg/trajectory_setpoint.hpp>
#include <px4_msgs/msg/vehicle_command.hpp>
#include <px4_msgs/msg/vehicle_control_mode.hpp>
#include <px4_msgs/msg/vehicle_odometry.hpp>
#include <rclcpp/rclcpp.hpp>
#include <stdint.h>

#include <chrono>
#include <iostream>

using namespace std::chrono;
using namespace std::chrono_literals;
using namespace px4_msgs::msg;

class OffboardControl : public rclcpp::Node
{
public:
    OffboardControl() : Node("offboard_control"){

        rmw_qos_profile_t qos_profile = rmw_qos_profile_sensor_data;
        auto qos = rclcpp::QoS(rclcpp::QoSInitialization(qos_profile.history,5), qos_profile);

        offboard_control_mode_publisher_  = this->create_publisher<OffboardControlMode>("/fmu/in/offboard_control_mode", 10);
        trajectory_setpoint_publisher_ = this->create_publisher<TrajectorySetpoint>("/fmu/in/trajectory_setpoint",10);
        vehicle_command_publisher_ = this->create_publisher<VehicleCommand>("/fmu/in/vehicle_command",10);
        vehicle_odometry_subscriber_ =  this->create_subscription<VehicleOdometry>("/fmu/out/vehicle_odometry",qos,
            [this](const VehicleOdometry::SharedPtr msg){
                current_position_.store({msg->position[0], msg->position[1], msg->position[2]});
            });
            
        waypoints_.push_back({0.0,0.0,-5.0});
        waypoints_.push_back({5.0,0.0,-5.0});
        waypoints_.push_back({5.0,5.0,-5.0});
        waypoints_.push_back({0.0,5.0,-5.0});
        waypoints_.push_back({0.0,0.0,-5.0});

        offboard_setpoint_counter_ = 0;
        current_waypoint_index_ = 0;


        auto timer_callback = [this]() -> void {
            if (offboard_setpoint_counter_ == 10) {
                this->publish_vehicle_command(VehicleCommand::VEHICLE_CMD_DO_SET_MODE,1,6);

                this-> arm();
            }
        
            if (offboard_setpoint_counter_ > 10){
                this->process_waypoints();
            } else{
                publish_trajectory_setpoint(waypoints_[0]);
            }


            publish_offboard_control_mode();
            //publish_trajectory_setpoint();

            if (offboard_setpoint_counter_ < 11) {
                offboard_setpoint_counter_++;
            }
        };
        timer_ = this->create_wall_timer(100ms,timer_callback);

    }
    void arm();
    void disarm();

private:
    rclcpp::TimerBase::SharedPtr timer_;

    rclcpp::Publisher<OffboardControlMode>::SharedPtr offboard_control_mode_publisher_;
    rclcpp::Publisher<TrajectorySetpoint>::SharedPtr trajectory_setpoint_publisher_;
    rclcpp::Publisher<VehicleCommand>::SharedPtr vehicle_command_publisher_;
    rclcpp::Subscription<VehicleOdometry>::SharedPtr vehicle_odometry_subscriber_ ; 
    std::atomic<uint64_t> timestamp_;
    
    uint64_t offboard_setpoint_counter_;
    std::atomic<size_t> current_waypoint_index_;
    std::atomic<std::array<float, 3>>  current_position_ ;
    std::vector<std::array<float,3>> waypoints_;

    void publish_offboard_control_mode();
    void publish_trajectory_setpoint(const std::array<float,3>& position, float yaw = -3.14);
    void publish_vehicle_command(uint16_t command, float param1 = 0.0, float param2 = 0.0);
    void process_waypoints();
    float calculate_distance(const std::array<float, 3>& pos1, const std::array<float, 3>& pos2);

};

void OffboardControl::arm()
{
    publish_vehicle_command(VehicleCommand::VEHICLE_CMD_COMPONENT_ARM_DISARM,1.0);
    RCLCPP_INFO(this->get_logger(),"Arm command send");

}

void OffboardControl::disarm()
{

    publish_vehicle_command(VehicleCommand::VEHICLE_CMD_COMPONENT_ARM_DISARM,0.0);

    RCLCPP_INFO(this->get_logger(),"Disarm command send");

}

void OffboardControl::publish_offboard_control_mode()
{
    OffboardControlMode msg{};
    msg.position = true;
    msg.velocity = false;
    msg.acceleration = false;
    msg.attitude = false;
    msg.body_rate = false;
    msg.timestamp = this->get_clock()->now().nanoseconds() / 1000;
    offboard_control_mode_publisher_-> publish(msg);

}

void OffboardControl::publish_trajectory_setpoint(const std::array<float, 3>& position, float yaw)
{
    TrajectorySetpoint msg{};
    msg.position = {position[0], position[1], position[2]};
    msg.yaw = yaw;
    msg.timestamp = this->get_clock()->now().nanoseconds() / 1000;
    trajectory_setpoint_publisher_-> publish(msg);
}

void OffboardControl::publish_vehicle_command(uint16_t command, float param1,float param2)
{
    VehicleCommand msg{};
    msg.param1 = param1;
    msg.param2 = param2;
    msg.command = command;
    msg.target_system = 1;
    msg.target_component = 1;
    msg.source_system = 1;
    msg.source_component = 1 ; 
    msg.from_external = true;
    msg.timestamp = this->get_clock()->now().nanoseconds()/1000;
    vehicle_command_publisher_-> publish(msg);
}

void OffboardControl::process_waypoints(){
    if(current_waypoint_index_.load() >= waypoints_.size()){
        publish_trajectory_setpoint(waypoints_.back());
        return;
    }

    auto target_pos = waypoints_[current_waypoint_index_.load()];
    auto current_pos_local = current_position_.load();

    float distance = calculate_distance(current_pos_local,target_pos);

    if (distance < 0.5) {
        RCLCPP_INFO(this->get_logger(),"waypoint %zu'e ulaşıldı. Bir sonrakine geçiliyor", current_waypoint_index_ + 1);
        current_waypoint_index_ ++ ;
    }

    publish_trajectory_setpoint(target_pos);
}

float OffboardControl::calculate_distance(const std::array<float, 3>& pos1, const std::array<float, 3>& pos2){return sqrt(pow(pos1[0] - pos2[0], 2) + pow(pos1[1] - pos2[1], 2) + pow(pos1[2] - pos2[2], 2));}
int main(int argc, char *argv[])
{
    std::cout << "Starting ..." <<  std::endl;
    setvbuf(stdout, NULL , _IONBF, BUFSIZ);
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<OffboardControl>());

    rclcpp::shutdown();
    return 0;
}