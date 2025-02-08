#include <Servo.h>
#include <SoftwareSerial.h>

// Khai báo các chân kết nối với HC-05
const int RX_PIN = 2; // Arduino nhận dữ liệu từ HC-05 (TXD của HC-05)
const int TX_PIN = 3; // Arduino gửi dữ liệu tới HC-05 (RXD của HC-05)

// Khởi tạo đối tượng SoftwareSerial
SoftwareSerial bluetooth(RX_PIN, TX_PIN);
// Create servo objects
Servo servo1;
Servo servo2;

// Define the pins for the servos
const int servoPin1 = 12;
const int servoPin2 = 13;
//Infra red
const int irPin = A5;  
int irValue = 0;   

int mode = 0;

//Motor l298n
int pwmRight = 11;
int mRight = 9; 
int dirRight = 10;
int pwmLeft = 6;
int mLeft = 7; 
int dirLeft = 8;

//Line sensor
int sensor[5] = {0,0,0,0,0};
int error, last_error, MV,pid_l,pid_r,D,D1,D2,D3,I,I1,I2,I3,P,Pd, bitSensor;
int Max_MV;
unsigned char Kp = 30; //10;
unsigned char Kd = 5;
unsigned char Ki = 2;
unsigned char Ts = 1;
unsigned char maxPwm = 125;

//count intersection and junction
int countIntersec = 0;
int countLeftJunc = 0;
int countRightJunc = 0;
byte next=0;

void(* resetFunc) (void) = 0;

void setup(){
  Serial.begin(9600);
  Serial3.begin(9600);
  bluetooth.begin(9600);
  //Motor l298
  pinMode(pwmRight, OUTPUT);
  pinMode(mRight, OUTPUT); 
  pinMode(dirRight, OUTPUT); 
  pinMode(pwmLeft, OUTPUT);
  pinMode(mLeft, OUTPUT); 
  pinMode(dirLeft, OUTPUT); 
  //Line sensor
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);

  //Infra red
  pinMode(irPin, INPUT);
  //  serrvo
  servo1.attach(servoPin1);
  servo2.attach(servoPin2);

  // Start by moving the servos to the initial position
  servo1.write(25);
  servo2.write(20);    
}

void loop(){
  
  mission();
  
}

