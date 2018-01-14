#include "LightSwitch.h"

using namespace std;




//<<constructor>>
LightSwitch::LightSwitch(){
  //defult constructor
}
LightSwitch::LightSwitch(int _servoPin, int _on_position, int _off_position, int _neutral_position){
  this->on_position = _on_position;
  this->off_position = _off_position;
  this->neutral_position = _neutral_position;
  this->servoPin = _servoPin;
  myservo.attach(this->servoPin);
  moveNeutral();
  printf("init servo\n");

}

LightSwitch::LightSwitch(int _servoPin, int _on_position, int _off_position, int _neutral_position, boolean _fliped){

  this->fliped = _fliped;
  this->on_position = _on_position;
  this->off_position = _off_position;
  this->neutral_position = _neutral_position;
  this->servoPin = _servoPin;
  myservo.attach(this->servoPin);
  moveNeutral();
  printf("init servo\n");

}

void LightSwitch::turnOff(){
  moveOff();
}

void LightSwitch::turnOn(){
  moveOn();
}

void LightSwitch::moveOn(){
  this->wakeup();
  if (fliped) {
    printf("move down\n");
    for(int pos = this->neutral_position ; pos > this->off_position; pos--){
      myservo.write(pos);
      delay(MOVE_DELAY);
    }
    delay(WAIT_DELAY);
    printf("move back\n");
    for(int pos = this->off_position; pos < this->neutral_position; pos++){
      myservo.write(pos);
      delay(MOVE_DELAY);
    }
  }
  else{
    printf("move up\n");
    for(int pos = this->neutral_position ; pos < this->on_position; pos++){
      myservo.write(pos);
      delay(MOVE_DELAY);
    }
    delay(WAIT_DELAY);
    printf("move back\n");
    for(int pos = this->on_position; pos > this->neutral_position; pos--){
      myservo.write(pos);
      delay(MOVE_DELAY);
    }
  }
  this->standby();
}

void LightSwitch::moveOff(){
  this->wakeup();

  if (fliped) {
    printf("move up\n");
    for(int pos = this->neutral_position ; pos < this->on_position; pos++){
      myservo.write(pos);
      delay(MOVE_DELAY);
    }
    delay(WAIT_DELAY);
    printf("move back\n");
    for(int pos = this->on_position; pos > this->neutral_position; pos--){
      myservo.write(pos);
      delay(MOVE_DELAY);
    }
  }

  printf("move down\n");
  for(int pos = this->neutral_position ; pos > this->off_position; pos--){
    myservo.write(pos);
    delay(MOVE_DELAY);
  }
  delay(WAIT_DELAY);
  printf("move back\n");
  for(int pos = this->off_position; pos < this->neutral_position; pos++){
    myservo.write(pos);
    delay(MOVE_DELAY);
  }
  this->standby();
}

void LightSwitch::moveNeutral(){
  myservo.write(this->neutral_position);
  delay(MOVE_DELAY);
}

void LightSwitch::wakeup(){
  myservo.attach(this->servoPin);
}
void LightSwitch::standby(){
  myservo.detach();
}
