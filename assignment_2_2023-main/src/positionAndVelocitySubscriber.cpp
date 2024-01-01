#include "ros/ros.h"
#include "std_msgs/String.h"
#include <assignment_2_2023/PlanningAction.h>
#include "assignment_2_2023/Parameters.h"
#include "assignment_2_2023/LastTarget.h"
#include <geometry_msgs/Point.h>
/**
 * This tutorial demonstrates simple receipt of messages over the ROS system.
 */

 float pos_x,pos_y,vel_x,vel_z;
assignment_2_2023::LastTarget lastTarget;
float lastPosition_x;
float lastPosition_y;
void chatterCallback(const assignment_2_2023::Parameters::ConstPtr& msg)
{

pos_x= msg->pos_x;
pos_y= msg->pos_y;
vel_x= msg->vel_x;
vel_z= msg->vel_z;

  ROS_INFO("I heard pos x: [%f], pos y: [%f] , vel x: [%f] ,vel z: [%f] ",
  	 pos_x,
  	 pos_y,
  	 vel_x,
  	 vel_z);
 ROS_INFO("distance from target x: %f y:%f", (pos_x-lastPosition_x),(pos_y-lastPosition_y));
  	 
}


int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "listener");
  ros::NodeHandle n;
  ros::ServiceClient client = n.serviceClient<assignment_2_2023::LastTarget>("/lastTarget");
  

	
	

	client.waitForExistence();
	client.call(lastTarget);
	lastPosition_x= lastTarget.response.target_pose.pose.position.x;
	lastPosition_y= lastTarget.response.target_pose.pose.position.y;
	


 
  ros::Subscriber sub = n.subscribe("robot/parameters", 1, chatterCallback);
  

  

  


 
  ros::spin();

  return 0;
}
