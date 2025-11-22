#include <AFMotor.h>  
#include <NewPing.h>
#include <Servo.h> 

#define TRIG_PIN A0 
#define ECHO_PIN A1 
#define MAX_DISTANCE 10

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 

AF_DCMotor motor1(1, MOTOR12_1KHZ); 
AF_DCMotor motor2(2, MOTOR12_1KHZ);
Servo servo;

void setup() {
  Serial.begin(9600);
  delay(50);
  motor1.setSpeed(100); // set motor1 speed to maximum
  motor2.setSpeed(100); // set motor2 speed to maximum
  servo.attach(9); // attach servo to pin 9
    motor1.run(FORWARD); 
    motor2.run(FORWARD); 
  }

void loop() {
  Serial.println(sonar.ping_cm());
  delay(1000);

  int distance = sonar.ping_cm(); // get distance from ultrasonic sensor in cm
  if (distance > 3) { 
    motor1.run(RELEASE); // stop motor1
    motor2.run(RELEASE); // stop motor2
    delay(1000); // wait for 1 second
    servo.write(-20); // spin servo to 90 degrees
    delay(1000);
    exit(0);
  }
  else { // if distance is less than or equal to 2 cm
    motor1.run(FORWARD); 
    motor2.run(FORWARD); 
  }
}
