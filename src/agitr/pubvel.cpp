// This program publishes randomly/generated velocity
// messages for Turtlesim
#include <ros/ros.h>
#include <geometry_msgs/Twist.h> // For geometry_msgs::Twist
#include <stdlib.h> // For rand() and RAND_MAX
#include <agitr/Pause.h>

ros::Publisher *pub;


void stopReciever(const agitr::Pause& msgIn){
	geometry_msgs::Twist msgGo;
	int answer = msgIn.x;
	if (answer=1){
		srand(time(0));
		ros::Rate rate(2);
		while(ros::ok() && answer >= 1){
			msgGo.linear.x = 3;
			msgGo.angular.z = 2*double(rand())/double(RAND_MAX)-1;
			pub-> publish(msgGo);
			ROS_INFO_STREAM(" I publish: " << msgGo.linear.x << " and " << msgGo.angular.z);
			rate.sleep();
			}
		}
	else if (answer=0){
		ros::Rate rate(2);
		int mark = 0;
		while (mark < 2){
			msgGo.linear.x = -5;
			msgGo.angular.z = 4;
			pub-> publish(msgGo);
			ROS_INFO_STREAM(" It should be turning. I publish: " << msgGo.linear.x << " and " << msgGo.angular.z);
			++mark;
			rate.sleep();
			}
		}
	}

int main (int argc, char **argv) {
	ros::init(argc, argv, "pubvel");
	ros::NodeHandle nh;

	pub = new ros::Publisher(nh.advertise<geometry_msgs::Twist>
	("turtle1/cmd_vel", 1000));

	ros::Subscriber sub=nh.subscribe("agitr/Pause", 1000, & stopReciever);	
	ros::spin();
	ROS_INFO_STREAM(" I publish:anyhing????");
	delete pub;
}

