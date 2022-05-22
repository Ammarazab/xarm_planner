#include "excution.cpp"

int main(int argc, char **argv)
{

	// ros init
	ros::init(argc, argv, "xarm_simple_planner_client");

	// declare func
	excution exc;

	// joint-space planning target
	std::vector<double> joint_trgt = {-0.890118, 0.68, -1.553, 1.64061, 1.16937, 1.29154};

	// Cartesian straight line planning target or Cartesian-space point-to-point planning target
	geometry_msgs::Pose landptp_target;
	target1.position.x = 0.3;
	target1.position.y = -0.1;
	target1.position.z = 0.2;

	target1.orientation.x = 1;
	target1.orientation.y = 0;
	target1.orientation.z = 0;
	target1.orientation.w = 0;

	// joint-space planning request
	exc.joint_target(joint_trgt);

	// Cartesian straight line planning request or Cartesian-space point-to-point planning request
	exc.linear_target(landptp_target);
	exc.ptop_target(landptp_target);

	return 0;
}
