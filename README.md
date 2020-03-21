# catkin_service_robot
Picked-up service robot.

## Configuration requires
- A 2D Laser, providing sensor_msgs/LaserScan messages
- Odometry sensors, providing nav_msgs/Odometry messages

## Usage
1. Change working directory to top level and `catkin_make`
2. `source devel/setup.bash`
3. `sh src/scripts/home_service.sh`
