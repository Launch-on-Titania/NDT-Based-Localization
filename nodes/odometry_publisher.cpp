#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
#include <tf/transform_listener.h>
#include <tf/transform_datatypes.h>
#include <iostream>
#include <fstream>

int main(int argc, char** argv){

 std::ofstream outfile;
  outfile.open("track.txt",std::ios::out);
  std::ofstream utm_outfile;
  utm_outfile.open("/home/yyxunn/school/smartV/project/team1_track_tum.txt", std::ios::out);
  // if (!outfile.is_open())
  // {
  //   std::cout<<std::endl<<"!is_open"<<std::endl;
  // }
  // else
  // {
  //   std::cout<<std::endl<<"is open"<<std::endl;
  // }


  ros::init(argc, argv, "odom_pub");

  ros::NodeHandle n;
  ros::Publisher odom_pub = n.advertise<nav_msgs::Odometry>("odom", 100);
  tf::TransformListener listener;

  ros::Rate r(100.0);
  while(n.ok()){

    ros::spinOnce();             
      // check for incoming messages
    
    tf::StampedTransform transform;
    try{
      listener.lookupTransform("/map", "/base_link",  
                               ros::Time(0), transform);
    }
    catch (tf::TransformException ex){
      std::cout<<ex.what();
      ros::Duration(1.0).sleep();
    }

    
    utm_outfile<<transform.stamp_<<" "<<transform.getOrigin().x()<<" "<<transform.getOrigin().y()<<" "
    <<transform.getOrigin().z()<<" "<<transform.getRotation().x()<<" "<<transform.getRotation().y()<<" "
    <<transform.getRotation().z()<<" "<<transform.getRotation().w()<<std::endl;

   

    //next, we'll publish the odometry message over ROS
    nav_msgs::Odometry odom;
    odom.header.stamp = transform.stamp_;
    odom.header.frame_id = "map";

  

    //set the position
    
    odom.pose.pose.position.x = transform.getOrigin().x();
    odom.pose.pose.position.y = transform.getOrigin().y();
    odom.pose.pose.position.z = transform.getOrigin().z();
    tf::quaternionTFToMsg(transform.getRotation(), odom.pose.pose.orientation) ;

    outfile<<transform.getOrigin().x()<<", "<<transform.getOrigin().y()<<std::endl;

    //set the velocity
    odom.child_frame_id = "base_link";
    odom.twist.twist.linear.x = 0;
    odom.twist.twist.linear.y = 0;
    odom.twist.twist.angular.z = 0;

    //publish the message
    odom_pub.publish(odom);

    
    r.sleep();
  }

  outfile.close();
  utm_outfile.close();
  std::cout<<"done."<<std::endl;
  return 0;
}