#include <ros/ros.h>
#include <chatbot_node/reply_msg.h>
#include <counter_node/counter.h>
#include <message_ui/sent_msg.h>
#include <arithmetic_node/arithmetic_reply.h>
#include <typeinfo>
#include <string>

using namespace std;
ros::Publisher apub;
std::string arithmetic_msg;

void arithmeticCallback(const message_ui::sent_msg msg)
{
    arithmetic_node::arithmetic_reply ar;
    ar.header.stamp = ros::Time::now();

    std::ostringstream os;
	os << msg.message.c_str();  
    arithmetic_msg = os.str();

    int op1;
    int op2;
    char opt;
    std::stringstream s(arithmetic_msg);
    
    s >> op1;
    s >> opt;
    s >> op2;

    if (opt == '+'){
        
        float ans = op1 + op2;
        
        ar.answer = ans;
        ar.oper_type = "Add";
        ar.time_received = ar.header.stamp.toSec();
        ar.time_answered = ros::Time::now().toSec();
        ar.process_time = ar.time_answered - ar.time_received;
        apub.publish(ar);
    } else if (opt == '-') {
        float ans = op1 - op2;
        
        ar.answer = ans;
        ar.oper_type = "Subtract";
        ar.time_received = ar.header.stamp.toSec();
        ar.time_answered = ros::Time::now().toSec();
        ar.process_time = ar.time_answered - ar.time_received;
        apub.publish(ar);
    } else if (opt == '*') {
        float ans = op1 * op2;
        
        ar.answer = ans;
        ar.oper_type = "Multiply";
        ar.time_received = ar.header.stamp.toSec();
        ar.time_answered = ros::Time::now().toSec();
        ar.process_time = ar.time_answered - ar.time_received;
        apub.publish(ar);
    } else if (opt == '/') {
        float ans = op1 / op2;
        
        ar.answer = ans;
        ar.oper_type = "Divide";
        ar.time_received = ar.header.stamp.toSec();
        ar.time_answered = ros::Time::now().toSec();
        ar.process_time = ar.time_answered - ar.time_received;
        apub.publish(ar);
    }
}    

int main(int argc, char** argv) {

    ros::init(argc, argv, "arithmetic_node");
    ros::NodeHandle nh;
    ros::Rate loop_rate(20);

    apub = nh.advertise<arithmetic_node::arithmetic_reply>("arithmetic_reply", 1000);

    ros::Subscriber asub = nh.subscribe("sent_msg", 1000, arithmeticCallback);
    ros::spin();

    return 0;
}