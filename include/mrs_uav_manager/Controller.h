#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <ros/ros.h>

#include <mrs_msgs/AttitudeCommand.h>
#include <mrs_msgs/ControllerStatus.h>
#include <mrs_msgs/PositionCommand.h>
#include <mrs_msgs/AttitudeCommand.h>
#include <mrs_msgs/UavState.h>

namespace mrs_uav_manager
{

// parameters of the propulsion thrust curve
// T = A*sqrt(F) + B
// T is within [0, 1]
// F is in Newtons
struct MotorParams
{
  double hover_thrust_a;
  double hover_thrust_b;
};

class Controller {
public:
  virtual ~Controller(void) {
  }

  // initialize() is called once for every controller
  // * the run time is not limited
  virtual void initialize(const ros::NodeHandle &parent_nh, std::string name, std::string name_space, const mrs_uav_manager::MotorParams motor_params,
                          const double uav_mass, const double g) = 0;

  // activate() is called before the controllers output will be used
  // * the last command of previously used controller is passed, so mass ans disturbance estimates can be shared
  // * it should not take much time (within miliseconds)
  virtual bool activate(const mrs_msgs::AttitudeCommand::ConstPtr &cmd) = 0;

  // deactivate() is called after before the controller is stopped being used
  // * turn of any ros::Timers and threads (which should not be used anymore)
  virtual void deactivate(void) = 0;

  // this may be called to reset the controllers disturbance estimators, for safety reasons (typically in failsafe)
  virtual void resetDisturbanceEstimators(void) = 0;

  // update() is called with every UavState update
  // * it should not take long to evaluate
  virtual const mrs_msgs::AttitudeCommand::ConstPtr update(const mrs_msgs::UavState::ConstPtr &       uav_state,
                                                           const mrs_msgs::PositionCommand::ConstPtr &reference) = 0;

  // getStatus()
  // * self-explanatory
  virtual const mrs_msgs::ControllerStatus getStatus() = 0;

  // switchOdometrySource() is called during every switch of reference frames
  // * the new UavState (which will come in the next update()) is passed
  // * recalculate internal states from old frame to the new one
  virtual void switchOdometrySource(const mrs_msgs::UavState::ConstPtr &msg) = 0;
};
}  // namespace mrs_uav_manager

#endif
