#include <ros/ros.h>
#include <chatbot_node/reply_msg.h>
#include <counter_node/counter.h>
#include <message_ui/sent_msg.h>
#include <arithmetic_node/arithmetic_reply.h>

int num_reply_msg = 0;
int num_sent_msg = 0;

ros::Time last_sent_msg_time;
ros::Time last_reply_msg_time;

ros::Subscriber reply_msg_sub;
ros::Subscriber arithmetic_reply_msg_sub;
ros::Subscriber sent_msg_sub;

ros::ServiceServer service;

void sent_msg_callback(const message_ui::sent_msg msg)
{
	num_sent_msg++;
	last_sent_msg_time = msg.header.stamp;
}

void reply_msg_callback(const chatbot_node::reply_msg msg)
{
	num_reply_msg++;
	last_reply_msg_time = msg.header.stamp;
}

void arithmetic_reply_msg_callback(const arithmetic_node::arithmetic_reply msg)
{
	num_reply_msg++;
	last_reply_msg_time = msg.header.stamp;
}
bool counter(counter_node::counter::Request& req, counter_node::counter::Response& res)
{
    if (req.req_id == 0) {
        res.reply = num_reply_msg + num_sent_msg;
    } 
    if (req.req_id == 1) {
        res.reply = num_reply_msg;
    }
    if (req.req_id == 2) {
        res.reply = num_sent_msg;
    }
    if (req.req_id == 3) {
        if (num_reply_msg != 0) {
            res.reply = (ros::Time::now() - last_reply_msg_time).toSec();
        } else {
            res.reply = 0;
        }
    }
    if (req.req_id == 4) {
        if (num_reply_msg != 0) {
            res.reply = (ros::Time::now() - last_sent_msg_time).toSec();
        } else {
            res.reply = 0;
        }
    }

	ROS_INFO("%f", res.reply);
    return true;
}

int main(int argc, char **argv) {

    ros::init(argc, argv, "counter_node");
    ros::NodeHandle nh;

    service = nh.advertiseService("message_counter", counter);

    reply_msg_sub = nh.subscribe("reply_msg", 1000, reply_msg_callback);
    sent_msg_sub = nh.subscribe("sent_msg", 1000, sent_msg_callback);
    arithmetic_reply_msg_sub = nh.subscribe("arithmetic_reply", 1000, arithmetic_reply_msg_callback);

    ros::Rate loop_rate(20);
    last_sent_msg_time = ros::Time::now();
    last_reply_msg_time = ros::Time::now();


    while(ros::ok()) {
    ros::spinOnce();
    loop_rate.sleep();
    }

    return 0;
}