void readSensor(){
  sensor[0] = digitalRead(A0); sensor[1] = digitalRead(A1); sensor[2] = digitalRead(A2);
  sensor[3] = digitalRead(A3); sensor[4] = digitalRead(A4); 
}
void goDrive(){
  int a=100;
  readSensor();
  int s1 = digitalRead(A0);  //Left Most Sensor
  int s2 = digitalRead(A1);  //Left Sensor
  int s3 = digitalRead(A2);  //Middle Sensor
  int s4 = digitalRead(A3);  //Right Sensor
  int s5 = digitalRead(A4);  //Right Most Sensor

  //if only middle sensor detects black line
  if((s1 == 1) && (s2 == 1) && (s3 == 0) && (s4 == 1) && (s5 == 1))
{
  //going forward with full speed 
  analogWrite(pwmLeft, a); //you can adjust the speed of the motors from 0-255
  analogWrite(pwmRight, a); //you can adjust the speed of the motors from 0-255
  digitalWrite(mLeft, HIGH);
  digitalWrite(dirLeft, LOW);
  digitalWrite(mRight, HIGH);
  digitalWrite(dirRight, LOW);
}

//if only left sensor detects black line
if((s1 == 1) && (s2 == 0) && (s3 == 1) && (s4 == 1) && (s5 == 1))
{
  //going right with full speed 
  analogWrite(pwmLeft, a); //you can adjust the speed of the motors from 0-255
  analogWrite(pwmRight, a); //you can adjust the speed of the motors from 0-255
  digitalWrite(mLeft, HIGH);
  digitalWrite(dirLeft, LOW);
  digitalWrite(mRight, LOW);
  digitalWrite(dirRight, LOW);
}

//if only left most sensor detects black line
if((s1 == 0) && (s2 == 1) && (s3 == 1) && (s4 == 1) && (s5 == 1))
{
  //going right with full speed 
  analogWrite(pwmLeft, a); //you can adjust the speed of the motors from 0-255
  analogWrite(pwmRight, a); //you can adjust the speed of the motors from 0-255
  digitalWrite(mLeft, HIGH);
  digitalWrite(dirLeft, LOW);
  digitalWrite(mRight, LOW);
  digitalWrite(dirRight, HIGH);
}

//if only right sensor detects black line
if((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 0) && (s5 == 1))
{
  //going left with full speed 
  analogWrite(pwmLeft, a); //you can adjust the speed of the motors from 0-255
  analogWrite(pwmRight, a); //you can adjust the speed of the motors from 0-255
  digitalWrite(mLeft, LOW);
  digitalWrite(dirLeft, LOW);
  digitalWrite(mRight, HIGH);
  digitalWrite(dirRight, LOW);
}

//if only right most sensor detects black line
if((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 1) && (s5 == 0))
{
  //going left with full speed 
  analogWrite(pwmLeft, a); //you can adjust the speed of the motors from 0-255
  analogWrite(pwmRight, a); //you can adjust the speed of the motors from 0-255
  digitalWrite(mLeft, LOW);
  digitalWrite(dirLeft, HIGH);
  digitalWrite(mRight, HIGH);
  digitalWrite(dirRight, LOW);
}

//if middle and right sensor detects black line
if((s1 == 1) && (s2 == 1) && (s3 == 0) && (s4 == 0) && (s5 == 1))
{
  //going left with full speed 
  analogWrite(pwmLeft, a); //you can adjust the speed of the motors from 0-255
  analogWrite(pwmRight, a); //you can adjust the speed of the motors from 0-255
  digitalWrite(mLeft, LOW);
  digitalWrite(dirLeft, LOW);
  digitalWrite(mRight, HIGH);
  digitalWrite(dirRight, LOW);
}

//if middle and left sensor detects black line
if((s1 == 1) && (s2 == 0) && (s3 == 0) && (s4 == 1) && (s5 == 1))
{
  //going right with full speed 
  analogWrite(pwmLeft, a); //you can adjust the speed of the motors from 0-255
  analogWrite(pwmRight, a); //you can adjust the speed of the motors from 0-255
  digitalWrite(mLeft, HIGH);
  digitalWrite(dirLeft, LOW);
  digitalWrite(mRight, LOW);
  digitalWrite(dirRight, LOW);
}

//if middle, left and left most sensor detects black line
if((s1 == 0) && (s2 == 0) && (s3 == 0) && (s4 == 1) && (s5 == 1))
{
  //going right with full speed 
  analogWrite(pwmLeft, a); //you can adjust the speed of the motors from 0-255
  analogWrite(pwmRight, a); //you can adjust the speed of the motors from 0-255
  digitalWrite(mLeft, HIGH);
  digitalWrite(dirLeft, LOW);
  digitalWrite(mRight, LOW);
  digitalWrite(dirRight, LOW);
}

//if middle, right and right most sensor detects black line
if((s1 == 1) && (s2 == 1) && (s3 == 0) && (s4 == 0) && (s5 == 0))
{
  //going left with full speed 
  analogWrite(pwmLeft, a); //you can adjust the speed of the motors from 0-255
  analogWrite(pwmRight, a); //you can adjust the speed of the motors from 0-255
  digitalWrite(mLeft, LOW);
  digitalWrite(dirLeft, LOW);
  digitalWrite(mRight, HIGH);
  digitalWrite(dirRight, LOW);
}

//if all sensors are on a black line
if((s1 == 0) && (s2 == 0) && (s3 == 0) && (s4 == 0) && (s5 == 0))
{
  //stop
  digitalWrite(mLeft, LOW);
  digitalWrite(dirLeft, LOW);
  digitalWrite(mRight, LOW);
  digitalWrite(dirRight, LOW);
}
}
void goDrive2(){
  readSensor();
  int a=80;
  int s1 = digitalRead(A0);  //Left Most Sensor
  int s2 = digitalRead(A1);  //Left Sensor
  int s3 = digitalRead(A2);  //Middle Sensor
  int s4 = digitalRead(A3);  //Right Sensor
  int s5 = digitalRead(A4);  //Right Most Sensor

  //if only middle sensor detects black line
  if((s1 == 1) && (s2 == 1) && (s3 == 0) && (s4 == 1) && (s5 == 1))
{
  //going forward with full speed 
  analogWrite(pwmLeft, a); //you can adjust the speed of the motors from 0-255
  analogWrite(pwmRight, a); //you can adjust the speed of the motors from 0-255
  digitalWrite(mLeft, HIGH);
  digitalWrite(dirLeft, LOW);
  digitalWrite(mRight, HIGH);
  digitalWrite(dirRight, LOW);
}

//if only left sensor detects black line
if((s1 == 1) && (s2 == 0) && (s3 == 1) && (s4 == 1) && (s5 == 1))
{
  //going right with full speed 
  analogWrite(pwmLeft, a); //you can adjust the speed of the motors from 0-255
  analogWrite(pwmRight, a); //you can adjust the speed of the motors from 0-255
  digitalWrite(mLeft, HIGH);
  digitalWrite(dirLeft, LOW);
  digitalWrite(mRight, LOW);
  digitalWrite(dirRight, LOW);
}

//if only left most sensor detects black line
if((s1 == 0) && (s2 == 1) && (s3 == 1) && (s4 == 1) && (s5 == 1))
{
  //going right with full speed 
  analogWrite(pwmLeft, a); //you can adjust the speed of the motors from 0-255
  analogWrite(pwmRight, a); //you can adjust the speed of the motors from 0-255
  digitalWrite(mLeft, HIGH);
  digitalWrite(dirLeft, LOW);
  digitalWrite(mRight, LOW);
  digitalWrite(dirRight, HIGH);
}

//if only right sensor detects black line
if((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 0) && (s5 == 1))
{
  //going left with full speed 
  analogWrite(pwmLeft, a); //you can adjust the speed of the motors from 0-255
  analogWrite(pwmRight, a); //you can adjust the speed of the motors from 0-255
  digitalWrite(mLeft, LOW);
  digitalWrite(dirLeft, LOW);
  digitalWrite(mRight, HIGH);
  digitalWrite(dirRight, LOW);
}

//if only right most sensor detects black line
if((s1 == 1) && (s2 == 1) && (s3 == 1) && (s4 == 1) && (s5 == 0))
{
  //going left with full speed 
  analogWrite(pwmLeft, a); //you can adjust the speed of the motors from 0-255
  analogWrite(pwmRight, a); //you can adjust the speed of the motors from 0-255
  digitalWrite(mLeft, LOW);
  digitalWrite(dirLeft, HIGH);
  digitalWrite(mRight, HIGH);
  digitalWrite(dirRight, LOW);
}

//if middle and right sensor detects black line
if((s1 == 1) && (s2 == 1) && (s3 == 0) && (s4 == 0) && (s5 == 1))
{
  //going left with full speed 
  analogWrite(pwmLeft, a); //you can adjust the speed of the motors from 0-255
  analogWrite(pwmRight, a); //you can adjust the speed of the motors from 0-255
  digitalWrite(mLeft, LOW);
  digitalWrite(dirLeft, LOW);
  digitalWrite(mRight, HIGH);
  digitalWrite(dirRight, LOW);
}

//if middle and left sensor detects black line
if((s1 == 1) && (s2 == 0) && (s3 == 0) && (s4 == 1) && (s5 == 1))
{
  //going right with full speed 
  analogWrite(pwmLeft, a); //you can adjust the speed of the motors from 0-255
  analogWrite(pwmRight, a); //you can adjust the speed of the motors from 0-255
  digitalWrite(mLeft, HIGH);
  digitalWrite(dirLeft, LOW);
  digitalWrite(mRight, LOW);
  digitalWrite(dirRight, LOW);
}

//if middle, left and left most sensor detects black line
if((s1 == 0) && (s2 == 0) && (s3 == 0) && (s4 == 1) && (s5 == 1))
{
  //going right with full speed 
  analogWrite(pwmLeft, a); //you can adjust the speed of the motors from 0-255
  analogWrite(pwmRight, a); //you can adjust the speed of the motors from 0-255
  digitalWrite(mLeft, HIGH);
  digitalWrite(dirLeft, LOW);
  digitalWrite(mRight, LOW);
  digitalWrite(dirRight, LOW);
}

//if middle, right and right most sensor detects black line
if((s1 == 1) && (s2 == 1) && (s3 == 0) && (s4 == 0) && (s5 == 0))
{
  //going left with full speed 
  analogWrite(pwmLeft, a); //you can adjust the speed of the motors from 0-255
  analogWrite(pwmRight, a); //you can adjust the speed of the motors from 0-255
  digitalWrite(mLeft, LOW);
  digitalWrite(dirLeft, LOW);
  digitalWrite(mRight, HIGH);
  digitalWrite(dirRight, LOW);
}

//if all sensors are on a black line
if((s1 == 0) && (s2 == 0) && (s3 == 0) && (s4 == 0) && (s5 == 0))
{
  //stop
  digitalWrite(mLeft, LOW);
  digitalWrite(dirLeft, LOW);
  digitalWrite(mRight, LOW);
  digitalWrite(dirRight, LOW);
}
}
void goDrive1(){   
  readSensor();
  bitSensor = ((sensor[0]*1)+(sensor[1]*2)+(sensor[2]*4)+(sensor[3]*8)+(sensor[4]*16));
  switch(bitSensor){
    case 0b01111: error = 4; break;
    case 0b00111: error = 3; break;
    case 0b10111: error = 2; break;
    case 0b10011: error = 1; break;
    case 0b11011: error = 0; break;
    case 0b11001: error = -1; break;
    case 0b11101: error = -2; break;
    case 0b11100: error = -3; break;
    case 0b11110: error = -4; break;
  }
  
  Max_MV = Kp*6; 
  P = Kp * error;
  D1 = Kd*8;
  D2 = D1 / Ts;
  D3 = error - last_error;
  D = D2 * D3;

  I1 = Ki/8;
  I2 = error + last_error;
  I3 = I1 * I2;
  I = I3 * Ts; 
  last_error = error;
  
  Pd = P + D;
  MV = P + I;
  
  if(MV>=-Max_MV && MV<=Max_MV){ 
    pid_l = maxPwm + MV;
    pid_r = maxPwm - MV;
    if (pid_l < 0) pid_l = 0;
    if (pid_l > 255) pid_l = 255;
    if (pid_r < 0) pid_r = 0;
    if (pid_r > 255) pid_r = 255;
    forward(pid_r,pid_l);
  }
  else if(MV<-Max_MV){
    turnLeft(100,200);
  }
  else if(MV>Max_MV){
    turnRight(200,100);
  }
  else{
    forward(pid_r,pid_l);
  }
}

