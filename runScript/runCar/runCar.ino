#define PIN_LEFT 7
#define PIN_RIGHT 6
#define PIN_STOP 3

#define PIN_MOTOR_L 5  // speed for motor left  0-255. A on board
#define PIN_MOTOR_R 9  // speed for motor right 0-255. B on board
#define PIN_DIR_L 4
#define PIN_DIR_R 8

void setup() {
  Serial.begin(115200);

  // Motor setup and output to Nicla vision
  pinMode(PIN_MOTOR_L, OUTPUT);
  pinMode(PIN_MOTOR_R, OUTPUT);
  pinMode(PIN_DIR_L, OUTPUT);
  pinMode(PIN_DIR_R, OUTPUT);

  pinMode(PIN_LEFT, INPUT);
  pinMode(PIN_RIGHT, INPUT);
  pinMode(PIN_STOP, INPUT);

  digitalWrite(PIN_DIR_L, HIGH);
  digitalWrite(PIN_DIR_R, LOW);
  analogWrite(PIN_MOTOR_L, 0);
  analogWrite(PIN_MOTOR_R, 0);
}

void loop() {
  runCar();
}

void runCar(){
  if ((digitalRead(PIN_LEFT) == HIGH) && (digitalRead(PIN_RIGHT) == HIGH) && (digitalRead(PIN_STOP) == LOW)){
    analogWrite(PIN_MOTOR_L, 100);
    analogWrite(PIN_MOTOR_R, 100);
    digitalWrite(PIN_DIR_L, LOW);
    digitalWrite(PIN_DIR_R, LOW);
  } else if ((digitalRead(PIN_RIGHT) == HIGH) && (digitalRead(PIN_LEFT) == LOW) && (digitalRead(PIN_STOP) == LOW)){
    analogWrite(PIN_MOTOR_L, 0);
    analogWrite(PIN_MOTOR_R, 50);
    digitalWrite(PIN_DIR_L, LOW);
    digitalWrite(PIN_DIR_R, LOW);
  } else if ((digitalRead(PIN_RIGHT) == LOW) && (digitalRead(PIN_LEFT) == HIGH) && (digitalRead(PIN_STOP) == LOW)){
    analogWrite(PIN_MOTOR_L, 50);
    analogWrite(PIN_MOTOR_R, 0);
    digitalWrite(PIN_DIR_L, LOW);
    digitalWrite(PIN_DIR_R, LOW);
  } else if ( (digitalRead(PIN_RIGHT) == HIGH) && (digitalRead(PIN_LEFT) == LOW) && (digitalRead(PIN_STOP) == HIGH)){
    analogWrite(PIN_MOTOR_L, 0);
    analogWrite(PIN_MOTOR_R, 0);
  }
}
