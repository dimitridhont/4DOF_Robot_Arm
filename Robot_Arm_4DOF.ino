/*
 * Control software for cheap-ass 4DOF acrylic servo powered robot arm
 * ===================================================================
 * 
 * V0.1, 24/08/2021 by Dimitri Dhont
 * 
 * 
 * This code just translates joystick positions into either left/right/up/down
 * There is no "in between", treats the analog input like buttons.
 * 
 * If a joystick is moved to a position, the position of the servo is increased by 1
 * This is followed by a delay to make the motion smooth (and more controllable).
 * When the joystick is released or moved back to the center position, the servo stops
 * but keeps its position.
 * 
 * The servo numbering as seen from above:
 * 
 *         Servo3
 *      +-------+                  //\\
 *      |       |                //   \\
 *      | Servo0|============Servo2
 *      |       |                \\   //
 *      +-------+                  \\//
 *         Servo1
 *
 * NOTE: if your analog inputs are stuck on 1023 (full 5V) this means you have the same
 *       crappy board I received. Check if there is a short between ARef and GND.
 *       If there is, just bend the pin inwards (or cut it off completely) so it does not make
 *       contact with the arduino anymore.
 *
 *
 */





#include <Servo.h>

 

int pinLH = A0;   // Left joystick, horizontal motion
int pinLV = A1;   // Left joystick, vertical motion
int pinRH = A3;   // Right joystick, horizontal motion
int pinRV = A2;   // Right joystick, vertical motion
int pinLB = 2;    // Left button
int pinRB = 4;    // Right button

 
Servo myServo0;
Servo myServo1;
Servo myServo2;
Servo myServo3;

 
byte servoSpeed = 5;    // speed of movement. Increase to slow down
byte pos0= 90;          // inital position of the servo's
byte pos1 = 90;
byte pos2 = 90;
byte pos3 = 90;
byte prevPos0 = 1;
byte prevPos1 = 1;
byte prevPos2 = 1;
byte prevPos3 = 1;


void setup() {
 
  Serial.begin(230400);
  delay(1000);
  Serial.println("Ready!");
 
  pinMode(pinLH, INPUT);
  pinMode(pinLV, INPUT);
  pinMode(pinRH, INPUT);
  pinMode(pinRV, INPUT);
  pinMode(pinLB, INPUT_PULLUP);   // pullup needed as button connects to ground but has no pullup on the board
  pinMode(pinRB, INPUT_PULLUP);   // same here...
 
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
    if(pos1>180 || pos1<20){pos1=20;}       // limit motion on this axis to prevent binding
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
 
  if(digitalRead(pinRB) == LOW || digitalRead(pinLB) == LOW) // return to "zero" position if any button is pressed (before turning off)
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