void forward(int valLeft, int valRight){
  digitalWrite(mRight, HIGH);
  digitalWrite(dirRight, LOW);
  analogWrite(pwmRight, valRight);
  digitalWrite(mLeft, HIGH);
  digitalWrite(dirLeft, LOW);
  analogWrite(pwmLeft, valLeft);
  
}

void backward(int valLeft, int valRight){
  digitalWrite(mRight, LOW);
  digitalWrite(dirRight, HIGH);
  analogWrite(pwmRight, valRight);
  digitalWrite(mLeft, LOW);
  digitalWrite(dirLeft, HIGH);
  analogWrite(pwmLeft, valLeft);
  while(sensor[1]==0){readSensor();}
  while(sensor[2]==1){readSensor();}
  while(sensor[3]==0){readSensor();}
} 


void stright1(int valLeft, int valRight){
  digitalWrite(mRight, HIGH);
  digitalWrite(dirRight, LOW);
  analogWrite(pwmRight, valRight);
  digitalWrite(mLeft, HIGH);
  digitalWrite(dirLeft, LOW);
  analogWrite(pwmLeft, valLeft);
  while(sensor[4]==0){readSensor();}
}

void stright2(int valLeft, int valRight){
  digitalWrite(mRight, HIGH);
  digitalWrite(dirRight, LOW);
  analogWrite(pwmRight, valRight);
  digitalWrite(mLeft, HIGH);
  digitalWrite(dirLeft, LOW);
  analogWrite(pwmLeft, valLeft);
  while(sensor[0]==0){readSensor();}
}

