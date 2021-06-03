/**
 * 네오아두보드 LED Power Ctrl
 * @Auth TaeJuneJoung
 * @Date 2021.06.03
 * 점점 밝아졌다 어두워지기(반복문)
 */
int PIN_GREEN   = 10;

void setup() {
  pinMode(PIN_GREEN, OUTPUT);
}

/**
 * 반복문 for문
 * for (초기값; 조건식; 증감) {
 *   수행문장
 * }
 */
void loop() {
  for (int power = 0; power < 255; power++) {
    analogWrite(PIN_GREEN, power);
    delay(30);
  }
  for (int power = 255; power > 0; power--) {
    analogWrite(PIN_GREEN, power);
    delay(30);
  }
}
