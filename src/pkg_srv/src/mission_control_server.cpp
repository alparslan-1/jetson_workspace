#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "pkg_srv/srv/mission_control.hpp" 
#include <functional>
#include <memory>
#include <string>
#include <memory>

using ChangeMode = pkg_srv::srv::MissionControl;


rclcpp::QoS reliable_mode_qos()
{
  rclcpp::QoS qos_profile(1);
  qos_profile.reliable();
  qos_profile.transient_local();
  qos_profile.keep_last(1);

  return qos_profile;
}

class  MissionControlNode : public rclcpp::Node
{
  public:
        MissionControlNode() : Node("mission_control_n") // the name of server node
        {
          service = this->create_service<ChangeMode>(
          "mission_control_node",
          std::bind(&MissionControlNode::handle_request, this,
          std::placeholders::_1, std::placeholders::_2));

	  publisher = this->create_publisher<std_msgs::msg::String>
	  ("/success/lockon_success", reliable_mode_qos());

       	  subscriber = this->create_subscription<std_msgs::msg::String>
	  ("/gcs/all_team_data", reliable_mode_qos(),
	  std::bind(&MissionControlNode::topic_callback, this, std::placeholders::_1));

        }
  private:
        std::string current_mode;
        rclcpp::Service<ChangeMode>::SharedPtr service;
	rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher;
	rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscriber;

        void handle_request(
            const std::shared_ptr<ChangeMode::Request> request,
            const std::shared_ptr<ChangeMode::Response> response)
        {
            std::string incoming_mode = request->state; // ?nce ge?ici de?i?kene alal?m

            // Sadece ge?erli komutlarda modu de?i?tirip yay?nlayal?m
            if(incoming_mode == "DOLASIM" || incoming_mode == "KAMIKAZE" || incoming_mode == "KILITLENME")
            {
                current_mode = incoming_mode;       // Kal?c? de?i?keni g?ncelle
                response->mission_state = current_mode; // Cevab? haz?rla
                publish_mission();                  // !!! SADECE GE?ERL?YSE YAYINLA !!!
            }
            else
            {
                response->mission_state = "GECERSIZ";
                // Burada publish_mission() ?a??rm?yoruz, b?ylece sistemin modu bozulmuyor.
            }
        }

	void topic_callback(const std_msgs::msg::String::SharedPtr message)
	{
	   std::string new_mode = message->data;

	   if(new_mode == "DOLASIM" || new_mode == "KAMIKAZE" || new_mode == "KILITLENME")
	   {
	      current_mode = new_mode;
	      publish_mission();
       	   }
	}

	void publish_mission()
	{
	   auto message = std_msgs::msg::String();
       	   message.data = current_mode;
	   publisher->publish(message);
	}
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    RCLCPP_INFO(rclcpp::get_logger("mission_control_node"), "The node was started...");
    rclcpp::spin(std::make_shared<MissionControlNode>());
    rclcpp::shutdown();

    return 0;
}
