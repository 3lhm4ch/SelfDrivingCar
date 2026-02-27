#include <Arduino.h>
#include <IRremote.h>

String direction = "stop";
String directionBefore = direction;
bool forw = false;
const int motorleft = 3;
const int motorright = 4;
const int right = 5;
const int left = 6;
const int forward = 7;

const int RECV_PIN = 2;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
  Serial.begin(115200);

  // Ir remote setup
  irrecv.enableIRIn();
  irrecv.blink13(true);

  // Motor setup
  pinMode(motorleft, OUTPUT);
  pinMode(motorright, OUTPUT);

  // Output to nicla vision setup
  pinMode(right, OUTPUT);
  pinMode(left, OUTPUT);
  pinMode(forward, OUTPUT);
}

void loop() {
  if (irrecv.decode(&results)){
    direction = irRemote(direction);
    irrecv.resume();
  } 
  Serial.println(direction);

  runCar(direction);
}


String irRemote(String direction){
  if (results.value == 0xFFA857){
    forw = true;
  } else if (results.value == 0xFF9867){
    forw = false;
  } 

  if (forw == true){
    if (results.value == 0xFFE01F){
      direction = "left";
    } else if (results.value == 0xFF906F){
      direction = "right";
    } else if (direction == "left" && results.value == 0xFFFFFFFF){
      direction = "left";
    } else if (direction == "right" && results.value == 0xFFFFFFFF){
      direction = "right";
    } else {
      direction = "forward";
    }
  } else{
    direction = "stop";
  }

  return direction;
}

void runCar(String direction){
  if (direction == "left"){
    digitalWrite(forward, LOW);
    digitalWrite(right, LOW);
    digitalWrite(left, HIGH);
    digitalWrite(motorleft, LOW);
    digitalWrite(motorright, HIGH);
  } else if (direction == "right"){
    digitalWrite(left, LOW);
    digitalWrite(forward, LOW);
    digitalWrite(right, HIGH);
    digitalWrite(motorleft, HIGH);
    digitalWrite(motorright, LOW);
  } else if (direction == "stop"){
    digitalWrite(left, LOW);
    digitalWrite(forward, LOW);
    digitalWrite(right, LOW);
    digitalWrite(motorleft, LOW);
    digitalWrite(motorright, LOW);
  } else if (direction == "forward"){
    digitalWrite(left, LOW);
    digitalWrite(right, LOW);
    digitalWrite(forward, HIGH);
    digitalWrite(motorleft, HIGH);
    digitalWrite(motorright, HIGH);
  }
}
