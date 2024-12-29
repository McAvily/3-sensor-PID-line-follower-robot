// 8.8 volts

#include <SparkFun_TB6612.h>

//Sensors
int sen1_v = 8;
int sen2_v = 9;
int sen3_v = 10;

//Values 

float Kp = 9.4; //
float Ki = 0.000001;
float Kd = 0.76;//
int P;
int I;
int D;
int lastError = 0;
int post; 

//speed
const uint8_t maxspeeda = 250;
const uint8_t maxspeedb = 250;
const uint8_t basespeeda = 200;
const uint8_t basespeedb = 200;

//MOTOR controls
//left
const int pwmA = 3;
const int m1 = 5;
const int m1u = 4;
//right
const int m2 = 6;
const int m2u = 7;
const int pwmB = 11;
int stby = 12;
int offsetA = 1;
int offsetB = 1;

Motor motor1 = Motor(m1, m1u, pwmA, offsetA, stby);
Motor motor2 = Motor(m2, m2u, pwmB, offsetB, stby);

//btn
const int btn_str = 2;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(btn_str,INPUT_PULLUP);
  pinMode(sen1_v,INPUT);
  pinMode(sen2_v,INPUT);
  pinMode(sen3_v,INPUT);
  pinMode(m1,OUTPUT);
  pinMode(m1u,OUTPUT);
  pinMode(pwmA,OUTPUT);
  pinMode(m2,OUTPUT);
  pinMode(m2u,OUTPUT);
  pinMode(pwmB,OUTPUT);

  while(digitalRead(btn_str)== LOW){}
}

void loop() {

  int sen1 = digitalRead(sen1_v);
  int sen2 = digitalRead(sen2_v);
  int sen3 = digitalRead(sen3_v);

  if(sen1 == 0 && sen2 == 1 && sen3 == 1){
    post = 1000;
  }
  if(sen1 == 0 && sen2 == 0 && sen3 == 1){
    post = 1500;
  }
  if(sen1 == 1 && sen2 == 0 && sen3 == 1){
    post = 2000;
  }
  if(sen1 == 1 && sen2 == 0 && sen3 == 0){
    post = 2500;
  }
  if(sen1 == 1 && sen2 == 1 && sen3 == 0){
    post = 3000;
  }
  
  int error = 2000 - post;
  P = error;
  I = I + error;
  D = error - lastError;
  lastError = error;

  int motorspeed = P*Kp + I*Ki + D*Kd;
  
  int motorspeeda = basespeeda - motorspeed;
  int motorspeedb = basespeedb + motorspeed;
  
  if (motorspeeda > maxspeeda) {
    motorspeeda = maxspeeda;
  }
  if (motorspeedb > maxspeedb) {
    motorspeedb = maxspeedb;
  }
  if (motorspeeda < 0) {
    motorspeeda = -75;
  }
  if (motorspeedb < 0) {
    motorspeedb = -75;
  }
  
  
  forward(motorspeeda, motorspeedb);

}
void forward(int sp1, int sp2) {

  motor1.drive(sp1);
  motor2.drive(sp2);
}
