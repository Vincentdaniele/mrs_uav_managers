#include <ros/ros.h>

#include <mrs_uav_manager/Tracker.h>

namespace mrs_uav_manager
{

/* //{ class NullTracker */

class NullTracker : public mrs_uav_manager::Tracker {

public:
  virtual void initialize(const ros::NodeHandle &parent_nh, mrs_uav_manager::SafetyArea_t const *safety_area);
  virtual bool activate(const mrs_msgs::PositionCommand::ConstPtr &cmd);
  virtual void deactivate(void);

  virtual const mrs_msgs::PositionCommand::ConstPtr update(const nav_msgs::Odometry::ConstPtr &msg);
  virtual const mrs_msgs::TrackerStatus             getStatus();
  virtual const std_srvs::SetBoolResponse::ConstPtr enableCallbacks(const std_srvs::SetBoolRequest::ConstPtr &cmd);
  virtual void                                      switchOdometrySource(const nav_msgs::Odometry::ConstPtr &msg);

  virtual const mrs_msgs::Vec4Response::ConstPtr goTo(const mrs_msgs::Vec4Request::ConstPtr &cmd);
  virtual const mrs_msgs::Vec4Response::ConstPtr goToRelative(const mrs_msgs::Vec4Request::ConstPtr &cmd);
  virtual const mrs_msgs::Vec1Response::ConstPtr goToAltitude(const mrs_msgs::Vec1Request::ConstPtr &cmd);
  virtual const mrs_msgs::Vec1Response::ConstPtr setYaw(const mrs_msgs::Vec1Request::ConstPtr &cmd);
  virtual const mrs_msgs::Vec1Response::ConstPtr setYawRelative(const mrs_msgs::Vec1Request::ConstPtr &cmd);

  virtual bool goTo(const mrs_msgs::TrackerPointStampedConstPtr &msg);
  virtual bool goToRelative(const mrs_msgs::TrackerPointStampedConstPtr &msg);
  virtual bool goToAltitude(const std_msgs::Float64ConstPtr &msg);
  virtual bool setYaw(const std_msgs::Float64ConstPtr &msg);
  virtual bool setYawRelative(const std_msgs::Float64ConstPtr &msg);

  virtual const std_srvs::TriggerResponse::ConstPtr hover(const std_srvs::TriggerRequest::ConstPtr &cmd);

