#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/string.hpp"
#include "example_interfaces/msg/int64.hpp"

using namespace std::placeholders;

int counter_ = 0;

class NumberCounter : public rclcpp::Node 
{
public:
    NumberCounter() : Node("number_counter")
    {
        subscriber_ = this->create_subscription<example_interfaces::msg::Int64>(
            "number", 
            10, 
            std::bind(&NumberCounter::callbackNumberPublisher, this, _1));
        RCLCPP_INFO(this->get_logger(), "Counter has been started.");
    }
 
private:
    void callbackNumberPublisher(const example_interfaces::msg::Int64::SharedPtr msg) {
        RCLCPP_INFO(this->get_logger(), "msg: %ld", msg->data);
        RCLCPP_INFO(this->get_logger(), "count: %d", counter_);
        counter_++;
    }
    rclcpp::Subscription<example_interfaces::msg::Int64>::SharedPtr subscriber_;
};
 
int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<NumberCounter>(); 
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
