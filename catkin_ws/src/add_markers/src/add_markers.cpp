#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <nav_msgs/Odometry.h>


class Sub_Pub
{
private:
ros::Publisher marker_pub;
ros::Subscriber sub;
int count;

public:

Sub_Pub(ros::NodeHandle &n)
{
        marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
        sub = n.subscribe("/odom", 2, &Sub_Pub::manageMarker,this);
        count=0;
	ROS_INFO("Initialized Sub_Pub instance");
}


void displayMarker(double x, double y, double w)
{
    //ROS_INFO("Trying to display Marker");
    // Set our initial shape type to be a cube
    uint32_t shape = visualization_msgs::Marker::CUBE;
    visualization_msgs::Marker marker;
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "map";
    marker.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "add_markers";
    marker.id = 0;

    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    marker.type = shape;

    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
    marker.action = visualization_msgs::Marker::ADD;

    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
    marker.pose.position.x = x;
    marker.pose.position.y = y;
    marker.pose.position.z = 0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = w;

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 0.5;
    marker.scale.y = 0.5;
    marker.scale.z = 0.5;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 1.0f;
    marker.color.g = 0.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;

    marker.lifetime = ros::Duration();

    // Publish the marker
    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
       // return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }
    marker_pub.publish(marker);

    
    if(count==0)
    {
    ros::Duration(5.0).sleep();
    ROS_INFO("Sleeping for 5 seconds");
    marker.action = visualization_msgs::Marker::DELETE;
    marker_pub.publish(marker);
    ROS_INFO("Deleted Marker");
    count++;
    }

}


void manageMarker(const nav_msgs::Odometry::ConstPtr& pos)
{
	//ROS_INFO("In callback function");
	double x = pos->pose.pose.position.x;
	double y = pos->pose.pose.position.y;
	double w = pos->pose.pose.orientation.w;
   	double tolerance = 0.55;
	if(count==0)
	{
		//if((x<=1.0+tolerance && x>=1.0-tolerance) && (y <= 2.5+tolerance && y>=2.5-tolerance) && (w <= 1.0+tolerance && w>=1.0-tolerance))
		if((x<=1.0+tolerance && x>=1.0-tolerance) && (y <= 2.5+tolerance && y>=2.5-tolerance))
		{
		ROS_INFO("found a match!");
		displayMarker(x,y,w);
		
		}
	}

	if(count==1)
	{
		//if((x<=4.0+tolerance && x>=4.0-tolerance) && (y <= 1.5+tolerance && y>=1.5-tolerance) && (w <= 3.0+tolerance && w>=3.0-tolerance))
		  if((x<=4.0+tolerance && x>=4.0-tolerance) && (y <= 1.5+tolerance && y>=1.5-tolerance))
		displayMarker(x,y,w);
		
	}
}

};


int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  Sub_Pub inst(n);
  //ros::Rate r(1);
  //r.sleep();
  ros::spin();
}