  virtual const mrs_msgs::TrackerConstraintsResponse::ConstPtr setConstraints(const mrs_msgs::TrackerConstraintsRequest::ConstPtr &cmd);

private:
  ros::NodeHandle nh_;
  bool            is_active         = false;
  bool            is_initialized    = false;
  bool            callbacks_enabled = false;
};

//}

// | ------------------- trackers interface ------------------- |

/* //{ initialize() */

void NullTracker::initialize(const ros::NodeHandle &parent_nh, [[maybe_unused]] mrs_uav_manager::SafetyArea_t const *safety_area) {

  ros::NodeHandle nh_(parent_nh, "null_tracker");

  ros::Time::waitForValid();

  is_initialized = true;

  ROS_INFO("[NullTracker]: initialized");
}

//}

/* //{ activate() */

bool NullTracker::activate([[maybe_unused]] const mrs_msgs::PositionCommand::ConstPtr &cmd) {

  ROS_INFO("[NullTracker]: activated");
  is_active = true;
  return true;
}

//}

/* //{ deactivate() */

void NullTracker::deactivate(void) {

  ROS_INFO("[NullTracker]: deactivated");
  is_active = false;
}

//}

/* switchOdometrySource() //{ */

void NullTracker::switchOdometrySource([[maybe_unused]] const nav_msgs::Odometry::ConstPtr &msg) {
}

//}

/* //{ update() */

const mrs_msgs::PositionCommand::ConstPtr NullTracker::update([[maybe_unused]] const nav_msgs::Odometry::ConstPtr &msg) {

  return mrs_msgs::PositionCommand::Ptr();
}

//}

/* //{ getStatus() */

const mrs_msgs::TrackerStatus NullTracker::getStatus() {

  mrs_msgs::TrackerStatus tracker_status;

  tracker_status.active            = is_active;
  tracker_status.callbacks_enabled = callbacks_enabled;

  return tracker_status;
}

//}

/* //{ enableCallbacks() */

const std_srvs::SetBoolResponse::ConstPtr NullTracker::enableCallbacks(const std_srvs::SetBoolRequest::ConstPtr &cmd) {

  char                      message[100];
  std_srvs::SetBoolResponse res;

  if (cmd->data != callbacks_enabled) {

    callbacks_enabled = cmd->data;

    sprintf((char *)&message, "Callbacks %s", callbacks_enabled ? "enabled" : "disabled");

    ROS_INFO("[MpcTracker]: %s", message);

  } else {

    sprintf((char *)&message, "Callbacks were already %s", callbacks_enabled ? "enabled" : "disabled");
  }

  res.message = message;
  res.success = true;

  return std_srvs::SetBoolResponse::ConstPtr(new std_srvs::SetBoolResponse(res));
}

//}

// | -------------- setpoint topics and services -------------- |

/* //{ goTo() service */

const mrs_msgs::Vec4Response::ConstPtr NullTracker::goTo([[maybe_unused]] const mrs_msgs::Vec4Request::ConstPtr &cmd) {
  return mrs_msgs::Vec4Response::Ptr();
}

//}

/* //{ goTo() topic */

bool NullTracker::goTo([[maybe_unused]] const mrs_msgs::TrackerPointStampedConstPtr &msg) {
  return false;
}

//}

/* //{ goToRelative() topic */

const mrs_msgs::Vec4Response::ConstPtr NullTracker::goToRelative([[maybe_unused]] const mrs_msgs::Vec4Request::ConstPtr &cmd) {
  return mrs_msgs::Vec4Response::Ptr();
}

//}

/* //{ goToRelative() topic */

bool NullTracker::goToRelative([[maybe_unused]] const mrs_msgs::TrackerPointStampedConstPtr &msg) {
  return false;
}

//}

/* //{ goToAltitude() service */

const mrs_msgs::Vec1Response::ConstPtr NullTracker::goToAltitude([[maybe_unused]] const mrs_msgs::Vec1Request::ConstPtr &cmd) {
  return mrs_msgs::Vec1Response::Ptr();
}

//}

/* //{ goToAltitude() topic */

bool NullTracker::goToAltitude([[maybe_unused]] const std_msgs::Float64ConstPtr &msg) {
  return false;
}

//}

/* //{ setYaw() service */

const mrs_msgs::Vec1Response::ConstPtr NullTracker::setYaw([[maybe_unused]] const mrs_msgs::Vec1Request::ConstPtr &cmd) {
  return mrs_msgs::Vec1Response::Ptr();
}

//}

/* //{ setYaw() topic */

bool NullTracker::setYaw([[maybe_unused]] const std_msgs::Float64ConstPtr &msg) {
  return false;
}

//}

/* //{ setYawRelative() service */

const mrs_msgs::Vec1Response::ConstPtr NullTracker::setYawRelative([[maybe_unused]] const mrs_msgs::Vec1Request::ConstPtr &cmd) {
  return mrs_msgs::Vec1Response::Ptr();
}

//}

/* //{ setYawRelative() topic */

bool NullTracker::setYawRelative([[maybe_unused]] const std_msgs::Float64ConstPtr &msg) {
  return false;
}

//}

/* //{ hover() service */

const std_srvs::TriggerResponse::ConstPtr NullTracker::hover([[maybe_unused]] const std_srvs::TriggerRequest::ConstPtr &cmd) {
  return std_srvs::TriggerResponse::Ptr();
}

//}

/* //{ setConstraints() service */

const mrs_msgs::TrackerConstraintsResponse::ConstPtr NullTracker::setConstraints([[maybe_unused]] const mrs_msgs::TrackerConstraintsRequest::ConstPtr &cmd) {

  return mrs_msgs::TrackerConstraintsResponse::Ptr();
}

//}

}  // namespace mrs_uav_manager

#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(mrs_uav_manager::NullTracker, mrs_uav_manager::Tracker)
