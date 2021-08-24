#include <Servo.h>

 

int pinLH = A0;
int pinLV = A1;
int pinRH = A3;
int pinRV = A2;
int pinLB = 2;
int pinRB = 4;

 
Servo myServo0;
Servo myServo1;
Servo myServo2;
Servo myServo3;

 
byte servoSpeed = 5;
byte pos0= 90;
byte pos1 = 90;
byte pos2 = 90;
byte pos3 = 90;
byte prevPos0 = 1;
byte prevPos1 = 1;
byte prevPos2 = 1;
byte prevPos3 = 1;
unsigned long prevMillis = 0;

void setup() {
  // put your setup code here, to run once:
 
  Serial.begin(230400);
  delay(1000);
  Serial.println("Ready!");
 
  pinMode(pinLH, INPUT);
  pinMode(pinLV, INPUT);
  pinMode(pinRH, INPUT);
  pinMode(pinRV, INPUT);
  pinMode(pinLB, INPUT_PULLUP);
  pinMode(pinRB, INPUT_PULLUP);
 
  myServo0.attach(9);
  myServo1.attach(5);
  myServo2.attach(10);
  myServo3.attach(11);
 
  myServo0.write(pos0);
  myServo1.write(pos1);
  myServo2.write(pos2);
  myServo3.write(pos3);
}
 
void loop() {
 
  while(map(analogRead(pinLH), 0, 1023, -2, 2) == 2)
  {
    pos0--;
    if(pos0>180){pos0=0;}
    myServo0.write(pos0);
    prevPos0 = pos0;
    writePositions();
    delay(servoSpeed);
  }
  while(map(analogRead(pinLH), 0, 1023, -2, 2) == -2)
  {
    pos0++;
    if(pos0>180){pos0=180;}
    myServo0.write(pos0);
    prevPos0 = pos0;
    writePositions();
    delay(servoSpeed);
  }
  while(map(analogRead(pinLV), 0, 1023, -2, 2) == 2)
  {
    pos1--;
    if(pos1>180 || pos1<20){pos1=20;}       // limit motion on this axis
    myServo1.write(pos1);
    prevPos1 = pos1;
    writePositions();
    delay(servoSpeed);
  }
  while(map(analogRead(pinLV), 0, 1023, -2, 2) == -2)
  {
    pos1++;
    if(pos1>180){pos1=180;}
    myServo1.write(pos1);
    prevPos1 = pos1;
    writePositions();
    delay(servoSpeed);
  }
 while(map(analogRead(pinRH), 0, 1023, -2, 2) == -2)
 {
  pos2--;
  if(pos2>180){pos2=0;}
  myServo2.write(pos2);
  prevPos2 = pos2;
  writePositions();
  delay(servoSpeed);
 }
 while(map(analogRead(pinRH), 0, 1023, -2, 2) == 2)
 {
  pos2++;
  if(pos2>180){pos2=180;}
  myServo2.write(pos2);
  prevPos2 = pos2;
  writePositions();
  delay(servoSpeed);
 }
 while(map(analogRead(pinRV), 0, 1023, -2, 2) == -2)
 {
  pos3--;
  if(pos3>180){pos3=0;}
  myServo3.write(pos3);
  prevPos3 = pos3;
  writePositions();
  delay(servoSpeed);
 }
 while(map(analogRead(pinRV), 0, 1023, -2, 2) == 2)
 {
  pos3++;
  if(pos3>180){pos3=180;}
  myServo3.write(pos3);
  prevPos3 = pos3;
  writePositions();
  delay(servoSpeed);
 }
 
  if(digitalRead(pinRB) == LOW || digitalRead(pinLB) == LOW) // return to "zero" position (before turning off)
  {
    bool dir0 = false;
    bool dir1 = false;
    bool dir2 = false;
    bool dir3 = false;
    Serial.println("Let's go home!");
    
    if(pos0>90) {dir0 = true;}
    if(pos1>90) {dir1 = true;}
    if(pos2>90) {dir2 = true;}
    if(pos3>90) {dir3 = true;}
    
    while(pos0 != 90)
    {
      if(dir0)
      {
        pos0--;
      }
      else
      {
        pos0++;
      }
      myServo0.write(pos0);
      writePositions();
      delay(10);
    }
    while(pos1 != 90)
    {
      if(dir1)
      {
        pos1--;
      }
      else
      {
        pos1++;
      }
      myServo1.write(pos1);
      writePositions();
      delay(10);
    }
    while(pos2 != 90)
    {
      if(dir2)
      {
        pos2--;
      }
      else
      {
        pos2++;
      }
      myServo2.write(pos2);
      writePositions();
      delay(10);
    }
    while(pos3 != 90)
    {
      if(dir3)
      {
        pos3--;
      }
      else
      {
        pos3++;
      }
      myServo3.write(pos3);
      writePositions();
      delay(10);
    }
    
  }
}

 

void writePositions()
{
  Serial.print(" 0:");
  Serial.print(pos0);
  Serial.print(" 1:");
  Serial.print(pos1);
  Serial.print(" 2:");
  Serial.print(pos2);
  Serial.print(" 3:");
  Serial.println(pos3);
  
}

