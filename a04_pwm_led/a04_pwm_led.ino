/**
 * 네오아두보드 RGB LED
 * @Auth TaeJuneJoung
 * @Date 2021.05.28
 * LED 세기 조절
 */
int PIN_GREEN = 10;

void setup() {
  pinMode(PIN_GREEN, OUTPUT);
}

/**
 * analogWrite(핀번호, 세기);
 * : 세기는 디지털핀일 경우 0~255
 *         아날로그핀일 경우 0~1023
 * 세기값의 이유는 초기 설정시 세팅이 되어있음
 * 디지털핀은 2의 8승 경우만큼
 * 아날로그핀은 2의 10승 경우만큼
 */
void loop() {
  analogWrite(PIN_GREEN, 0);
  delay(1000);
  analogWrite(PIN_GREEN, 50);
  delay(1000);
  analogWrite(PIN_GREEN, 150);
  delay(1000);
  analogWrite(PIN_GREEN, 255);
  delay(1000);
}
