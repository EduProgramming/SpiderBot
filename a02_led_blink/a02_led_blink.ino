/**
 * 네오아두보드 LED Blink
 * @Auth TaeJuneJoung
 * @Date 2021.05.28
 * 초록색 LED 0.5초간 ON/OFF 반복
 */

int PIN_GREEN = 10;

void setup() {
  pinMode(PIN_GREEN, OUTPUT);
}

/**
 * loop(): 아두이노에 전원이 들어오고 나서부터 계속 반복
 * 
 * delay(microSeconds);
 * -> 정해진 ms만큼 보드가 멈춤
 */
void loop() {
  digitalWrite(PIN_GREEN, HIGH);
  delay(500);
  digitalWrite(PIN_GREEN, LOW);
  delay(500);
}
