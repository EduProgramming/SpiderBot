/**
 * 네오아두보드 Buzzer
 * @Auth TaeJuneJoung
 * @Date 2021.06.03
 * 부저 소리내보기
 */

int PIN_BUZZER = 3;
/**
 * tone(부저 핀번호, 음계주파수, 울릴시간);
 * : 울릴시간을 주지 않고 tone(부저 핀번호, 음계주파수); 이와 같게도 사용 가능
 * 이렇게 사용할시에 noTone(부저 핀번호);를 사용해줘야 멈출 수 있음
 */
void setup() {
  pinMode(PIN_BUZZER, OUTPUT);
  tone(PIN_BUZZER, 262, 300);
  delay(500);
  tone(PIN_BUZZER, 294);
  delay(300);
  noTone(PIN_BUZZER);
}

void loop() {
  // put your main code here, to run repeatedly:

}
