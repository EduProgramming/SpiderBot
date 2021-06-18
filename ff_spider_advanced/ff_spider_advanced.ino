/**
 * 스파이더로봇 다기능 처리
 * @Auth TaeJuneJoung
 * @Date 2021.06.18
 */

#define PIN_LED_RED           9
#define PIN_LED_GREEN        10
#define PIN_LED_BLUE         11
#define PIN_LEFT_WHEEL_FW     2
#define PIN_LEFT_WHEEL_BW     4
#define PIN_RIGHT_WHEEL_FW    7
#define PIN_RIGHT_WHEEL_BW    8
#define PIN_LEFT_WHEEL_SP     5
#define PIN_RIGHT_WHEEL_SP    6
#define PIN_BUZZER            3
#define PIN_TRIG             12
#define PIN_ECHO             13
#define PIN_BT_TX            A4
#define PIN_BT_RX            A5

#include <SoftwareSerial.h>

SoftwareSerial BT(PIN_BT_TX, PIN_BT_RX);

const int START_VAL = 255;
const int DATA_LEN = 12;
const int END_VALUE = 10;

const int STOP_INT = 0;

unsigned char buf[DATA_LEN];
unsigned char prevc;
unsigned long currentTime;
int index = 0;
int mode = -1;
boolean isStart = false;

boolean PIANO_LED[8][3] = {
  {true, false, false}, {false, true, false}, {false, false, true},
  {true, true, false}, {true, false, true}, {false, true, true},
  {true, true, true}, {true, false, false}
}; 

int NOTES[7][8] = {
  {33, 37, 41, 44, 49, 55, 62, 65},
  {65, 73, 82, 87, 98, 110, 123, 131},
  {131, 147, 165, 175, 196, 220, 247, 262},
  {262, 294, 330, 349, 392, 440, 494, 523},
  {523, 587, 659, 698, 784, 880, 988, 1046},
  {1046, 1175, 1319, 1397, 1568, 1760, 1976, 2093},
  {2093, 2349, 2637, 2794, 3136, 3520, 3951, 4186}
};


/**
 * Pin Init Function
 */
void pinInit() {
  for (int pin=2; pin < 13; pin++) {
    pinMode(pin, OUTPUT);
  }
  pinMode(PIN_ECHO, INPUT);
}

/**
 * Get Bluetooth Data
 * @params c
 */
void getUpdateData(unsigned char c) {
  if (c == DATA_LEN && isStart == false) {
    if (prevc == START_VAL) {
      isStart = true;
      index = 1;
      writeBuffer(index-1, prevc);
      writeBuffer(index, c);
    }
  } else {
    prevc = c;
    if (isStart) {
      writeBuffer(index, c);
    }
  }

  index++;

  if (index > DATA_LEN) {
    isStart = false;
    index=0;
  }

  if (isStart && index == DATA_LEN && index > 3) {
    isStart = false;
    parseData();
    index = 0;
  }
}

/**
 * Check Buffer Sum Data
 * @return boolean
 */
bool isCheckOk() {
  if (buf[DATA_LEN-1] == END_VALUE) {
    int checkSum = buf[DATA_LEN-2];
    int sumValue = 0;
    for (int i=2; i<DATA_LEN-2; i++) {
      sumValue += buf[i];
    }
    sumValue = sumValue & 0xff;
    if (checkSum == sumValue) {
      return true;
    }
  }
  return false;
}

/**
 * Read Buffer Data
 * @params index
 */
unsigned char readBuffer(int index) {
  return buf[index];
}

/**
 * Write Buffer Data
 * @params c
 */
void writeBuffer(int index, unsigned char c) {
  buf[index] = c;
}

/**
 * Control Motor
 * @params leftWheel, rightWheel, leftSpeed, rightSpeed
 */
void ctrlMotor(int leftWheel, int rightWheel, int leftSpeed, int rightSpeed) {
  if (leftSpeed == 0 && rightSpeed == 0) { // Stop Motor
    digitalWrite(PIN_LEFT_WHEEL_FW, LOW);
    digitalWrite(PIN_LEFT_WHEEL_BW, LOW);
    digitalWrite(PIN_RIGHT_WHEEL_FW, LOW);
    digitalWrite(PIN_RIGHT_WHEEL_BW, LOW);
    analogWrite(PIN_LEFT_WHEEL_SP, leftSpeed);
    analogWrite(PIN_RIGHT_WHEEL_SP, rightSpeed);
  } else { // Move Motor
    boolean leftState = leftWheel ? true : false;
    boolean rightState = rightWheel ? true : false;
    
    digitalWrite(PIN_LEFT_WHEEL_FW, leftState);
    digitalWrite(PIN_LEFT_WHEEL_BW, !leftState);
    digitalWrite(PIN_RIGHT_WHEEL_FW, rightWheel);
    digitalWrite(PIN_RIGHT_WHEEL_BW, !rightWheel);
    analogWrite(PIN_LEFT_WHEEL_SP, leftSpeed);
    analogWrite(PIN_RIGHT_WHEEL_SP, rightSpeed);
  }
}

