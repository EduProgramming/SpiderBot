/**
 * 네오아두보드 블루투스 HC06
 * @Auth TaeJuneJoung
 * @Date 2021.06.03
 * 블루투스 HC06 설정 변경
 */

#include <SoftwareSerial.h>

int PIN_TX = A4;
int PIN_RX = A5;

SoftwareSerial BT(PIN_TX, PIN_RX);

void setup() {
  Serial.begin(9600);
  BT.begin(9600);
}

/**
 * 소스 업로드 후에 시리얼 모니터에서
 * 보드레이트 9600 설정
 * line ending없음 설정 
 * -> 반응 없을시에 '새줄' 이나 다른 것으로도 확인 필요
 * 
 * [로직]
 * 블루투스가 사용 가능하면 블루투스에서 오는 값을 읽어서 시리얼 모니터에 써라
 * 시리얼 모니터가 사용 가능하면 시리얼에서 오는 값을 블루투스로 보내라
 * 
 * 시리얼 모니터 작성
 * AT
 * : 작성후에 엔터 누르면 OK가 출력되어야 정상
 * AT+NAME변경할이름
 * : 여기서 변경할 이름은 영어로 시작해야하며, 영어와 숫자로만 작성 권장
 * 작성후에 엔터 누르면 OK+SETNAME이 나와야함
 * AT+RESET
 * : 블루투스 모듈을 다시 재실행 해줌으로써 적용이 빠르게 해줌
 * 
 * 이외에 AT+PIN, AT+BAUD 등... 명령어 존재하나, 블루투스 제조사마다 상이함
 */
void loop() {
  if (Serial.available()) {
    BT.write(Serial.read());
  }
  if (BT.available()) {
    Serial.write(BT.read());
  }
}
