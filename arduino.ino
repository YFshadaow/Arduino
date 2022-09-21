#include <Servo.h>
int TRIG_PIN = 13;
int ECHO_PIN = 12;
int MOTOR_PIN1 = 6;
int MOTOR_PIN2 = 5;
int MOTOR_PIN3 = 4;
int MOTOR_PIN4 = 3;
int SERVO_PIN = 9;
float SPEED_OF_SOUND = 0.0345;
int THRESHOLD = 20;

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
  SERVO.write(0);

  //start moving at the start
  startMoving();
}


void launchBall() {
  //code to launch ball
  Serial.println("launch!");
  SERVO.write(180);
  delay(2000);
  SERVO.write(0);
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
  float distance = getDistanceFromWall();
  if (distance > THRESHOLD) {//distance > threshold
    if (COUNTER != 0) {
      COUNTER = 0;
      Serial.println("counter resets!");
    }
  } else {//distance <= threshold
    if (COUNTER < 3) {
      COUNTER += 1;
      Serial.println("counter increases!");
    } else {//counter reaches 3 times
      stopMoving();
      COUNTER = 0;//reset counter
      launchBall();
      startMoving();
    }
  }
}
