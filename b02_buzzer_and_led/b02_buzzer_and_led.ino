/**
 * 네오아두보드 Buzzer
 * @Auth TaeJuneJoung
 * @Date 2021.06.03
 * 경보알림음 만들기
 */

int PIN_BUZZER = 3;
int PIN_RED = 9;
int PIN_BLUE = 11;

void setup() {
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_BLUE, OUTPUT);
}

void loop() {
  digitalWrite(PIN_RED, HIGH);
  digitalWrite(PIN_BLUE, LOW);
  tone(PIN_BUZZER, 2096, 500)
  delay(800);
  digitalWrite(PIN_RED, LOW);
  digitalWrite(PIN_BLUE, HIGH);
  tone(PIN_BUZZER, 3048, 500)
  delay(800);
}
