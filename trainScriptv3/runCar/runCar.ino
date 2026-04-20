#include <IRremote.h>

#define PIN_LEFT 7
#define PIN_RIGHT 6
#define PIN_STOP 3
#define PIN_MOTOR_L 5  // speed for motor left  0-255. A on board
#define PIN_MOTOR_R 9  // speed for motor right 0-255. B on board
#define PIN_DIR_L 4
#define PIN_DIR_R 8
#define PIN_IR 2

#define IR_REPEAT 0xFFFFFFFF
#define IR_BACK 0xFF9867
#define IR_FORWARD 0xFF02FD
#define IR_LEFT 0xFFE01F
#define IR_RIGHT 0xFF906F
#define IR_SETTING 0xFFA857

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
  pinMode(PIN_DIR_L, OUTPUT);
  pinMode(PIN_DIR_R, OUTPUT);
  pinMode(PIN_LEFT, OUTPUT);
  pinMode(PIN_RIGHT, OUTPUT);
  pinMode(PIN_STOP, OUTPUT);

  digitalWrite(PIN_DIR_L, HIGH);
  digitalWrite(PIN_DIR_R, LOW);
  analogWrite(PIN_MOTOR_L, 0);
  analogWrite(PIN_MOTOR_R, 0);
}

void loop() {
  if (irrecv.decode(&results)) {
    uint32_t val = results.value;
    Serial.println(results.value);
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
  Serial.println(hexvalue);
  switch (hexvalue){
    case IR_SETTING:
      analogWrite(PIN_MOTOR_L, 0);
      analogWrite(PIN_MOTOR_R, 0);
      digitalWrite(PIN_LEFT, LOW);
      digitalWrite(PIN_RIGHT, LOW);
      digitalWrite(PIN_STOP, HIGH);
      break;

    case IR_FORWARD:
      analogWrite(PIN_MOTOR_L, 120);
      analogWrite(PIN_MOTOR_R, 90);
      digitalWrite(PIN_LEFT, HIGH);
      digitalWrite(PIN_RIGHT, HIGH);
      digitalWrite(PIN_STOP, LOW);
      digitalWrite(PIN_DIR_L, LOW);
      digitalWrite(PIN_DIR_R, LOW);
      break;

    case IR_LEFT:
      analogWrite(PIN_MOTOR_L, 40);
      analogWrite(PIN_MOTOR_R, 90);
      digitalWrite(PIN_LEFT, LOW);
      digitalWrite(PIN_RIGHT, HIGH);
      digitalWrite(PIN_STOP, LOW);
      digitalWrite(PIN_DIR_L, LOW);
      digitalWrite(PIN_DIR_R, LOW);
      break;

    case IR_RIGHT:
      analogWrite(PIN_MOTOR_L, 120);
      analogWrite(PIN_MOTOR_R, 40);
      digitalWrite(PIN_LEFT, HIGH);
      digitalWrite(PIN_RIGHT, LOW);
      digitalWrite(PIN_STOP, LOW);
      digitalWrite(PIN_DIR_L, LOW);
      digitalWrite(PIN_DIR_R, LOW);
      break;

    case IR_BACK:
      analogWrite(PIN_MOTOR_L, 100);
      analogWrite(PIN_MOTOR_R, 100);
      digitalWrite(PIN_LEFT, LOW);
      digitalWrite(PIN_RIGHT, LOW);
      digitalWrite(PIN_STOP, HIGH);
      digitalWrite(PIN_DIR_L, HIGH);
      digitalWrite(PIN_DIR_R, HIGH);
      break;

    default:
      return;
  }
}