void turnRight(int valLeft, int valRight){ 
  digitalWrite(mRight, HIGH);
  digitalWrite(dirRight, LOW);
  analogWrite(pwmRight, valRight);
  digitalWrite(mLeft, LOW);
  digitalWrite(dirLeft, HIGH);
  analogWrite(pwmLeft, valLeft);
  while(sensor[3]==1){readSensor();}
  while(sensor[2]==0){readSensor();}
  while(sensor[1]==1){readSensor();} 
}
void turnRight1(int valLeft, int valRight){ 
  digitalWrite(mRight, HIGH);
  digitalWrite(dirRight, LOW);
  analogWrite(pwmRight, valRight);
  digitalWrite(mLeft, LOW);
  digitalWrite(dirLeft, HIGH);
  analogWrite(pwmLeft, valLeft);
  while(sensor[4]==0){readSensor();}
  while(sensor[3]==0){readSensor();}
  while(sensor[2]==0){readSensor();}
  while(sensor[1]==1){readSensor();}
}
void turnLeft(int valLeft, int valRight){
  digitalWrite(mRight, LOW);
  digitalWrite(dirRight, HIGH);
  analogWrite(pwmRight, valRight);
  digitalWrite(mLeft, HIGH);
  digitalWrite(dirLeft, LOW);
  analogWrite(pwmLeft, valLeft);
  while(sensor[1]==0){readSensor();}
  while(sensor[2]==1){readSensor();}
  while(sensor[3]==0){readSensor();}
  
}
void turnLeft1(int valLeft, int valRight){
  digitalWrite(mRight, LOW);
  digitalWrite(dirRight, HIGH);
  analogWrite(pwmRight, valRight);
  digitalWrite(mLeft, HIGH);
  digitalWrite(dirLeft, LOW);
  analogWrite(pwmLeft, valLeft);
  while(sensor[0]==0){readSensor();}
  while(sensor[1]==0){readSensor();}
  while(sensor[2]==0){readSensor();}
  while(sensor[3]==1){readSensor();}

  
}

