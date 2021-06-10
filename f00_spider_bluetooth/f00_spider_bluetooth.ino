
#include <SoftwareSerial.h>
int bluetoothTx = A4;
int bluetoothRx = A5;
SoftwareSerial Bluetooth(bluetoothTx,bluetoothRx);
char cmd;

int left_fw=2;   //DC모터 A 전진
int left_bw=4;   //DC모터 A 후진
int right_fw=7;   //DC모터 B 전진
int right_bw=8;  //DC모터 B 후진
int left_pwm=5;
int right_pwm=6;

int trig=12;  //초음파 트리거 핀
int echo=13;  //초음파 에코 핀
int right_led=A0;
int left_led=10;
int piezo=3;
int ledstate=LOW;

float duration;     // 초음파 센서 센싱 시간
float distance;     // 초음파 센서 센싱 거리

const long interval=200;
unsigned long beforetime=0;
unsigned long current_time;

void setup() {
Bluetooth.begin(9600);  
pinMode(left_fw,OUTPUT);
pinMode(left_bw,OUTPUT);
pinMode(right_fw,OUTPUT);
pinMode(right_bw,OUTPUT);
pinMode(trig,OUTPUT);
pinMode(echo,INPUT);
pinMode(right_led,OUTPUT);
pinMode(left_led,OUTPUT);
pinMode(piezo,OUTPUT);
randomSeed(analogRead(A2));

digitalWrite(right_led,HIGH);
digitalWrite(left_led,HIGH);
delay(500);
digitalWrite(right_led,LOW);
digitalWrite(left_led,LOW);
delay(500);
digitalWrite(right_led,HIGH);
digitalWrite(left_led,HIGH);
delay(500);
digitalWrite(right_led,LOW);
digitalWrite(left_led,LOW);
delay(500);
}
void forward(){                    // 전진
  digitalWrite(left_fw,1);           // PWM 제어를 통한 모터 속도 제어 (0~255까지 가능)
  digitalWrite(left_bw,0);
  digitalWrite(right_fw,1);
  digitalWrite(right_bw,0);
  analogWrite(left_pwm,255);
  analogWrite(right_pwm,255);
}
void backward(){                   // 후진
  digitalWrite(left_fw,0);
  digitalWrite(left_bw,1);
  digitalWrite(right_fw,0);
  digitalWrite(right_bw,1);
  analogWrite(left_pwm,255);
  analogWrite(right_pwm,255);
}
void left_turn(){                // 좌회전
  digitalWrite(left_fw,0);
  digitalWrite(left_bw,1);
  digitalWrite(right_fw,1);
  digitalWrite(right_bw,0);
  analogWrite(left_pwm,255);
  analogWrite(right_pwm,255);
}
void stop_motor(){               // 멈춤
  digitalWrite(left_fw,0);
  digitalWrite(left_bw,0);
  digitalWrite(right_fw,0);
  digitalWrite(right_bw,0);
  digitalWrite(right_led,LOW);
  digitalWrite(left_led,LOW);
}
void right_turn(){               // 우회전
  digitalWrite(left_fw,1);
  digitalWrite(left_bw,0);
  digitalWrite(right_fw,0);
  digitalWrite(right_bw,1);
  analogWrite(left_pwm,255);
  analogWrite(right_pwm,255);
}
void left_Blink(){ 
   unsigned long current_time = millis();
    if(current_time-beforetime >= interval){
      if(ledstate==LOW){
        ledstate=HIGH;
      }else{
        ledstate=LOW;
      }
    digitalWrite(left_led,ledstate);
    tone(piezo,392,100);
     beforetime = current_time; 
    }
}
void right_Blink(){
    unsigned long current_time = millis();
    if(current_time-beforetime >= interval){
      if(ledstate==LOW){
        ledstate=HIGH;
      }else{
        ledstate=LOW;
      }
    digitalWrite(right_led,ledstate);
    tone(piezo,392,100);
     beforetime = current_time; 
    }
}
void back_Blink(){
    unsigned long current_time = millis();
    if(current_time-beforetime >= interval){
      if(ledstate==LOW){
        ledstate=HIGH;
      }else{
        ledstate=LOW;
      }
    digitalWrite(right_led,ledstate);
    digitalWrite(left_led,!ledstate);
    tone(piezo,392,100);
     beforetime = current_time; 
    }
}
void Automatic_driving(){ 
  digitalWrite(trig,HIGH);          // 초음파센서 트리거핀에서 초음파 발생
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  duration = pulseIn(echo,HIGH);     // pulsIn함수는 (핀번호,핀상태)형식으로 사용하며 핀상태가 변할때 핀상태가 유지되었던
                                     //시간을 계산해주는 함수이다.(pulseIn에서"I"는 대문자 i)초음파가 장애물에 부딫치고
                                     //다시 반사되어서 에코핀으로 돌아오는 시간(에코핀이 HIGH 상태를 유지하다가 반사된 초음파가
                                     //들어오면 LOW상태로 변하게 되는데 이때 에코핀이 HIGH상태였던 시간)을 계산하여
                                     //백만분의 1초단위로(ms마이크로세컨드) 반환해준다
  distance = (duration/2)*0.0343;  // 위에서 반환된 시간값을 이용해 거리값을 계산하는 식(음파의 속도는 343m/s => 34300cm/1000000ms => 0.0343cm/1ms)
  Serial.print(distance);   // 거리값 출력
  Serial.println("cm");     //(println에서 "l"은 소문자 L) 문자 "cm"출력 

  if(distance>20){    // 거리값이 20cm보다 크면
      forward();      // 전진
      digitalWrite(right_led,HIGH);
      digitalWrite(left_led,HIGH);
    }
    if(distance<=20){    // 거리값이 20cm보다 작으면
      stop_motor();      // 모터 정지
      delay(100);        //0.1초 기다림
      backward();        //후진
      tone(piezo,392,100);
      delay(200);
      tone(piezo,392,100);
      digitalWrite(right_led,HIGH);
      digitalWrite(left_led,HIGH);
      delay(1400);       //2초동안
      stop_motor();      // 모터 정지
      delay(100);        //0.1초 기다림
      long direction = random(0,2);    // 0 또는 1  난수 생성하여 방향값 반환
        if(direction==0){               // 반환값이 "0"이면
          right_turn();                 // 우회전
          tone(piezo,392,100);
          digitalWrite(right_led,HIGH);
          delay(2000);
          stop_motor(); 
          }else{                          // 반환값이 "1"이면
          left_turn();                  // 좌회전 
          digitalWrite(left_led,HIGH);
          tone(piezo,392,100);
          delay(2000);
          stop_motor(); 
         }     
    } 
}
void loop(){
 if(Bluetooth.available()){
  cmd = Bluetooth.read();
  }
  if(cmd == '2'){    
     forward();  
      digitalWrite(right_led,HIGH);
      digitalWrite(left_led,HIGH);
    }
  
  if(cmd == '4'){                 //좌회전
     left_turn(); 
     left_Blink(); 
    }
  
  
  if(cmd == '6'){                 //우회전
    right_turn();
    right_Blink(); 
  }
  
  if(cmd == '5'){                 //정지
    stop_motor(); 
   
  } 
     
  if(cmd == '8'){                 //후진
    backward(); 
    back_Blink();
  }
   if(cmd =='A'){                 //자율주행   
    Automatic_driving();   
  } 
}
