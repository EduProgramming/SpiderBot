/**
 * 스파이더로봇 모터 제어
 * @Auth TaeJuneJoung
 * @Date 2021.06.07
 * @Update 2021.06.10
 * 
 * 수정내용:
 *   - LED 핀 번호 수정
 */

#include <SoftwareSerial.h>

int PIN_BUZZER = 3;
int PIN_LEFT_FW = 2;
int PIN_LEFT_BW = 4;
int PIN_RIGHT_FW = 7;
int PIN_RIGHT_BW = 8;
int PIN_LEFT_PWM = 5;
int PIN_RIGHT_PWM = 6;
int PIN_RED_LED = 9;
int PIN_GREEN_LED = 10;
int PIN_BLUE_LED = 11;
int PIN_TRIG = 12;
int PIN_ECHO = 13;
int PIN_TX = A4;
int PIN_RX = A5;

const long INTERVAL = 200;
const int MIN_SPEED = 150;
const int MAX_SPEED = 255;
const int speedModification = 5;

unsigned long currentTime;
int motorSpeed = 200;
float distance;
char cmd;

SoftwareSerial BT(PIN_TX, PIN_RX);

/**
 * 모터 방향 설정
 * @params isLeftFront, isRightFront
 */
void directionControl(boolean isLeftFront, boolean isRightFront) {
  digitalWrite(PIN_LEFT_FW, isLeftFront);
  digitalWrite(PIN_LEFT_BW, !isLeftFront);
  digitalWrite(PIN_RIGHT_FW, isRightFront);
  digitalWrite(PIN_RIGHT_BW, !isRightFront);
}

/**
 * 모터 스피드 설정
 * @params isPlus
 */
void speedControl(boolean isPlus) {
  if (isPlus) {
    motorSpeed += speedModification;
    if (motorSpeed > MAX_SPEED) {
      motorSpeed = MAX_SPEED;
    }
  } else {
    motorSpeed -= speedModification;
    if (motorSpeed < MIN_SPEED) {
      motorSpeed = MIN_SPEED;
    }
  }
  analogWrite(PIN_LEFT_PWM, motorSpeed);
  analogWrite(PIN_RIGHT_PWM, motorSpeed);
}

/**
 * 모터 정지
 */
void motorStop() {
  digitalWrite(PIN_LEFT_FW, LOW);
  digitalWrite(PIN_LEFT_BW, LOW);
  digitalWrite(PIN_RIGHT_FW, LOW);
  digitalWrite(PIN_RIGHT_BW, LOW);
  analogWrite(PIN_LEFT_PWM, 0);
  analogWrite(PIN_RIGHT_PWM, 0);
}

void setup() {
  BT.begin(9600);
  pinMode(PIN_LEFT_FW, OUTPUT);
  pinMode(PIN_LEFT_BW, OUTPUT);
  pinMode(PIN_RIGHT_FW, OUTPUT);
  pinMode(PIN_RIGHT_BW, OUTPUT);
  pinMode(PIN_LEFT_PWM, OUTPUT);
  pinMode(PIN_RIGHT_PWM, OUTPUT);
  pinMode(PIN_RED_LED, OUTPUT);
  pinMode(PIN_GREEN_LED, OUTPUT);
  pinMode(PIN_BLUE_LED, OUTPUT);
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);

  boolean state = false;
  for (int i=0; i < 4; i++) {
    state = !state; // !false -> true / !true -> false
    digitalWrite(PIN_GREEN_LED, state);
    delay(500);
  }

  analogWrite(PIN_LEFT_PWM, motorSpeed);
  analogWrite(PIN_RIGHT_PWM, motorSpeed);
}

void loop() {
  if (BT.available()) {
    cmd = BT.read();
    if (cmd == '2') { // 앞으로
      directionControl(true, true);
    } else if (cmd == '4') { // 왼쪽으로
      directionControl(false, true);
    } else if (cmd == '6') { // 오른쪽으로
      directionControl(true, false);
    } else if (cmd == '8') { // 뒤로
      directionControl(false, false);
    } else if (cmd == 'S') { // 정지
      motorStop();
    } else if (cmd == 'A') {
      // Autoomous Driving Mode
    } else if (cmd == '+') { // 추가] 모터 속도 5 증가: 현재 앱에서 정의 안됨
      speedControl(true);
    } else if (cmd == '-') { // 추가] 모터 속도 5 감소: 현재 앱에서 정의 안됨
      speedControl(false);
    } else if (cmd == 'P') {
      // Ultrasonic Sensor Piano
    }
  }
}
