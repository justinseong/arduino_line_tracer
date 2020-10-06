#include <SoftwareSerial.h>
#include <AFMotor.h>
AF_DCMotor motor_L(1);              // 모터드라이버 L293D  1: M1에 연결,  4: M4에 연결
AF_DCMotor motor_R(4); 

int trig = 13;
int echo = 12;

void setup() {
  Serial.begin(9600);              // PC와의 시리얼 통신속도
  Serial.println("Eduino Smart Car Start!");

  // turn on motor
  motor_L.setSpeed(255);              // 왼쪽 모터의 속도   
  motor_L.run(RELEASE);
  motor_R.setSpeed(255);              // 오른쪽 모터의 속도   
  motor_R.run(RELEASE);

  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

void loop() {
    int val1 = digitalRead(A0);    // 라인센서1
    int val2 = digitalRead(A5);    // 라인센서2   

    long duration, distance;
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    duration = pulseIn(echo, HIGH);
    distance = duration / 29 / 2; // cm 단위

    Serial.println(distance);
      delay(100);
    
      if (val1 == 0 && val2 == 0) {                   // 직진
        // Serial.print(1);
       motor_L.run(FORWARD); 
       motor_R.run(FORWARD);
      }
      else if (val1 == 0 && val2 == 1) {              // 우회전
        // Serial.print(2);
       motor_L.run(FORWARD); 
       motor_R.run(RELEASE);
      }
      else if (val1 == 1 && val2 == 0) {              // 좌회전
        // Serial.print(3);
        motor_L.run(RELEASE); 
        motor_R.run(FORWARD);
        delay(15);
      } 
      else if (val1 == 1 && val2 == 1) {              // 정지  distance < 5
        // Serial.print(4);
        motor_L.run(RELEASE); 
        motor_R.run(RELEASE);
      }      
           
}
    