void turnBack(int valLeft, int valRight){ 
  digitalWrite(mRight, HIGH);
  digitalWrite(dirRight, LOW);
  analogWrite(pwmRight, valRight);
  digitalWrite(mLeft, LOW);
  digitalWrite(dirLeft, HIGH);
  analogWrite(pwmLeft, valLeft);
  while(sensor[4]==1){readSensor();}
  while(sensor[3]==1){readSensor();}
  while(sensor[2]==1){readSensor();}
  while(sensor[1]==0){readSensor();}
}

void stopDrive(){
  digitalWrite(dirRight, HIGH);
  digitalWrite(mRight, HIGH);
  analogWrite(pwmRight, 0);
  digitalWrite(dirLeft, HIGH);
  digitalWrite(mLeft, HIGH);
  analogWrite(pwmLeft, 0);  
}

void endDrive(){
  digitalWrite(dirRight, HIGH);
  digitalWrite(mRight, HIGH);
  analogWrite(pwmRight, 0);
  digitalWrite(dirLeft, HIGH);
  digitalWrite(mLeft, HIGH);
  analogWrite(pwmLeft, 0); 
  while(sensor[0]==0){readSensor();}
  while(sensor[1]==0){readSensor();}
  while(sensor[2]==0){readSensor();}
  while(sensor[3]==0){readSensor();}
  while(sensor[4]==0){readSensor();} 
}

void standBy(){
  while (digitalRead(irPin) == LOW){
   stopDrive(); 
  }
}

void defaults(){
  next = 1;
  countIntersec = 0;
  countLeftJunc = 0;
  countRightJunc = 0;
}

//Count intersection
int intersection(){
  readSensor();
  if(sensor[4]==0 && sensor[0]==0){
    countIntersec++;
    stopDrive();
  }
  return countIntersec;
}

//Count left junction
int leftJunction(){
  readSensor();
  if(sensor[0]==0 && sensor[1]==0 && sensor[3]==1 && sensor[4]==1){
    countLeftJunc++;
  }
  return countLeftJunc;
}

//Count right junction
int rightJunction(){
  readSensor();
  if(sensor[4]==0 && sensor[3]==0 && sensor[2]==0 && sensor[0]==1){
    countRightJunc++;
  }
  return countRightJunc;
}
void servo_nang(){
  for (int i=20;i<=50;i++){
    servo1.write(i+5);
    servo2.write(i);
    delay(35);
  }
}
void servo_ha(){
  for (int i=50;i>=20;i--){
    servo1.write(i+5);
    servo2.write(i);
    delay(35);
  }
}

