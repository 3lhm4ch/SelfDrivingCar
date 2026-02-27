#include <Arduino.h>
#include <IRremote.h>

String direction = "stop";
String directionBefore = direction;
int motorleft = 3;
int motorright = 4;
int right = 5;
int left = 6;
int forward = 7;

const int RECV_PIN = 7;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
  Serial.begin(115200);

  // Ir remote setup
  Serial.begin(9600);
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
  }

  if (directionBefore != direction){
    runCar(direction);
  }
  directionBefore = direction;
}


String irRemote(String direction){
  Serial.println(results.value, HEX);
  if (results.value == 0xFFFFFFFF){
    return direction;
  } else if (results.value == 0xFFE01F){
    return "left";
  } else if (results.value == 0xFF906F){
    return "right";
  } else if (results.value == 0xFF9867){
    return "stop";
  } else{
    return "forward";
  }
  irrecv.resume();
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
