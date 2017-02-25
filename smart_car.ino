// Armuino (GF) --- Smart Robot Car ---
// Playlist: https://www.youtube.com/playlist?list=PLRFnGJH1nJiJxoO0woBW6vl_8URTQPhfL
// Smart Robot Car: Part 6 - Obstacle Avoidance Prototype Program Test 
// Video Demo: https://www.youtube.com/watch?v=_XRHTeurU34

#include <Servo.h> 
#include <NewPing.h>

// Pins on the Arduino Sensor Shield v5.0
#define SONAR_SERVO_PIN 4
#define TRIGGER_PIN     A0
#define ECHO_PIN        A1

#define MAX_DISTANCE    200

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
Servo myServo;

// Motor A [Right Side]
const int enA = 10;
const int in1 = 9;
const int in2 = 8;
// Motor B [Left Side]
const int enB = 5;
const int in3 = 7;
const int in4 = 6;

const int triggerDistance = 20;

// Variables
unsigned int time;            // to store how long it takes for the ultrasonic wave to come back
int distance;                 // to store the distance calculated from the sensor
int fDistance;                // to store the distance in front of the robot
int lDistance;                // to store the distance on the left side of the robot
int rDistance;                // to store the distance on the right side of the robot
int scanDegrees = 90;

char dist[3];
char rot[3];
int rotation = 0;
String output = "";

void setup() 
{
  Serial.begin(9600);
  Serial.println("===== Smart Car =====");
  pinMode (TRIGGER_PIN, OUTPUT);
  pinMode (ECHO_PIN, INPUT);
  myServo.attach(SONAR_SERVO_PIN);  // Attaches the Servo to the Servo Object 

  // set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
} 

void loop()
{
  
  //Get the distance retrieved
  if(distance < triggerDistance){
    moveBackwards(180);
    scan();
    if(lDistance < rDistance){
      moveRight(180);
      delay(1000);
      moveForward(180);
    }
    else{
      moveLeft(180);
      delay(1000);
      moveForward(180);
    }
  }
  else{
    moveForward(180);
  }
}

void scan()
{
  // scan right to left
  for (int deg = 3; deg < 170; deg+=2) {
    myServo.write(deg);
    delay(30);
    displaySonar(deg);
  }
  lDistance = sonar.ping_cm();
  // scan left to right
  for (int deg = 170; deg > 10; deg-=2) {
    myServo.write(deg);
    delay(30);
    displaySonar(deg);
  }
  rDistance = sonar.ping_cm();
  // int deg = 90;
  // myServo.write(deg);
  // displaySonar(deg);
  // delay(10);

  // time = sonar.ping();
  // distance = time / US_ROUNDTRIP_CM;
  // delay(10);
  // if(distance <= 0){
  //   distance = triggerDistance;
  // }

  // delay(30);
}

void displaySonar(int degrees) {
  delay(30);
  if (distance < 0) distance = 0; 
  
  sprintf(dist,"%3d",distance);
  Serial.print("Range:");
  Serial.print(dist);
  Serial.print("cms/");
  sprintf(rot,"%3d",degrees);
  Serial.print(rot);
  Serial.print("deg:");

  for (int dloop = 0; dloop < distance/4; dloop++) {
    Serial.print("-");
  }
  Serial.println("=");
}

void moveForward(int speed)
{
  Serial.print("move forward");
  distance = sonar.ping_cm();
  // turn on motor A
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  // turn on motor B
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  analogWrite(enA, speed);
  analogWrite(enB, speed);
}

void moveBackwards(int speed)
{
  // turn on motor A
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  // turn on motor B
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  analogWrite(enA, speed);
  analogWrite(enB, speed);
}

void moveRight(int speed)
{
  // turn on motor A
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);

  // turn off motor B
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  analogWrite(enA, speed);
  analogWrite(enB, speed);
}

void moveLeft(int speed)
{
  // turn on motor A
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  // turn off motor B
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  analogWrite(enA, speed);
  analogWrite(enB, speed);
}

void moveStop()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  delay(200);
}