void table_1(){  
  defaults();
  while(next){ 
    goDrive2(); 
    if(intersection() == 1){ //Intersection 1, Start
    next=0;
    } 
  }  
  stopDrive();
  delay(500);
  // nang khung
  servo_nang();
  backward(110, 110);
  turnBack(110, 110); 
  
  defaults();
  while(next){       
    goDrive();
    if(rightJunction() == 1){ //Found right junction stright
    next=0; 
    }     
  }
  stright1(110, 110);
  goDrive();
  
  defaults();
  while(next){             
    irValue = digitalRead(irPin);
    if(irValue == LOW){              
      goDrive();
      if(leftJunction() == 1){ //Found left junction turn left
      next=0; 
      }     
    }
    if(irValue == HIGH){      
      stopDrive();
    }    
  }
  stright2(110,110);
  forward(110,110);
  delay(1600);
  turnLeft1(110, 110); 
  delay(1400);
  defaults();
  while(next){ 
    goDrive2();
    if(intersection() == 1){ //Finish intersection
    next=0; 
    }    
  }
      stopDrive();
      delay(1000);
      //standBy();
      // ha khung hang
      servo_ha();
      backward(110, 110);
      turnBack(110, 110);
   
  defaults();
  while(next){ 
    goDrive();
    if(intersection() == 1){ //Found intersection turn right
    next=0; 
    }    
  }
  forward(110,110);
  delay(1600);
  turnRight(110, 110);

  defaults();
  while(next){ 
    goDrive();
    if(leftJunction() == 1){ //Found left junction, stright
    next=0; 
    }    
  }
  stright2(110, 110);
  goDrive();
    
  defaults();
  while(next){ 
    goDrive();
    if(intersection() == 1){ //Intersection finish, Stop
    next=0; 
    }    
  }
  resetFunc(); 
  
}

void table_2(){ 
  defaults();
  while(next){
    goDrive(); 
    if(intersection() == 1){ //Intersection 1, Start
    next=0; 
    }    
  } 
  stopDrive();
  delay(500);
  servo_nang();
  backward(100, 100);
  turnBack(110, 110); 
  
  defaults();
  while(next){       
    goDrive();
    if(rightJunction() == 1){ //Found right junction stright
    next=0; 
    }     
  }
  stright1(110, 110); 
  goDrive();  
  
  defaults();
  while(next){ 
    goDrive();
    if(leftJunction() == 1){ //Found leftJunction stright
    next=0; 
    }    
  }
  stright2(110, 110);
  goDrive();
  
  defaults();
  while(next){ 
    irValue = digitalRead(irPin);
    if(irValue == LOW){              
      goDrive();
      if(intersection() == 1){ //Found left junction turn left
      next=0; 
      }     
    }
    if(irValue == HIGH){      
      stopDrive();
    }
  }
  forward(150,150);
  delay(1200);
  turnLeft1(100, 100);
  //delay(1000);
  defaults();
  while(next){ 
    goDrive2();
    if(intersection() == 1){ //Finish intersection
    next=0; 
    }    
  }
      stopDrive();
      delay(1000);
      //standBy();
      servo_ha();
      backward(110, 110);               
      turnBack(100, 100);
   
  defaults();
  while(next){ 
    goDrive();
    if(rightJunction() == 1){ //Found right junction turn right
    next=0; 
    }    
  }
  forward(130,130);
  delay(1200);
  turnRight1(130, 130);
  delay(1000);
  defaults();
  while(next){ 
    goDrive();
    if(rightJunction() == 1){ //Next right Junction stright
      next=0; 
      } 
  }          
  stright1(110, 110);
  goDrive();
  
  defaults();
  while(next){ 
    goDrive();
    if(leftJunction() == 1){ //Next left Junction stright
      next=0; 
      } 
  }          
  stright2(110, 110);
  goDrive();
  
  defaults();
  while(next){ 
    goDrive();
    if(intersection() == 1){ //Intersection 7, Stop
    next=0; 
    }     
  }
  resetFunc();
}

