/**
 * 네오아두보드 Buzzer
 * @Auth TaeJuneJoung
 * @Date 2021.06.03
 * 경보알림음 만들기(함수)
 */

int PIN_BUZZER = 3;
int PIN_RED = 9;
int PIN_BLUE = 11;

void ctrl(boolean redState, boolean blueState, int note) {
  digitalWrite(PIN_RED, redState);
  digitalWrite(PIN_BLUE, blueState);
  tone(PIN_BUZZER, note, 500)
  delay(800);
}

void setup() {
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_BLUE, OUTPUT);
}

void loop() {
  ctrl(HIGH, LOW, 2096);
  ctrl(LOW, HIGH, 3048);
}
