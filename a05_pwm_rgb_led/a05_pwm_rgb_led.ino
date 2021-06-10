/**
 * 네오아두보드 RGB LED
 * @Auth TaeJuneJoung
 * @Date 2021.05.28
 * 빛의 3원색을 이용(2)
 */
int PIN_RED = 9;
int PIN_GREEN = 10;
int PIN_BLUE = 11;

/**
 * ledCtrl 함수: RGB LED를 쉽게 제어하기 위한 커스텀 함수
 * @params: int red_power, int green_power, int blue_power
 * red_power: 빨간색의 세기값
 * green_power: 초록색의 세기값
 * blue_power: 파란색의 세기값
 * 
 * params라고 쓴 부분을 파라미터라고 하며, loop문에 ledCtrl을 호출하면서 쓴 숫자들은 아규먼트라고 함
 */
void ledCtrl(int red_power, int green_power, int blue_power) {
  analogWrite(PIN_RED, red_power);
  analogWrite(PIN_GREEN, green_power);
  analogWrite(PIN_BLUE, blue_power);
  delay(500);
}

void setup() {
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE, OUTPUT);
}

/**
 * 해당 부분은 함수와 연관하여 진행
 * 다양한 색상을 나타낼 수 있으니 안에 숫자 바꿔가면서 진행
 */
void loop() {
  ledCtrl(0, 0, 0);
  ledCtrl(100, 0, 0);
  ledCtrl(0, 100, 0);
  ledCtrl(0, 0, 100);
  ledCtrl(100, 150, 0);
  ledCtrl(100, 0, 150);
  ledCtrl(0, 150, 200);
  ledCtrl(150, 70, 210);
  ledCtrl(50, 80, 0);
  ledCtrl(0, 20, 90);
}
