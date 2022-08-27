#include <ros/ros.h>
#include <chatbot_node/reply_msg.h>
#include <message_ui/sent_msg.h>
#include <arithmetic_node/arithmetic_reply.h>
#include <counter_node/counter.h>
#include <string>

using namespace std;
ros::Publisher reply_pub;

void chatbotCallback(const message_ui::sent_msg::ConstPtr& msg)
{
    ros::NodeHandle nh;
    std::string user_name;
    chatbot_node::reply_msg reply; 

    if (msg->message == "Hello") {
        std::string result;

        nh.getParam("/user_name", user_name);

        result = "Hello, " + user_name;
        reply.message = result;
        reply_pub.publish(reply);        
    } else if (msg->message == "What is your name?") {
        reply.message = "My name is MRSD Siri";
        reply_pub.publish(reply); 
    } else if (msg->message == "How are you?") {
        reply.message = "I am fine, thank you.";
        reply_pub.publish(reply); 
    } else {
        std::cout << msg->message << std::endl;
    }
}

int main(int argc, char **argv) {

    ros::init(argc, argv, "chatbot_node");
    ros::NodeHandle nh;

    reply_pub = nh.advertise<chatbot_node::reply_msg>("reply_msg", 1000);
    ros::Rate loop_rate(20);

    ros::Subscriber sent_sub = nh.subscribe("sent_msg", 1000, chatbotCallback);
    ros::spin();

    return 0;
}