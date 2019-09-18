#ifndef TRACKER_H_
#define TRACKER_H_

#include <ros/ros.h>

#include <mrs_msgs/PositionCommand.h>
#include <mrs_msgs/TrackerStatus.h>
#include <nav_msgs/Odometry.h>

#include <mrs_msgs/Vec1.h>
#include <mrs_msgs/Vec1Request.h>
#include <mrs_msgs/Vec1Response.h>

#include <mrs_msgs/Vec4.h>
#include <mrs_msgs/Vec4Request.h>
#include <mrs_msgs/Vec4Response.h>

#include <std_srvs/Trigger.h>
#include <std_srvs/TriggerRequest.h>
#include <std_srvs/TriggerResponse.h>

#include <std_srvs/SetBool.h>
#include <std_srvs/SetBoolRequest.h>
#include <std_srvs/SetBoolResponse.h>

#include <mrs_msgs/TrackerConstraints.h>
#include <mrs_msgs/TrackerConstraintsRequest.h>
#include <mrs_msgs/TrackerConstraintsResponse.h>

#include <std_msgs/Float64.h>

#include <mrs_msgs/TrackerPointStamped.h>

#include <Eigen/Eigen>

namespace mrs_uav_manager
{

typedef boost::function<bool(const double x, const double y, const double z)> isPointInSafetyArea3d_t;
typedef boost::function<bool(const double x, const double y)>                 isPointInSafetyArea2d_t;
typedef boost::function<double(void)>                                         getMaxHeight_t;
typedef boost::function<double(void)>                                         getMinHeight_t;

struct SafetyArea_t
{
  mrs_uav_manager::isPointInSafetyArea3d_t isPointInSafetyArea3d;
  mrs_uav_manager::isPointInSafetyArea2d_t isPointInSafetyArea2d;
  mrs_uav_manager::getMaxHeight_t          getMaxHeight;
  mrs_uav_manager::getMinHeight_t          getMinHeight;
  bool                                     use_safety_area;
};

class Tracker {

public:
  virtual ~Tracker(void) {
  }

  virtual void initialize(const ros::NodeHandle &parent_nh, mrs_uav_manager::SafetyArea_t const *safety_area) = 0;
  virtual bool activate(const mrs_msgs::PositionCommand::ConstPtr &cmd)                                       = 0;
  virtual void deactivate(void)                                                                               = 0;
  virtual void switchOdometrySource(const nav_msgs::Odometry::ConstPtr &msg)                                  = 0;

  virtual const mrs_msgs::PositionCommand::ConstPtr update(const nav_msgs::Odometry::ConstPtr &msg) = 0;
  virtual const mrs_msgs::TrackerStatus             getStatus()                                     = 0;

  virtual const mrs_msgs::Vec4Response::ConstPtr goTo(const mrs_msgs::Vec4Request::ConstPtr &cmd)           = 0;
  virtual const mrs_msgs::Vec4Response::ConstPtr goToRelative(const mrs_msgs::Vec4Request::ConstPtr &cmd)   = 0;
  virtual const mrs_msgs::Vec1Response::ConstPtr goToAltitude(const mrs_msgs::Vec1Request::ConstPtr &cmd)   = 0;
  virtual const mrs_msgs::Vec1Response::ConstPtr setYaw(const mrs_msgs::Vec1Request::ConstPtr &cmd)         = 0;
  virtual const mrs_msgs::Vec1Response::ConstPtr setYawRelative(const mrs_msgs::Vec1Request::ConstPtr &cmd) = 0;

  virtual const std_srvs::TriggerResponse::ConstPtr hover(const std_srvs::TriggerRequest::ConstPtr &cmd)           = 0;
  virtual const std_srvs::SetBoolResponse::ConstPtr enableCallbacks(const std_srvs::SetBoolRequest::ConstPtr &cmd) = 0;

  virtual bool goTo(const mrs_msgs::TrackerPointStampedConstPtr &msg)         = 0;
  virtual bool goToRelative(const mrs_msgs::TrackerPointStampedConstPtr &msg) = 0;
  virtual bool goToAltitude(const std_msgs::Float64ConstPtr &msg)             = 0;
  virtual bool setYaw(const std_msgs::Float64ConstPtr &msg)                   = 0;
  virtual bool setYawRelative(const std_msgs::Float64ConstPtr &msg)           = 0;

  virtual const mrs_msgs::TrackerConstraintsResponse::ConstPtr setConstraints(const mrs_msgs::TrackerConstraintsRequest::ConstPtr &constraints) = 0;
};
}  // namespace mrs_uav_manager

#endif
