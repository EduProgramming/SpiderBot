/**
 * 네오아두보드 RGB LED
 * @Auth TaeJuneJoung
 * @Date 2021.05.28
 * 빛의 3원색을 이용(1)
 * : 세기 이용하지 않은 기본색상 제어
 */
int PIN_RED     =  9;
int PIN_GREEN   = 10;
int PIN_BLUE    = 11;

void setup() {
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE, OUTPUT);
}

/**
 * 주의) 이전의 LED 색상을 꺼주어야 기본 색상을 나타냄
 */
void loop() {
  // 빨강
  digitalWrite(PIN_RED, HIGH);
  digitalWrite(PIN_GREEN, LOW);
  digitalWrite(PIN_BLUE, LOW);
  delay(500);
  // 초록
  digitalWrite(PIN_RED, LOW);
  digitalWrite(PIN_GREEN, HIGH);
  digitalWrite(PIN_BLUE, LOW);
  delay(500);
  // 파랑
  digitalWrite(PIN_RED, LOW);
  digitalWrite(PIN_GREEN, LOW);
  digitalWrite(PIN_BLUE, HIGH);
  delay(500);
  // 노랑
  digitalWrite(PIN_RED, HIGH);
  digitalWrite(PIN_GREEN, HIGH);
  digitalWrite(PIN_BLUE, LOW);
  delay(500);
  // 분홍
  digitalWrite(PIN_RED, HIGH);
  digitalWrite(PIN_GREEN, LOW);
  digitalWrite(PIN_BLUE, HIGH);
  delay(500);
  // 연녹
  digitalWrite(PIN_RED, LOW);
  digitalWrite(PIN_GREEN, HIGH);
  digitalWrite(PIN_BLUE, HIGH);
  delay(500);
  // 하얀
  digitalWrite(PIN_RED, HIGH);
  digitalWrite(PIN_GREEN, HIGH);
  digitalWrite(PIN_BLUE, HIGH);
  delay(500);
}
