//**************************************************************
//  Name    : Pinball-Brain
//  Author  : Benjamin Vitters
//  Date    : 25 Oct, 2020
//  Modified: 28 Jan 2021
//  Version : 0.6.5
//  Notes   :
//****************************************************************
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);
// Game info
int homeScore;
int bonusScore;
int balls_left;
int mltplyr;
int buttonState = 0;
int delayAll;
const int buzzer = 10;
// ShiftIn
int dataPin = 7;
int clockPin = 8;
int latchPin = 9;
byte switchVar1 = 72;  //00000000
byte switchVar2 = 159; //00000000
// ShiftOut
int dataPinOut = 5;
int latchPinOut = 3;
int clockPinOut = 4;
// Set targets state false, not active
int targetOneSet = false;
int targetTwoSet = false;
int targetOneRSet = false;
int targetTwoRSet = false;
int targetThreeRSet = false;

int twoTargets;
int triTragets;

byte  settingArray[2];
byte  inputArray[2];

void setup()
{
  // initialize the LCD
  lcd.begin();
  setupScreen();
  Serial.begin(9600);
  // set ShiftIn / ShiftOut
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, INPUT);
  pinMode(latchPinOut, OUTPUT);
  pinMode(clockPinOut, OUTPUT);
  pinMode(dataPinOut, OUTPUT);
  pinMode(buzzer, OUTPUT);

  settingArray[0] = B00000000;
  inputArray[0] = B00000000;
  inputArray[1] = B10000000;
  inputArray[2] = B01000000;
  inputArray[3] = B00100000;
  inputArray[4] = B00010000;
  inputArray[5] = B00001000;
  inputArray[6] = B00000100;
  inputArray[7] = B00000010;
  inputArray[8] = B00000001;
}

#include "Animations.h"
#include "Tunes.h"

void setupScreen()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SCORE");
  lcd.setCursor(0, 1);
  lcd.print("BALL");
  homeScore = 0;
  balls_left = 1;
  bonusScore = 30;
  endEffect();
}

void endEffect()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SCORE       ");
  lcd.setCursor(0, 1);
  lcd.print("BALL            ");
  digitalWrite(latchPinOut, LOW);
  shiftOut(dataPinOut, clockPinOut, LSBFIRST, settingArray[0]);
  shiftOut(dataPinOut, clockPinOut, LSBFIRST, B00000000);
  shiftOut(dataPinOut, clockPinOut, LSBFIRST, B00000000);
  shiftOut(dataPinOut, clockPinOut, LSBFIRST, B00000000);
  digitalWrite(latchPinOut, HIGH);
}

