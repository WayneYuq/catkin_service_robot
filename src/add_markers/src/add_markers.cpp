#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include "nav_msgs/Odometry.h"


class Markerhandle
{
public:
  Markerhandle()
  {
    marker_sub_ = n_.subscribe("odom", 100, &Markerhandle::odom_callback, this);
    marker_pub_ = n_.advertise<visualization_msgs::Marker>("visualization_marker", 1);
    x_list_[0] = 3;
    x_list_[1] = 0;
    x_list_[2] = -1;
    y_list_[0] = -1;
    y_list_[1] = 0;
    y_list_[2] = 2;
    color_a_[0] = 1;
    color_a_[1] = 0;
    color_a_[2] = 1;
    step_ = 0;
    shape_ = visualization_msgs::Marker::ARROW;
  };

  void odom_callback(const nav_msgs::Odometry msg);

private:
  int x_list_[3];
  int y_list_[3];
  int color_a_[3];
  int step_;
  ros::NodeHandle n_;
  ros::Subscriber marker_sub_;
  ros::Publisher marker_pub_;
  uint32_t shape_;
};


int main( int argc, char** argv )
{
  ros::init(argc, argv, "basic_shapes");
  Markerhandle markerhandle;
  
  ros::spin();
}

void Markerhandle::odom_callback(const nav_msgs::Odometry msg)
{
  if (ros::ok())
  {
    visualization_msgs::Marker marker;
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "map";
    marker.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "basic_shapes";
    marker.id = 0;

    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    marker.type = shape_;

    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
    marker.action = visualization_msgs::Marker::ADD;

    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
    marker.pose.position.x = x_list_[step_];
    marker.pose.position.y = y_list_[step_];
    marker.pose.position.z = 0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 0.2;
    marker.scale.y = 0.2;
    marker.scale.z = 0.2;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 0.0f;
    marker.color.g = 0.0f;
    marker.color.b = 1.0f;
    marker.color.a = color_a_[step_];

    marker.lifetime = ros::Duration();

    // Publish the marker
    while (marker_pub_.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }
    marker_pub_.publish(marker);
    if ( step_ == 0
      && fabs(msg.pose.pose.position.x - x_list_[0]) < 0.3
      && fabs(msg.pose.pose.position.y - y_list_[0]) < 0.3)
    {
      ROS_INFO("Marker has been picked up!");
      step_++;
    }
    if ( step_ == 1
      && fabs(msg.pose.pose.position.x - x_list_[2]) < 0.4
      && fabs(msg.pose.pose.position.y - y_list_[2]) < 0.4)
    {
      ROS_INFO("Marker has been droped off!");
      step_++;
    }
  }
}

