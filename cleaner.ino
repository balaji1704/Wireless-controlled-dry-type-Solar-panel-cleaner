#include "thingProperties.h"
const int trigPin1 = 15;
const int echoPin1 = 2;
const int trigPin2 = 4;
const int echoPin2 = 16;
int r11 = 14;
int r12 = 27;
int r21 = 26;
int r22 = 25;
long duration1;
int distance1;
long duration2;
int distance2;
int count = 0;
void setup() {
  pinMode(trigPin1, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin1, INPUT); // Sets the echoPin as an Input
  pinMode(trigPin2, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin2, INPUT); // Sets the echoPin as an Input
  pinMode(r11, OUTPUT);
  pinMode(r12, OUTPUT);
  pinMode(r21, OUTPUT);
  pinMode(r22, OUTPUT);
  digitalWrite(r11, HIGH);
  digitalWrite(r12, HIGH);
  digitalWrite(r21, HIGH);
  digitalWrite(r22, HIGH);
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500);

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
  */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void ultrasonic1() {
  // Clears the trigPin
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration1 = pulseIn(echoPin1, HIGH);
  // Calculating the distance
  distance1 = duration1 * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance1);
}

void ultrasonic2() {
  // Clears the trigPin
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration2 = pulseIn(echoPin2, HIGH);
  // Calculating the distance
  distance2 = duration2 * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance2);
}

void loop() {
  ArduinoCloud.update();
  // Your code here
}
void loop1() {
  while (count <= 3) {
    ultrasonic1();
    ultrasonic2();
    while (distance1 >= 20 || distance1 <= 0) {
      digitalWrite(r11, HIGH);
      digitalWrite(r12, HIGH);
      digitalWrite(r21, LOW);
      digitalWrite(r22, LOW);
      ultrasonic1();
      ultrasonic2();
      if (distance2 >= 20 || distance2 <= 0) {
        count += 1;
      }
    }
    while (distance2 >= 20 || distance2 <= 0) {
      digitalWrite(r11, LOW);
      digitalWrite(r12, LOW);
      digitalWrite(r21, HIGH);
      digitalWrite(r22, HIGH);
      ultrasonic1();
      ultrasonic2();
      if (distance1 >= 20 || distance1 <= 0) {
        count += 1;

      }
    }
    loop1();
    if (count = 4) {
      digitalWrite(r11, HIGH);
      digitalWrite(r12, HIGH);
      digitalWrite(r21, HIGH);
      digitalWrite(r22, HIGH);
    }
  }
}

void onM1Change()  {
  if (m1 == 1) {
    count = 0;
    loop1();
  }
}
