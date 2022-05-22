
#include "ros/ros.h"
#include <std_msgs/Bool.h>
#include <xarm_planner/pose_plan.h>
#include <xarm_planner/joint_plan.h>
#include <xarm_planner/exec_plan.h>
#include <xarm_planner/single_straight_plan.h>
#include <stdlib.h>
#include <vector>
// if you want to make joint plan
bool request_plan(ros::ServiceClient &client, xarm_planner::joint_plan &srv)
{
    if (client.call(srv))
    {
        return srv.response.success;
    }
    else
    {
        ROS_ERROR("Failed to call service joint_plan");
        return false;
    }
}
// if you want to make pose plan
bool request_plan(ros::ServiceClient &client, xarm_planner::pose_plan &srv)
{
    if (client.call(srv))
    {
        return srv.response.success;
    }
    else
    {
        ROS_ERROR("Failed to call service pose_plan");
        return false;
    }
}
// if you want to make straight plan
bool request_plan(ros::ServiceClient &client, xarm_planner::single_straight_plan &srv)
{
    if (client.call(srv))
    {
        return srv.response.success;
    }
    else
    {
        ROS_ERROR("Failed to call service single_straight_plan");
        return false;
    }
}
// ececute the plan
bool request_exec(ros::ServiceClient &client, xarm_planner::exec_plan &srv)
{
    if (client.call(srv))
    {
        return srv.response.success;
    }
    else
    {
        ROS_ERROR("Failed to call service exec_plan");
        return false;
    }
}

class excution
{
     ros::NodeHandle nh;
public:
    double joint_target(std::vector<double> &joint_target)
    {

       

        // service client init for all type of joint
        ros::ServiceClient client = nh.serviceClient<xarm_planner::joint_plan>("xarm_joint_plan");

        // service client init for excute blocking
        ros::ServiceClient client_exec = nh.serviceClient<xarm_planner::exec_plan>("xarm_exec_plan");
        // publish excute non-blocking
        ros::Publisher exec_pub = nh.advertise<std_msgs::Bool>("xarm_planner_exec", 10);

        // DECLARATION
        std_msgs::Bool msg;
        xarm_planner::joint_plan srv;

        // xarm_planner::single_straight_plan srv3;
        xarm_planner::exec_plan srv_exec;

        // sleep time
        double slp_t = 0.5;
        //********************************************************************

        srv.request.target = joint_target;
        if (request_plan(client, srv))
        {
            ROS_INFO("Plan SUCCESS! Executing Joint Plan \n ");
            srv_exec.request.exec = true;
            request_exec(client_exec, srv_exec);
        }
        ros::Duration(slp_t).sleep();
    }
    float linear_target(const geometry_msgs::Pose &linear_target)
    {

       

        // the home target given as a joint
        ros::ServiceClient client22 = nh.serviceClient<xarm_planner::pose_plan>("xarm_straight_plan");
        xarm_planner::single_straight_plan srv22;

        // service client init for excute blocking
        ros::ServiceClient client_exec = nh.serviceClient<xarm_planner::exec_plan>("xarm_exec_plan");
        // publish excute non-blocking
        ros::Publisher exec_pub = nh.advertise<std_msgs::Bool>("xarm_planner_exec", 10);

        // DECLARATION
        std_msgs::Bool msg;
        xarm_planner::exec_plan srv_exec;

        // sleep time
        double slp_t = 0.5;

        //********************************************************************

        srv22.request.target = linear_target;
        if (request_plan(client22, srv22))
        {   printf("ready \n");
            ROS_INFO("Plan SUCCESS! Executing Linear movement ");
            printf("done \n");
            
            srv_exec.request.exec = true;
            printf("done2");

            request_exec(client_exec, srv_exec);
        }
        ros::Duration(slp_t).sleep();
    }

    float ptop_target(const geometry_msgs::Pose &ptop_target)
    {

        

        ros::ServiceClient client2 = nh.serviceClient<xarm_planner::pose_plan>("xarm_pose_plan");
        ros::ServiceClient client_exec = nh.serviceClient<xarm_planner::exec_plan>("xarm_exec_plan");

        ros::Publisher exec_pub = nh.advertise<std_msgs::Bool>("xarm_planner_exec", 10);
        std_msgs::Bool msg;

        xarm_planner::pose_plan srv2;
        xarm_planner::exec_plan srv_exec;

        double slp_t = 0.5;

        //********************************************************************

        srv2.request.target = ptop_target;
        if (request_plan(client2, srv2))
        {
            ROS_INFO("Plan SUCCESS! Executing Point to Point movement ");
            srv_exec.request.exec = true;
            request_exec(client_exec, srv_exec);
        }
        ros::Duration(slp_t).sleep();
    }
};