/**
 * 스파이더 구동
 * @Auth TaeJuneJoung
 * @Date 2021.06.10
 * 기능:
 *  - 기존 기능
 *   1. 구동
 *   2. 장애물 회피 주행
 *  - 추가 기능:
 *   3. 모터 속도 조절
 *   cf. App은 추가 안되어 있음
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
 * LED 제어
 * @params redState, greenState, blueState
 */
void ledControl(boolean redState, boolean greenState, boolean blueState) {
  digitalWrite(PIN_RED_LED, redState);
  digitalWrite(PIN_GREEN_LED, greenState);
  digitalWrite(PIN_BLUE_LED, blueState);
}

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

/**
 * 초음파 센서 거리값 측정
 * @return distance
 * distance = duration / 29.0 / 2
 */
float getDistance() {
  digitalWrite(PIN_TRIG, LOW);
  digitalWrite(PIN_ECHO, LOW);
  delayMicroseconds(2);
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);
  float duration = pulseIn(PIN_ECHO, HIGH);
  return duration / 29.0 / 2;
}

/**
 * 회피주행모드: 후진주행알림
 * @params commandChar
 */
void obstacleBackwardAction(char commandChar) {
  boolean ledState = false;
  for (int i=0; i < 6; i++) {
    while (millis() - currentTime < 500) {
      getBluetoothCommand();
      if (cmd != commandChar) {
        ledControl(false, false, false);
        motorStop();
        return;
      }
    }
    currentTime = millis();
    ledState = !ledState;
    if (ledState) {
      ledControl(true, false, false);
      tone(PIN_BUZZER, 2048,300);
    } else { 
      ledControl(false, false, true);
      tone(PIN_BUZZER, 2342, 300);
    }
  }
  ledControl(false, false, false);
}

/**
 * 회피주행모드: 우측이동(우선법)
 * @params commandChar
 */
void obstacleRightMove(char commandChar) {
  currentTime = millis();
  directionControl(true, false);
  while (millis() - currentTime < 3000) {
    getBluetoothCommand();
    if (cmd != commandChar) {
      motorStop();
      return;
    }
  }
  motorStop();
}

/**
 * 회피주행모드
 * : 초음파 센서 측정값 10cm 이상일 때 전진
 * 이하일 때 뒤로 3초간 후진 및 제자리 우측으로 3초간 이동
 */
void obstacleAvoidance() {
  char commandChar = 'A';
  while (true) {
    distance = getDistance();
    if (distance > 10) {
      directionControl(true, true);
    } else {
      directionControl(false, false);
      obstacleBackwardAction(commandChar);
      obstacleRightMove(commandChar);
    }
    getBluetoothCommand();
    if (cmd != commandChar) {
      motorStop();
      return;
    }
  }
}

/**
 * 블루투스 값 받아오기
 */
void getBluetoothCommand() {
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
      obstacleAvoidance(); // 장애물 회피 주행(우선법)
    } else if (cmd == '+') { // 추가] 모터 속도 5 증가: 현재 앱에서 정의 안됨
      speedControl(true);
    } else if (cmd == '-') { // 추가] 모터 속도 5 감소: 현재 앱에서 정의 안됨
      speedControl(false);
    } else if (cmd == 'P') {
      // Ultrasonic Sensor Piano
    }
  }
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
  getBluetoothCommand();
}
