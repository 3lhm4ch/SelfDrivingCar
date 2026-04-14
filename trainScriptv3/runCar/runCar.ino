#include <IRremote.h>

#define PIN_LEFT 7
#define PIN_RIGHT 6
#define PIN_STOP 5
#define PIN_MOTOR_L 10  // speed for motor left  0-255
#define PIN_MOTOR_R 11  // speed for motor right 0-255
#define PIN_IR 2

#define IR_REPEAT 0xFFFFFFFF
#define IR_STOP 0xFF9867
#define IR_FORWARD 0xFFA857 //(settings button on "makeblock" remote)
#define IR_LEFT 0xFFE01F
#define IR_RIGHT 0xFF906F

IRrecv irrecv(PIN_IR);
decode_results results;
uint32_t PreviousVal;

void setup() {
  Serial.begin(115200);

  // IR remote setup
  irrecv.enableIRIn();
  irrecv.blink13(true);

  // Motor setup and output to Nicla vision
  pinMode(PIN_MOTOR_L, OUTPUT);
  pinMode(PIN_MOTOR_R, OUTPUT);
  pinMode(PIN_LEFT, OUTPUT);
  pinMode(PIN_RIGHT, OUTPUT);
  pinMode(PIN_STOP, OUTPUT);
}

void loop() {
  if (irrecv.decode(&results)) {
    uint32_t val = results.value;
    if (val == IR_REPEAT){
      val = PreviousVal;
    }
    Serial.println(val, HEX);
    irRemote(val);
    irrecv.resume();
    PreviousVal = val;
  }
}

void irRemote(uint32_t hexvalue){
  switch (hexvalue){
    case IR_STOP:
      analogWrite(PIN_MOTOR_L, 0);
      analogWrite(PIN_MOTOR_R, 0);
      digitalWrite(PIN_LEFT, LOW);
      digitalWrite(PIN_RIGHT, LOW);
      digitalWrite(PIN_STOP, HIGH);
      break;

    case IR_FORWARD:
      analogWrite(PIN_MOTOR_L, 200);
      analogWrite(PIN_MOTOR_R, 200);
      digitalWrite(PIN_LEFT, HIGH);
      digitalWrite(PIN_RIGHT, HIGH);
      digitalWrite(PIN_STOP, LOW);
      break;

    case IR_LEFT:
      analogWrite(PIN_MOTOR_L, 0);
      analogWrite(PIN_MOTOR_R, 100);
      digitalWrite(PIN_LEFT, LOW);
      digitalWrite(PIN_RIGHT, HIGH);
      digitalWrite(PIN_STOP, LOW);
      break;

    case IR_RIGHT:
      analogWrite(PIN_MOTOR_L, 100);
      analogWrite(PIN_MOTOR_R, 0);
      digitalWrite(PIN_LEFT, HIGH);
      digitalWrite(PIN_RIGHT, LOW);
      digitalWrite(PIN_STOP, LOW);
      break;
      
    default:
      return;
  }
}
