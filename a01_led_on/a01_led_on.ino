/**
 * 네오아두보드 LED 제어
 * @Auth TaeJuneJoung
 * @Date 2021.05.28
 * RGB LED 핀 번호
 * 빨강(RED)    ->  D9
 * 초록(GREEN)  ->  D10
 * 파랑(BLUE)   ->  D11
 */

// 유지보수를 위해서 변수를 사용
int PIN_GREEN = 10;

/**
 * setup(): 아두이노 보드 전원 들어올 때 처음 한번 실행되는 요소
 * 참조 -> 설정부분들을 주로 작성
 * 
 * pinMode(핀번호, 입/출력 설정);
 * : 해당 핀에 대해서 입력(INPUT)인지 출력(OUTPUT)인지 설정
 * 
 * 변수명이 전체가 대문자라면 상수(변하지 않는 값)
 * `const`를 사용한 변수명
 * 
 * digitalWrite(핀번호, 전기신호여부);
 * : 디지털핀에 대해서 전기 신호 여부 선택
 * HIGH -> +전기 제공
 * LOW -> -(Gound) 상태
 */
void setup() {
  pinMode(PIN_GREEN, OUTPUT);
  digitalWrite(PIN_GREEN, HIGH);
}

/**
 * loop(): 아두이노에 전원이 들어오고 나서부터 계속 반복
 */
void loop() {

}
