#include <Servo.h>
int TRIG_PIN = 13;
int ECHO_PIN = 12;
int MOTOR_PIN1 = 6;
int MOTOR_PIN2 = 5;
int MOTOR_PIN3 = 4;
int MOTOR_PIN4 = 3;
int SERVO_PIN = 9;
float SPEED_OF_SOUND = 0.0345;
int THRESHOLD = 11; // distance from sensor to obstacle

int SERVO_REST_DEGREE = 170;
int SERVO_LAUNCH_DEGREE = 10;

bool IS_MOVING = false;
int COUNTER = 0;

Servo SERVO;

//start moving forward
void startMoving() {  
  digitalWrite(MOTOR_PIN1, HIGH);
  digitalWrite(MOTOR_PIN2, HIGH);
  digitalWrite(MOTOR_PIN3, HIGH);
  digitalWrite(MOTOR_PIN4, HIGH);
}

//stop moving
void stopMoving() {
  digitalWrite(MOTOR_PIN1, LOW);
  digitalWrite(MOTOR_PIN2, LOW);
  digitalWrite(MOTOR_PIN3, LOW);
  digitalWrite(MOTOR_PIN4, LOW);
}

void setup() {
  pinMode(MOTOR_PIN1, OUTPUT);
  pinMode(MOTOR_PIN2, OUTPUT);
  pinMode(MOTOR_PIN3, OUTPUT);
  pinMode(MOTOR_PIN4, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  digitalWrite(TRIG_PIN, LOW);
  pinMode(ECHO_PIN, INPUT);
  Serial.begin(9600);
  SERVO.attach(SERVO_PIN, 1000, 2000);
  SERVO.write(SERVO_REST_DEGREE);

  delay(10000);
}


void launchBall() {
  //code to launch ball
  Serial.println("launch!");
  SERVO.write(SERVO_LAUNCH_DEGREE);
  delay(2000);
  SERVO.write(SERVO_REST_DEGREE); 
  delay(2000);
}

//get distance from wall in centimeter
float getDistanceFromWall() {
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  int microsecs = pulseIn(ECHO_PIN, HIGH);
  float cms = microsecs * SPEED_OF_SOUND / 2;
  Serial.println(cms);
  return cms;
}

void loop() {
  delay(10);
  SERVO.write(SERVO_REST_DEGREE);
  float distance = getDistanceFromWall();
  if (distance > THRESHOLD || distance <= 0) {//distance > threshold 
    Serial.println("exceeds threshold");
    if (!IS_MOVING) {
      Serial.println("start moving");
      startMoving();
      IS_MOVING = true;
      
    }
  } else {//distance <= threshold
    Serial.println("does not exceed threshold");
    if (IS_MOVING) {
      Serial.println("stop moving");
      stopMoving();
      IS_MOVING = false;
    }
    launchBall();
  }
}
