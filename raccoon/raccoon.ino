/*
* Autonomos robot with ultra sonic sensor in order to exit a labyrinth. The robot is based on Arduino mini and L298 controller with two DC motors
*/

#include "Arduino.h" // Used for the ultrasonic class.

/*
Class to control 2 DC motors. 6 digital pins are required.
The controller is http://www.robotev.com/product_info.php?cPath=1_40_39&products_id=173
*/
class Movement
{
  public:
    Movement(void);
    void moveForward(int leftWheel, int rightWheel);
    void moveBackward(int leftWheel, int rightWheel);
    void turnRight(int leftWheel, int rightWheel);
  private:
    int motor1APin;
    int motor1BPin;
    int motor1ENPin;
    int motor2APin;
    int motor2BPin;
    int motor2ENPin;
};

Movement::Movement(void)
{
  // Setting the 6 digital pins for controlling the motors
  motor1APin = 4;
  motor1BPin = 5;
  motor1ENPin = 9;
  motor2APin = 6;
  motor2BPin = 7;
  motor2ENPin = 10;

  pinMode(motor1APin, OUTPUT);
  pinMode(motor1BPin, OUTPUT);
  pinMode(motor1ENPin, OUTPUT);
  pinMode(motor2APin, OUTPUT);
  pinMode(motor2BPin, OUTPUT);
  pinMode(motor2ENPin, OUTPUT);
}

/*
Method for moving forward. The speed of the wheels could be different and this will bend the path of the robot.
*/
void Movement::moveForward(int leftWheel, int rightWheel)
{
  analogWrite(motor1ENPin, rightWheel);
  digitalWrite(motor1APin, LOW);
  digitalWrite(motor1BPin, HIGH);
  analogWrite(motor2ENPin, leftWheel);
  digitalWrite(motor2APin, LOW);
  digitalWrite(motor2BPin, HIGH);
}

/*
Method for moving backward.
*/
void Movement::moveBackward(int leftWheel, int rightWheel)
{
  analogWrite(motor1ENPin, rightWheel);
  digitalWrite(motor1APin, HIGH);
  digitalWrite(motor1BPin, LOW);
  analogWrite(motor2ENPin, leftWheel);
  digitalWrite(motor2APin, HIGH);
  digitalWrite(motor2BPin, LOW);
}

/*
Method for turning right
*/
void Movement::turnRight(int leftWheel, int rightWheel)
{
  analogWrite(motor1ENPin, rightWheel);
  digitalWrite(motor1APin, HIGH);
  digitalWrite(motor1BPin, LOW);
  analogWrite(motor2ENPin, leftWheel);
  digitalWrite(motor2APin, LOW);
  digitalWrite(motor2BPin, HIGH);
}

/*
Class for taking the distance of Ultrasonic sensor. Inches is commented out.
*/
class Ultrasonic
{
  public:
    Ultrasonic(int pin);
    void DistanceMeasure(void);
    long microsecondsToCentimeters(void);
    //long microsecondsToInches(void);
  private:
    int _pin;//pin number of Arduino that is connected with SIG pin of Ultrasonic Ranger.
    long duration;// the Pulse time received;
};
Ultrasonic::Ultrasonic(int pin)
{
  _pin = pin;
}
/*Begin the detection and get the pulse back signal*/
void Ultrasonic::DistanceMeasure(void)
{
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(_pin, HIGH);
  delayMicroseconds(5);
  digitalWrite(_pin, LOW);
  pinMode(_pin, INPUT);
  duration = pulseIn(_pin, HIGH);
}
/*The measured distance from the range 0 to 400 Centimeters*/
long Ultrasonic::microsecondsToCentimeters(void)
{
  return duration / 29 / 2;
}
/*The measured distance from the range 0 to 157 Inches*/
/*long Ultrasonic::microsecondsToInches(void)
{
  return duration / 74 / 2;
}*/

Ultrasonic ultrasonic(11);
Movement movement;

int lastDistance = 0;
int stillCounter = 0;

void setup()
{
  //Serial.begin(9600);
}

void loop() {

  //long RangeInInches;
  long RangeInCentimeters;
  ultrasonic.DistanceMeasure();// get the current signal time;
  //RangeInInches = ultrasonic.microsecondsToInches();//convert the time to inches;
  RangeInCentimeters = ultrasonic.microsecondsToCentimeters();//convert the time to centimeters
  //Serial.print(RangeInInches);//0~157 inches
  //Serial.println(" inch");
  //Serial.print(RangeInCentimeters);//0~400cm
  //Serial.println(" cm");
  //delay(100);

  if (RangeInCentimeters < 100 && RangeInCentimeters == lastDistance) {
    stillCounter++; // increment the stillCounter when the robot is blocked
  } else {
    stillCounter = 0;
  }

  // when the still counter reach 50 (around 2 sec), move backward in order to escape from the lockdown.
  if (stillCounter > 50) {
    movement.moveBackward(200, 240);
    delay(550);
    stillCounter = 0;
  } else {
    lastDistance = RangeInCentimeters;
  }
  //Serial.println(stillCounter);


  /* Cases to follow the left wall until the robot leaves the labyrinth.
   */

  if (RangeInCentimeters > 20) {
    movement.moveForward(140, 200);
    delay(50);
  }
  else if (RangeInCentimeters > 10) {
    movement.moveForward(140, 180);
    delay(50);
  }
  else if (RangeInCentimeters > 8) {
    movement.moveForward(150, 165);
    delay(50);
  }
  else if (RangeInCentimeters > 6) {
    movement.moveForward(150, 155);
    delay(50);
  }
  else if (RangeInCentimeters > 4) {
    movement.moveForward(160, 150);
    delay(50);
  }
  else if (RangeInCentimeters > 3) {
    movement.turnRight(150, 150);
    delay(50);
  }
  else {
    movement.moveBackward(150, 190);
    delay(50);
  }

  /*
   // Stop the motors
   analogWrite(motor1ENPin, 0);
   digitalWrite(motor1APin, LOW);
   digitalWrite(motor1BPin, LOW);
   analogWrite(motor2ENPin, 0);
   digitalWrite(motor2APin, LOW);
   digitalWrite(motor2BPin, LOW);
   delay(2000); //zadyrja motorite izklyucheni za 2 sekundi
  */

}

