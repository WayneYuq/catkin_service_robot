#!/bin/sh

xterm -e " source /opt/ros/kinetic/setup.bash" &
sleep 5
xterm -e " source /home/robond/catkin_service_robot/devel/setup.bash " &
sleep 5
xterm -e " roslaunch turtlebot_gazebo turtlebot_world.launch" &
sleep 5
xterm -e " roslaunch turtlebot_gazebo gmapping_demo.launch" &
sleep 5
xterm -e " roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 5
xterm -e " roslaunch turtlebot_teleop keyboard_teleop.launch"
