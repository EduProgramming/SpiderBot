/**
 * 네오아두보드 초음파센서
 * @Auth TaeJuneJoung
 * @Date 2021.06.03
 * 초음파 거리 측정기
 */


int PIN_TRIG = 12;
int PIN_ECHO = 13;

/**
 * Serial -> 시리얼 통신을 사용하기 위한 라이브러리
 * 시리얼 통신은 아두이노 툴에서 개발자가 나오는 값을 확인하기 위해 사용
 * 정확한 표현으로는 디버깅 용도로 사용
 * 
 * Serial.begin(숫자): 보드레이트 속도
 * 1초에 몇 bit를 통신속도로 둘 것인지
 * : 300, 1200, 2400, 4800, 9600, 19200...
 * 보편적으로 아두이노 우노에서는 9600을 많이 사용
 * 소스 업로드를 위해서 115200을 사용하기도 함
 */
void setup() {
  Serial.begin(9600);
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
}

/**
 * pulseIn(핀번호, HIGH/LOW, timeout);
 * : 해당 핀이 지정한 HIGH나 LOW로 올때가지 기다린 후,
 * 반대값이 올때까지 시간을 잽니다. 정해진 timeout 안에 펄스가 시작되지 않으면 0 반환
 * timeout을 기재하지 않을 시에 1초(=1000ms)가 기본값 -> pulseIn(핀번호, HIGH/LOW);
 */
void loop() {
  digitalWrite(PIN_TRIG, LOW);
  digitalWrite(PIN_ECHO, LOW);
  delayMicroseconds(2);
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);
  float duration = pulseIn(PIN_ECHO, HIGH);
  float distance = duration / 29.0 / 2;
  Serial.print(distance);
  Serial.println("cm") // ln이 붙으면 해당 내용 출력 후 개행(Enter)
}