void loop() {
  digitalWrite(latchPin, 1);
  delayMicroseconds(20);
  digitalWrite(latchPin, 0);
  switchVar1 = shiftIn(dataPin, clockPin);
  switchVar2 = shiftIn(dataPin, clockPin);
  buttonState = (LOW);
  settings();

  // bumper Mid
  if (switchVar1 == inputArray[3])
  {
    lcd.setCursor(0, 0);
    lcd.print("BUMP!                    ");
    for (int i = 0; i <= 2; i++)
    {
      homeScore++;
    }
    delay(300);
    endEffect();
  }
  // bumper left
  if (switchVar2 == inputArray[2])
  {
    for (int i = 0; i <= 6; i++)
    {
      homeScore++;
    }
    delay(350);
    endEffect();
  }
  lcd.setCursor(6, 0);
  lcd.print(homeScore);
  lcd.setCursor(6, 1);
  lcd.print(balls_left);


  // left under target
  if (switchVar1 == inputArray[1])
  {
    for (int i = 0; i <= 4; i++)
    {
      homeScore++;
    }
    digitalWrite(latchPinOut, LOW);
    shiftOut(dataPinOut, clockPinOut, LSBFIRST, settingArray[0]);
    shiftOut(dataPinOut, clockPinOut, LSBFIRST, B11111111);
    shiftOut(dataPinOut, clockPinOut, LSBFIRST, B00000000);
    digitalWrite(latchPinOut, HIGH);

    delay(350);
    targetOneSet = true;
    endEffect();
  }
  // left upper target
  if (switchVar2 == inputArray[1])
  {
    for (int i = 0; i <= 4; i++)
    {
      homeScore++;
    }
    targetTwoSet = true;
    digitalWrite(latchPinOut, LOW);
    shiftOut(dataPinOut, clockPinOut, LSBFIRST, settingArray[0]);
    shiftOut(dataPinOut, clockPinOut, LSBFIRST, B00000000);
    shiftOut(dataPinOut, clockPinOut, LSBFIRST, B11111111);
    digitalWrite(latchPinOut, HIGH);
    delay(350);
    endEffect();
  }

  //   if live loses
  if (switchVar1 == inputArray[8])
  {
    balls_left--;
    lcd.setCursor(0, 0);
    lcd.print("BALL LOST");
    lcd.setCursor(6, 1);
    lcd.print(balls_left);
    delay(2000);
    lcd.setCursor(0, 0);
    lcd.print("BONUS +");
    lcd.setCursor(7, 0);
    lcd.print(bonusScore * 10);
    lcd.setCursor(0, 1);
    lcd.print("               ");
    lcd.setCursor(0, 1);
    lcd.print(homeScore);
    delay(700);
    mltplyr = bonusScore;

    int myBits[] = {B10101010,B01010101,B10011001,B01100110,B10101010,B01010101,B10011001,B01100110,B10101010,B01010101,B10011001,B01100110,B10101010,B01010101,B10011001,B01100110,B10101010,B01010101,B10011001,B01100110,B10101010,B01010101,B10011001,B01100110,B10101010,B01010101,B10011001,B01100110,B10101010,B01010101,B10011001,B01100110,B10101010,B01010101,B10011001,B01100110,B10101010,B01010101,B10011001,B01100110,B10101010,B01010101,B10011001,B01100110,B10101010,B01010101,B10011001,B01100110,B10101010,B01010101,B10011001,B01100110,B10101010,B01010101,B10011001,B01100110,B10101010,B01010101,B10011001,B01100110,B10101010,B01010101,B10011001,B01100110};
    int Tone;
    Tone = 1500;

    for (int i = 1; i <= mltplyr; i++)
    {
      for (int i = 0; i <= 9; i++)
      {
        homeScore++;
      }
      
      bonusScore--;
      lcd.setCursor(7, 0);
      lcd.print("         ");
      lcd.setCursor(7, 0);
      lcd.print(bonusScore * 10);
      lcd.setCursor(0, 1);
      lcd.print(homeScore);
      digitalWrite(latchPinOut, LOW); 
      shiftOut(dataPinOut, clockPinOut, LSBFIRST, myBits[i]);
      digitalWrite(latchPinOut, HIGH);
      tone(buzzer, Tone); // Send 1KHz sound signal..
      Tone = Tone + 10;
      delay(100);
    }
    noTone(buzzer);     // Stop sound...
    delay(700);
    bonusScore = 1;
    endEffect();
  }

  // plunger shoot
  if (switchVar1 == inputArray[7])
  {
    lcd.setCursor(0, 0);
    lcd.print("LETS GOOOOO!");
    for (int i = 0; i <= 15; i++)
    {
      lcd.setCursor(i, 1);
      lcd.print("+");
      delay(40);
    }
    delay(500);
    endEffect();
  }

  if (targetOneSet == 1 & targetTwoSet == 1) {
    lcd.setCursor(0, 0);
    lcd.print("TARGET BONUS!");
    lcd.setCursor(0, 1);
    lcd.print("+50 points");
    TwoTarget();
    for (int i = 0; i <= 49; i++)
    {
      homeScore++;
    }
    targetOneSet = false;
    targetTwoSet = false;
    bonusScore++;
    delay(10);
    endEffect();
  }

  if (balls_left == 0)
  {
    lcd.setCursor(0, 0);
    lcd.print("GAME OVER       ");
    lcd.setCursor(0, 1);
    lcd.print("TOTAL:          ");
    lcd.setCursor(7, 1);
    lcd.print(homeScore);
    delay(3000);
    setup();
  }

}
byte shiftIn(int myDataPin, int myClockPin) {
  int i;
  int temp = 0;
  int pinState;
  byte myDataIn = 0;
  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin, INPUT);
  for (i = 7; i >= 0; i--)
  {
    digitalWrite(myClockPin, 0);
    delayMicroseconds(2);
    temp = digitalRead(myDataPin);
    if (temp) {
      pinState = 1;
      //set the bit to 0 no matter what
      myDataIn = myDataIn | (1 << i);
    }
    else {
      //turn it off -- only necessary for debuging
      //print statement since myDataIn starts as 0
      //pinState = 0;
    }
    //Debuging print statements
    //Serial.print(pinState);
    //Serial.print("     ");
    //Serial.println (dataIn, BIN);
    digitalWrite(myClockPin, 1);
  }
  //debuging print statements whitespace
  //Serial.println();
  //Serial.println(myDataIn, BIN);
  return myDataIn;
}

//void shiftOut(int myDataPin, int myClockPin, byte myDataOut) {
//// This shifts 8 bits out MSB first,
////on the rising edge of the clock,
////clock idles low
////internal function setup
//int i=0;
//int pinState;
//pinMode(myClockPin, OUTPUT);
//pinMode(myDataPin, OUTPUT);
////clear everything out just in case to
////prepare shift register for bit shifting
//digitalWrite(myDataPin, 0);
//digitalWrite(myClockPin, 0);
////for each bit in the byte myDataOut&#xFFFD;
////NOTICE THAT WE ARE COUNTING DOWN in our for loop
////This means that %00000001 or "1" will go through such
////that it will be pin Q0 that lights.
//for (i=7; i>=0; i--)  {
//digitalWrite(myClockPin, 0);
////if the value passed to myDataOut and a bitmask result
//// true then... so if we are at i=6 and our value is
//// %11010100 it would the code compares it to %01000000
//// and proceeds to set pinState to 1.
//if ( myDataOut & (1<<i) ) {
//pinState= 1;
//}
//else {
//pinState= 0;
//}
////Sets the pin to HIGH or LOW depending on pinState
//digitalWrite(myDataPin, pinState);
////register shifts bits on upstroke of clock pin
//digitalWrite(myClockPin, 1);
////zero the data pin after shift to prevent bleed through
//digitalWrite(myDataPin, 0);
//}
////stop shifting
//digitalWrite(myClockPin, 0);
//}
