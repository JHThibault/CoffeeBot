#ifndef LIGHTSWITCH_H
#define LIGHTSWITCH_H

#include <Arduino.h>
#include <Servo.h>

#define MOVE_DELAY 15
#define WAIT_DELAY 250



class LightSwitch {
private:
  Servo myservo;
  int off_position;
  int on_position;
  int neutral_position;
  int servoPin;
  boolean fliped = false;

public:
  LightSwitch();
  LightSwitch(int servoPin, int _on_position, int _off_position, int neutral_position, boolean _fliped);
  LightSwitch(int servoPin, int _on_position, int _off_position, int neutral_position);
  void turnOff();
  void turnOn();
  void moveOn();
  void moveOff();
  void moveNeutral();
  void wakeup();
  void standby();
};

#endif
