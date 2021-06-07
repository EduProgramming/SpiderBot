/**
 * 네오아두보드 블루투스 HC06
 * @Auth TaeJuneJoung
 * @Date 2021.06.07
 * 블루투스 HC06 Receive Data
 */

#include <SoftwareSerial.h>

int PIN_TX = A4;
int PIN_RX = A5;

char cmd;
int PIN_GREEN_LED = 10;

SoftwareSerial BT(PIN_TX, PIN_RX);

void setup() {
  BT.begin(9600);
  pinMode(PIN_GREEN_LED, OUTPUT);
}

void loop() {
  if (BT.available()) {
    cmd = BT.read();
    if (cmd == '1') {
      digitalWrite(PIN_GREEN_LED, HIGH);
    } else if (cmd == '2') {
      digitalWrite(PIN_GREEN_LED, LOW);
    }
  }
}