/**
 * Get Ultrasonic Sensor Distance Value
 * @return distance
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
 * Obstacle Avoidance Driving: Direction
 * @params command, direct, turnTime, leftSpeed, rightSpeed
 */
void obstacleDirectionMove(int command, int direct, unsigned long turnTime, int leftSpeed, int rightSpeed) {
  currentTime = millis();
  int frontInt = 1;
  int backInt = 0;

  if (direct) {
    ctrlMotor(frontInt, backInt, leftSpeed, rightSpeed);
  } else {
    ctrlMotor(backInt, frontInt, leftSpeed, rightSpeed);
  }
  
  while (millis() - currentTime < turnTime) {
    getData();
    if (mode != command) {
      ctrlMotor(STOP_INT, STOP_INT, STOP_INT, STOP_INT);
      return;
    }
  }
  ctrlMotor(STOP_INT, STOP_INT, STOP_INT, STOP_INT);
}

/**
 * Obstacle Avoidance Driving
 * @params distance, direct, turnTime, leftSpeed, rightSpeed
 */
void obstacleAvoidanceDriving(int distance, int direct, int turnTime, int leftSpeed, int rightSpeed) {
  int command = 1;
  analogWrite(PIN_LEFT_WHEEL_SP, leftSpeed);
  analogWrite(PIN_RIGHT_WHEEL_SP, rightSpeed);
  int frontInt = 1;
  int backInt = 0;
  
  while (mode == command) {
    float distanceVal = getDistance();
    if (distanceVal > distance) {
      ctrlMotor(frontInt, frontInt, leftSpeed, rightSpeed); // Move Front
    } else {
      ctrlMotor(STOP_INT, STOP_INT, STOP_INT, STOP_INT);
      unsigned long turnTimeVal = turnTime * 100;
      if (direct == 0) { // Right Hand on Wall
        obstacleDirectionMove(command, direct, turnTimeVal, leftSpeed, rightSpeed);
      } else if (direct == 1) { // Left Hand on Wall
        obstacleDirectionMove(command, direct, turnTimeVal, leftSpeed, rightSpeed);
      } else if (direct == 2) { // Random
        int randomNumber = random(direct);
        obstacleDirectionMove(command, randomNumber, turnTimeVal, leftSpeed, rightSpeed);
      }
    }
    getData();
  }
}

/**
 * Piano Led Control
 * @params redState, greenState, blueState
 */
void pianoLedControl(int redState, int greenState, int blueState) {
  digitalWrite(PIN_LED_RED, redState);
  digitalWrite(PIN_LED_GREEN, greenState);
  digitalWrite(PIN_LED_BLUE, blueState);
}

void pianoRestTimer(int command, unsigned long restTime) {
  currentTime = millis();
  
  while (millis() - currentTime < restTime) {
    getData();
    if (mode != command) {
      pianoLedControl(false, false, false);
      return;
    }
  }
}

/**
 * Play Air Piano
 * @params distance, soundTime, sleepTime, octave
 */
void playAirPiano(int distance, int soundTime, int sleepTime, int octave) {
  int command = 2;
  
  while (mode == command) {
    int distanceVal = int(getDistance() / distance);
    if (distanceVal < 8) {
      unsigned long soundTimeVal = soundTime * 100;
      unsigned long sleepTimeVal = sleepTime * 100;
      pianoLedControl(PIANO_LED[distanceVal][0], PIANO_LED[distanceVal][1], PIANO_LED[distanceVal][2]);
      tone(PIN_BUZZER, NOTES[octave][distanceVal], soundTimeVal);
      pianoRestTimer(command, soundTimeVal + sleepTimeVal);
    } else {
      pianoLedControl(false, false, false);
    }
    getData();
  }
}

/**
 * Parse Data 
 */
void parseData() {
  if (isCheckOk()) {
    mode = readBuffer(2);
    int redValue = readBuffer(3);
    int greenValue = readBuffer(4);
    int blueValue = readBuffer(5);
    int leftWheel = readBuffer(6);
    int rightWheel = readBuffer(7);
    int leftSpeed = readBuffer(8);
    int rightSpeed = readBuffer(9);
    if (mode == 0) { // General Control Mode
      analogWrite(PIN_LED_RED, redValue);
      analogWrite(PIN_LED_GREEN, greenValue);
      analogWrite(PIN_LED_BLUE, blueValue);
      ctrlMotor(leftWheel, rightWheel, leftSpeed, rightSpeed);
      analogWrite(PIN_LEFT_WHEEL_SP, leftSpeed);
      analogWrite(PIN_RIGHT_WHEEL_SP, rightSpeed);
    } else if (mode == 1) { // Obstracle Avoidance Driving
      obstacleAvoidanceDriving(redValue, greenValue, blueValue, leftSpeed, rightSpeed);
    } else if (mode == 2) { // Air 피아노
      playAirPiano(redValue, greenValue, blueValue, leftWheel);
    }
  }
}

/**
 * Get Bluetooth Data
 */
void getData() {
  if (BT.available()) {
    unsigned char c = BT.read();
    Serial.println(c);
    getUpdateData(c);
  }
}

void setup() {
  Serial.begin(9600);
  BT.begin(9600);
  pinInit();
  randomSeed(analogRead(0));
}

void loop() {
  getData();
}