void table_3(){   
  defaults();
  while(next){
    goDrive2(); 
    if(intersection() == 1){ //Intersection 1, Start
    next=0; 
    }    
  } 
  stopDrive();
  delay(500);
  servo_nang();
  backward(100, 100);
  turnBack(100, 100);
   
  defaults();
  while(next){       
    goDrive();
    if(rightJunction() == 1){ //Found right junction stright
    next=0; 
    }     
  }
  stright1(100, 100);
  goDrive(); 
  
  defaults();
  while(next){ 
    goDrive();
    if(leftJunction() == 1){ //Found leftJunction stright
    next=0; 
    }    
  }
  stright2(100, 100);
  goDrive(); 
    
  defaults();
  while(next){ 
    irValue = digitalRead(irPin);
    if(irValue == LOW){              
      goDrive();
      if(intersection() == 1){ //Found left junction turn left
      next=0; 
      }     
    }
    if(irValue == HIGH){      
      stopDrive();
    }
  }
  forward(110,110);
  delay(1600);
  turnRight1(110, 110);
  
  defaults();
  while(next){ 
    goDrive2();
    if(intersection() == 1){ //Finish intersection
    next=0; 
    }    
  }
      stopDrive();
      delay(1000);
      //standBy();
      servo_ha();
      backward(100, 100);                
      turnBack(100, 100);
   
  defaults();
  while(next){ 
    goDrive();
    if(leftJunction() == 1){ //Found left junction turn left
    next=0; 
    }    
  }
  forward(110,110);
  delay(1600);
  turnLeft1(110, 110);
  delay(1300);
  defaults();
  while(next){       
    goDrive();
    if(rightJunction() == 1){ //Found right junction stright
    next=0; 
    }     
  }
  stright1(110, 110); 
  goDrive(); 
  
  defaults();
  while(next){ 
    goDrive();
    if(leftJunction() == 1){ //Found leftJunction stright
    next=0; 
    }    
  }
  stright2(100, 100);
  goDrive();
  
  defaults();
  while(next){ 
    goDrive();
    if(intersection() == 1){ //Intersection 7, Stop
    next=0; 
    }    
  }
  resetFunc();
}

void goHome(){ 
  defaults();
  while(next){
    goDrive(); 
    if(intersection() == 1){ //Intersection 1, Start
    next=0; 
    }    
  }
  stopDrive();
  delay(500);
  backward(100, 100);
  turnBack(100, 100); 
  
  defaults();
  while(next){       
    goDrive();
    if(rightJunction() == 1){ //Found right junction stright
    next=0; 
    }     
  }
  forward(110,110);
  delay(1600);
  turnRight1(110, 110);
  delay(1350);
  defaults();
  while(next){ 
    goDrive2();
    if(intersection() == 1){ //Intersection 7, Stop
    next=0; 
    }    
  }
  stright1(100,100);
  
  defaults();
  while(next){ 
    goDrive2();
    if(intersection() == 1){ //Intersection 7, Stop
    next=0; 
    }    
  }
  stopDrive();
  delay(500);
  backward(100, 100);
  turnBack(100, 100);
  //delay(1100); 
  //backward(100, 100);
  //delay(2000);
  stopDrive();  
  resetFunc(); 
}
void homegoto(){
  defaults();
  while(next){
    goDrive2(); 
    if(intersection() == 1){ //Intersection 1, Start
    next=0; 
    }    
  }
  stright1(100,100);
  defaults();
  while(next){
    goDrive2(); 
    if(intersection() == 1){ //Intersection 1, Start
    next=0; 
    }    
  }
  forward(110,110);
  delay(1500);
  turnLeft1(100,100);
  //delay(1300);
  defaults();
  while(next){ 
    goDrive();
    if(intersection() == 1){ //Intersection 7, Stop
    next=0; 
    }    
  }
  resetFunc();
}


void mission(){
  goDrive2();
  if(sensor[4] == 0 && sensor[0] == 0){ 
  stopDrive(); 
  mode = Serial3.read();
  //mode = bluetooth.read();
  //mode=4;
  switch(mode){
    case '1': 
      table_1();
      break;

    case '2':
      table_2();
      break;

    case '3':
      table_3();
      break;

    case '4':
      goHome();
    case '5':
      homegoto();
    case 0:
      stopDrive();
      break;
    }
  }
}
