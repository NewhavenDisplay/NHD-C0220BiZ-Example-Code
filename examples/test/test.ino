//---------------------------------------------------------
/*

test.ino

Program for writing to Newhaven Display's 2x20 Character COG Display with ST7036 controller.

Pick one up today in the Newhaven Display shop!

------> http://www.newhavendisplay.com/nhdc0220bizfsrgbfbw3vm-p-2411.html

------> http://www.newhavendisplay.com/nhdc0220bizfswfbw3v3m-p-2410.html

This code is written for the Arduino.
Copyright (c) 2015 - Newhaven Display International, LLC.

Newhaven Display invests time and resources providing this open source code,
please support Newhaven Display by purchasing products from Newhaven Display!

*/

#include <Wire.h>

int RES = 22;
int ASDA = 20;
int ASCL = 21;

unsigned char text1[]={"  Newhaven Display  "};
unsigned char text2[]={" Clear Display Test "};
unsigned char text3[]={"    COG  Display    "};
unsigned char text4[]={"  2x20  Characters  "};

const char slave2w = 0x3C;  //3E for CiZ (0x7C shifted over 1 bit)  //3C for BiZ (0x78 shifted over 1 bit)
const char comsend = 0x00;
const char datasend = 0x40;
const char line2 = 0xC0;

void show(unsigned char *text)
{
  int n, d;
  d=0x00;
  Wire.beginTransmission(slave2w);
  Wire.write(datasend);
  for(n=0;n<20;n++)
  {
    Wire.write(*text);
    ++text;
  }
  Wire.endTransmission();
}

void nextline(void)
{
  Wire.beginTransmission(slave2w);
  Wire.write(comsend);
  Wire.write(line2);
  Wire.endTransmission();
}

void cleardisplay(void)
{
  Wire.beginTransmission(slave2w);
  Wire.write(comsend);
  Wire.write(0x01);
  Wire.endTransmission();
}

void CiZ_init()
{
  Wire.beginTransmission(slave2w);
  Wire.write(comsend);
  Wire.write(0x39);
  delay(1);
  Wire.write(0x14);
  Wire.write(0x70);
  Wire.write(0x5E);
  Wire.write(0x6D);
  Wire.write(0x0C);
  Wire.write(0x01);
  Wire.write(0x06);
  Wire.endTransmission();
}

void setup() 
{
  pinMode(RES, OUTPUT);
  pinMode(ASCL, OUTPUT);
  pinMode(ASDA, OUTPUT);
  digitalWrite(RES, HIGH);
  //delay(10);
  //digitalWrite(ASCL, LOW);
  //digitalWrite(ASDA, LOW);
  //delay(10);
  Wire.begin();
  delay(10);
  CiZ_init();
  delay(5);
}

void loop() 
{
  show(text1);
  nextline();
  show(text2);
  delay(1500);
  cleardisplay();
  delay(2);

  show(text3);
  nextline();
  show(text4);
  delay(1500);
  cleardisplay();
  delay(2);
}
