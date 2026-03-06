#include <Arduino.h>
#include <IRremote.h>

const int left = 7;
const int forward = 6;
const int right = 5;
const int motorleft = 4;
const int motorright = 3;
const int ir_pin = 2;

bool forw = false;
String direction = "stop";

IRrecv irrecv(ir_pin);
decode_results results;

void setup() {
  Serial.begin(115200);

  // Ir remote setup
  irrecv.enableIRIn();
  // irrecv.blink13(true);

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
    runCar(direction);
  } 
  Serial.println(direction);
}


String irRemote(String direction){
  if (results.value == 0xFF9867){
    forw = false;
    return "stop";
  } 

  if (results.value == 0xFFFFFFFF){
    return direction;
  }

  if (results.value == 0xFFA857){
    forw = true;
  }

  if (forw == true){
    if (results.value == 0xFFE01F){
      direction = "left";
    } else if (results.value == 0xFF906F){
      direction = "right";
    } else{
      direction = "forward";
    }
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
