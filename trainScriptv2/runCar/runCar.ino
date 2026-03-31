#include <IRremote.h>

#define PIN_STOP 5
#define PIN_MOTOR_L 4
#define PIN_MOTOR_R 3
#define PIN_IR 11

#define IR_REPEAT 0xFFFFFFFF
#define IR_STOP 0xFF9867
#define IR_FORWARD 0xFFA857
#define IR_LEFT 0xFFE01F
#define IR_RIGHT 0xFF906F

IRrecv irrecv(PIN_IR);
decode_results results;

void setup() {
  Serial.begin(115200);

  // IR remote setup
  irrecv.enableIRIn();
  irrecv.blink13(true);

  // Motor setup and output to Nicla vision
  pinMode(PIN_MOTOR_L, OUTPUT);
  pinMode(PIN_MOTOR_R, OUTPUT);
  pinMode(PIN_STOP, OUTPUT);
}

void loop() {
  if (irrecv.decode(&results)) {
    uint32_t val = results.value;
    Serial.println(val, HEX);
    irRemote(val);
    irrecv.resume();
  }
}

void irRemote(uint32_t hexvalue){
  switch (hexvalue){
    case IR_REPEAT:
      return; // Ignore repeat if needed

    case IR_STOP:
      digitalWrite(PIN_STOP, HIGH);
      digitalWrite(PIN_MOTOR_L, LOW);
      digitalWrite(PIN_MOTOR_R, LOW);
      break;

    case IR_FORWARD:
      digitalWrite(PIN_STOP, LOW);
      digitalWrite(PIN_MOTOR_L, HIGH);
      digitalWrite(PIN_MOTOR_R, HIGH);
      break;

    case IR_LEFT:
      digitalWrite(PIN_STOP, LOW);
      digitalWrite(PIN_MOTOR_L, LOW);
      digitalWrite(PIN_MOTOR_R, HIGH);
      break;

    case IR_RIGHT:
      digitalWrite(PIN_STOP, LOW);
      digitalWrite(PIN_MOTOR_L, HIGH);
      digitalWrite(PIN_MOTOR_R, LOW);
      break;
      
    default:
      return;
  }
}
