# 함열여고 아두이노 기본 수업:spider:

![](https://img.shields.io/badge/Arduino-Base-lightgrey?style=plastic&logo=arduino&labelColor=00979D&logoColor=FFFFFF)

## Index

### :traffic_light: LED 제어

1. [**a01_led_on**](./a01_led_on/a01_led_on.ino)

RGB LED 중에 초록색만 ON

2. [**a02_led_blink**](./a02_led_blink/a02_led_blink.ino)

초록색 LED Blink

3. [**a03_rgb_led**](./a03_rgb_led/a03_rgb_led.ino)

RGB LED를 이용하여 간단하게 7가지 색상 ON

4. [**a04_pwm_led**](./a04_pwm_led/a04_pwm_led.ino)

LED 빛의 세기를 제어

5. [**a05_pwm_rgb_led**](./a05_pwm_rgb_led/a05_pwm_rgb_led.ino)

RGB LED를 이용하여 다양한 색상 ON

6. [**a06_led_power_ctrl**](./a06_led_power_ctrl/a06_led_power_ctrl.ino)

LED 점점 밝아졌다가 어두워지기(반복문)

7. [**a07_led_power_ctrl**](./a07_led_power_ctrl/a07_led_power_ctrl.ino)

LED 점점 밝아졌다가 어두워지기



### :notes:수동 부저 제어

1. [**b01_buzzer_base**](./b01_buzzer_base/b01_buzzer_base.ino)

부저 소리내보기

2. [**b02_buzzer_and_led**](./b02_buzzer_and_led/b02_buzzer_and_led.ino)

LED와 부저를 이용한 알림

3. [**b03_buzzer_and_led_func**](./b03_buzzer_and_led_func/b03_buzzer_and_led_func.ino)

LED와 부저를 이용한 알림(함수 사용)



### :eyes:초음파 센서

1. [**c01_ultrasonic_base**](./c01_ultrasonic_base/c01_ultrasonic_base.ino)

초음파 센서값 시리얼 모니터 확인해보기

> **응용해볼 수 있는 내용**
>
> 초음파 센서값이 일정 범위 안에 들어오면 다른 센서 작동
>
> ex) 도난장치 경보 알림, 초음파 센서 피아노



### :large_blue_diamond:블루투스 HC06

1. [**d01_bluetooth_setting**](./d01_bluetooth_setting/d01_bluetooth_setting.ino)

블루투스 HC06 이름 설정 바꾸기

2. [**d02_bluetooth_ctrl**](./d02_bluetooth_ctrl/d02_bluetooth_ctrl.ino)

블루투스 HC06 명령어를 보내어 LED Turn On/OFF



### :racing_car:기능 구현

1. [**e01_spider_motor_ctrl**](./e01_spider_motor_ctrl/e01_spider_motor_ctrl.ino)

스파이더 모터 기능 구현하기

2. [**e02_spider_obstacle_avoidance**](./e02_spider_obstacle_avoidance/e02_spider_obstacle_avoidance.ino)

스파이더 장애물 회피 주행



### :triangular_flag_on_post:최종 소스

1. [**f00_spider_bluetooth**](./f00_spider_bluetooth/f00_spider_bluetooth.ino)

교구 배포되어 있는 소스 코드

코딩을 배운 사람이라면 이렇게 작성하지 않기를 권장하는 차원으로 업로드

2. [**f01_spider_devj**](./f01_spider_devj/f01_spider_devj.ino)

생각없이 바로 작성한 소스로 그래도 코딩을 배운 사람이라면 이런식으로는 작성하는 것이 좋습니다.

> **기능**
>
> - 기존 기능
>   1. 구동
>   2. 장애물 회피 주행
> - 추가 기능
>   3. 모터 속도 조절
>   4. 초음파 센서 피아노
>
> 추가 기능은 App에 추가되어 있지 않습니다.

