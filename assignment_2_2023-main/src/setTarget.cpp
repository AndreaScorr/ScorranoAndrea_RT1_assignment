#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
//#include <actionlib_tutorials/FibonacciAction.h>
#include <assignment_2_2023/PlanningAction.h>
//from geometry_msgs.msg import Point
#include <geometry_msgs/Point.h>
#include "nav_msgs/Odometry.h"
#include "assignment_2_2023/Parameters.h"

float pos_x;
float pos_y;
float vel_x;
float vel_z;


void odomCallback(const nav_msgs::Odometry::ConstPtr &msg)
{
  // ROS_INFO("%s", msg->header.frame_id.c_str());
  // ROS_INFO("%f", msg->twist.twist.linear.x);
  ROS_INFO("[pose x: %f ,  pose y: %f ,  vel x: %f  vel z: %f]",
   msg->pose.pose.position.x,
   msg->pose.pose.position.x,
   msg->twist.twist.linear.x,
   msg->twist.twist.angular.z);
  
  pos_x=msg->pose.pose.position.x;
  pos_y=msg->pose.pose.position.x;
  vel_x=msg->twist.twist.linear.x;
  vel_z=msg->twist.twist.angular.z;
  
}


int main (int argc, char **argv)
{
  ros::init(argc, argv, "Planning");
  ros::NodeHandle nh;
  // create the action client
  // true causes the client to spin its own thread
  actionlib::SimpleActionClient<assignment_2_2023::PlanningAction> ac("/reaching_goal", true);

  ROS_INFO("Waiting for action server to start.");
  // wait for the action server to start
  ac.waitForServer(); //will wait for infinite time

  ROS_INFO("Action server started, sending goal.");
  // send a goal to the action
  assignment_2_2023::PlanningGoal goal;
  geometry_msgs::Point desired_position_;
/*  desired_position_.x = 20;
  desired_position_.y = 10;
  */
  
  ROS_INFO("inserire popsizione x");
  std::cin>>goal.target_pose.pose.position.x;
  
  
  ROS_INFO("inserire popsizione y");
  std::cin>>goal.target_pose.pose.position.y;
  
  
  //goal.target_pose.pose.position.x=5;
  //goal.target_pose.pose.position.y=5;
  ac.sendGoal(goal);

  ros::Subscriber sub = nh.subscribe("odom", 1, odomCallback);

  ros::Publisher pub2 = nh.advertise<assignment_2_2023::Parameters>("robot/parameters", 1);
  
  

while(ros::ok())
{
	assignment_2_2023::Parameters parameters;
  	parameters.pos_x=  pos_x;
  	parameters.pos_y = pos_y;
 	parameters.vel_x = vel_x;
  	parameters.vel_z = vel_z;
  	pub2.publish(parameters);
	ros::spinOnce();
	/*  
	ROS_INFO("cancellare il goal?  [1] yes [0] no ");
	bool answer;
	std::cin>>answer;	
	if(answer==1)
  	{
  		ac.cancelGoal();
  		break;
  	}*/	
}  
ac.cancelGoal();
  
	/*
  //wait for the action to return
  bool finished_before_timeout = ac.waitForResult(ros::Duration(30.0));

  if (finished_before_timeout)
  {
    actionlib::SimpleClientGoalState state = ac.getState();
    ROS_INFO("Action finished: %s",state.toString().c_str());
  }
  else
    ROS_INFO("Action did not finish before the time out.");
*/
  //exit
  return 0;
}
