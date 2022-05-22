# Package Introduction
&ensp;&ensp;This package is intended to provide users a demo programming interface to use moveit!, instead of just using the GUI. To use the API better, users are encouraged to go through [Moveit tutorial](http://docs.ros.org/kinetic/api/moveit_tutorials/html/).  
&ensp;&ensp;Inside the package, 'xarm_simple_planner' is just a basic implementation of the Move_group interface, if higher level configurations (constraints, switch kinematic solver or planners, etc) are needed, user can fully explore Moveit abilities and implement a sofisticated version.  
&ensp;&ensp;For simplified Chinese instructions: [简体中文版](./ReadMe_cn.md)   

# Usage
If you want to know the package how it work you should read (./ReadMe.md), So in this ReadMe file will talk about the 2 files only execution.cpp and demp.cpp

## Open the execution.cpp:
in this file you will see the class called excution this is a main class will be start talk about 
```bash
   roslaunch xarm_planner xarm_planner_rviz_sim.launch robot_dof:=<7|6|5> add_gripper:=<true|false> add_vacuum_gripper:=<true|false>
```
