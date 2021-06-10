/**
 * 네오아두보드 LED Power Ctrl
 * @Auth TaeJuneJoung
 * @Date 2021.06.03
 * 점점 밝아졌다 어두워지기
 */
int PIN_GREEN   = 10;

int power = 0;
int sw = 1;

void setup() {
  pinMode(PIN_GREEN, OUTPUT);
}

/**
 * 조건문 if문
 * if (조건식) {
 *   수행문장
 * }
 * 
 * 조건문 if ~ else if ~ else문
 * if (조건식1) {
 *   수행문장1
 * } else if (조건식2) {
 *   수행문장2
 * } else {
 *   수행문장3
 * }
 */
void loop() {
  analogWrite(PIN_GREEN, power);
  power += sw;
  delay(30);
  if (power == 0) {
    sw = 1;
  } else if (power == 255) {
    sw = -1;
  }
}
