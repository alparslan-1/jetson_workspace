#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <string>
#include <memory>

class VideoRecorderControlNode : public rclcpp::Node
{
public:
    VideoRecorderControlNode()
        : Node("video_recorder_control_node"), is_recording_(false)
    {
        // Constructor sadece node'u olu?turur, logic initialize() i?inde ba?lar.
        RCLCPP_INFO(this->get_logger(), "Video Recorder Control Node olusturuldu (Beklemede).");
    }

    // --- INITIALIZE (BA?LATMA FONKS?YONU) ---
    void initialize()
    {
        // 1. QoS AYARLARI (Referans koddaki gibi)
        // Reliable + Transient Local: Node ge? a??lsa bile son yay?nlanan modu (?rn: KAMIKAZE) hemen yakalar.
        rclcpp::QoS state_qos_profile(1);
        state_qos_profile.reliable();
        state_qos_profile.transient_local();
        state_qos_profile.keep_last(1);

        // 2. Publisher (Kay?t ba?lat/durdur komutu g?ndermek i?in)
        control_publisher_ = this->create_publisher<std_msgs::msg::String>("/kayit/kontrol", 10);

        // 3. Subscription (Modlar? dinlemek i?in)
        state_subscriber_ = this->create_subscription<std_msgs::msg::String>(
            "/success/lockon_success",
            state_qos_profile,
            std::bind(&VideoRecorderControlNode::state_callback, this, std::placeholders::_1)
        );

        RCLCPP_INFO(this->get_logger(), "Node initialize edildi. Dinleniyor: /success/lockon_success");
    }

private:
    bool is_recording_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr control_publisher_;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr state_subscriber_;

    // Komut g?nderme yard?mc?s?
    void publish_command(const std::string& cmd)
    {
        std_msgs::msg::String msg;
        msg.data = cmd;
        control_publisher_->publish(msg);
    }

    // --- BURASI D?NLEME VE KARAR YER? ---
    void state_callback(const std_msgs::msg::String::SharedPtr msg)
    {
        // 1. ADIM: Gelen veriyi 'current_state' de?i?kenine ata
        std::string current_state = msg->data;

        // Loglayal?m ki ne geldi?ini g?relim
        RCLCPP_INFO(this->get_logger(), "Algilanan Mod: '%s'", current_state.c_str());

        // 2. ADIM: 3 ?htimale g?re mant?k kur
        // ?htimaller: "KAMIKAZE", "KILITLENME", "DOLASIM"

        if (current_state == "KAMIKAZE" || current_state == "KILITLENME")
        {
            // E?er kay?t zaten a??k de?ilse ba?lat
            if (!is_recording_) {
                RCLCPP_WARN(this->get_logger(), "Saldiri Modu (%s) -> Kayit BASLATILIYOR!", current_state.c_str());
                publish_command("start");
                is_recording_ = true;
            }
        }
        else if (current_state == "DOLASIM")
        {
            // E?er kay?t a??ksa durdur
            if (is_recording_) {
                RCLCPP_INFO(this->get_logger(), "Normal Mod (%s) -> Kayit DURDURULUYOR.", current_state.c_str());
                publish_command("stop");
                is_recording_ = false;
            }
        }
        else
        {
            // Tan?ms?z bir mod gelirse (?rn: "ARM", "DISARM" vb.) sadece bilgi ver, i?lem yapma
            RCLCPP_DEBUG(this->get_logger(), "Islem yapilmayacak mod: %s", current_state.c_str());
        }
    }
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    
    // Node'u shared pointer ile olu?turup initialize ediyoruz
    auto node = std::make_shared<VideoRecorderControlNode>();
    node->initialize();
    
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
