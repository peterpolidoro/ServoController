// ----------------------------------------------------------------------------
// ServoController.h
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#ifndef SERVO_CONTROLLER_H
#define SERVO_CONTROLLER_H
#include <ArduinoJson.h>
#include <JsonStream.h>
#include <Array.h>
#include <Vector.h>
#include <ConstantVariable.h>
#include <Functor.h>

#include <PCA9685.h>

#include <EventController.h>

#include <ModularServer.h>
#include <ModularDeviceBase.h>

#include "ServoController/Constants.h"


class ServoController : public ModularDeviceBase, public PCA9685
{
public:
  ServoController();
  virtual void setup();

  virtual size_t getChannelCount();

  void enableAll();
  void disableAll();

  void setChannelPulseDuration(size_t channel,
    uint16_t pulse_duration);
  void setAllChannelsPulseDuration(uint16_t pulse_duration);

  void rotateTo(size_t channel,
    double angle);
  void rotateAllTo(double angle);
  void rotateBy(size_t channel,
    double angle);
  void rotateAllBy(double angle);

protected:
  void addPwm(size_t channel,
    long delay,
    long period,
    long on_duration,
    long count,
    const Functor1<int> & start_pulse_functor,
    const Functor1<int> & stop_pulse_functor,
    const Functor1<int> & start_pwm_functor,
    const Functor1<int> & stop_pwm_functor);

  // Handlers
  virtual void setChannelCountHandler();

private:
  modular_server::Pin pins_[servo_controller::constants::PIN_COUNT_MAX];

  modular_server::Property properties_[servo_controller::constants::PROPERTY_COUNT_MAX];
  modular_server::Parameter parameters_[servo_controller::constants::PARAMETER_COUNT_MAX];
  modular_server::Function functions_[servo_controller::constants::FUNCTION_COUNT_MAX];
  modular_server::Callback callbacks_[servo_controller::constants::CALLBACK_COUNT_MAX];

  uint16_t pulse_durations_[servo_controller::constants::CHANNEL_COUNT_MAX];

  EventController<servo_controller::constants::EVENT_COUNT_MAX> event_controller_;
  EventIdPair event_id_pairs_[servo_controller::constants::CHANNEL_COUNT_MAX];

  long angleToPulseDuration(size_t channel,
    double angle);

  // Handlers
  void enableAllHandler(modular_server::Pin * pin_ptr);
  void disableAllHandler(modular_server::Pin * pin_ptr);
  void setChannelPulseDurationHandler();
  void setAllChannelsPulseDurationHandler();
  void rotateToHandler();
  void rotateAllToHandler();
  void rotateByHandler();
  void rotateAllByHandler();

};

#endif
