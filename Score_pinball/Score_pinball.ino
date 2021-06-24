#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);
int homeScore; 
int balls_left; 
int latchPin = 8;
int dataPin = 7;
int clockPin = 9;
int buttonState = 0;

byte switchVar1 = 72;  //00000000
byte switchVar2 = 159; //00000000

void setup()
{
	// initialize the LCD
	lcd.begin(); 
	setupScreen();
  Serial.begin(9600);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT); 
  pinMode(dataPin, INPUT);
  pinMode(11, OUTPUT);
  digitalWrite(11, HIGH);
  pinMode(12, OUTPUT);
  digitalWrite(12, HIGH);
}

void setupScreen() 
{ 
  lcd.clear(); 
  lcd.setCursor(0,0); 
  lcd.print("SCORE"); 
  lcd.setCursor(0,1); 
  lcd.print("BALL");
  homeScore = 0; 
  balls_left = 3; 
}

void loop() { 
  digitalWrite(latchPin,1);
  delayMicroseconds(20);
  digitalWrite(latchPin,0);
  switchVar1 = shiftIn(dataPin, clockPin);
  switchVar2 = shiftIn(dataPin, clockPin);
   
  buttonState = (LOW);
  
  if(switchVar1 == B10000000) 
  { 
    digitalWrite(11, LOW);
    for(int i = 0; i <= 2; i++)
    {
      homeScore++;
    }
    delay(200); 
    digitalWrite(11, HIGH);
  } 
  
  if(switchVar1 == B01000000)  
  { 
    digitalWrite(12, LOW);
    for(int i = 0; i <= 6; i++)
    {
      homeScore++;
    }
    delay(200); 
    digitalWrite(12, HIGH);
  }

  if(switchVar1 == B00100000) 
  { 
    setupScreen();
   delay(1000); 
  }
  
  if(switchVar1 == B00010000) 
  {
    balls_left--;
    delay(500);
  }
  if(switchVar1 == B00001000) 
  {
    lcd.setCursor(0,0);
    lcd.print("LETS GOOOOO!"); 
    for(int i = 0; i <= 15; i++)
    {
      lcd.setCursor(i,1);
      lcd.print("+");
      delay(100);
    }
    delay(500);
    lcd.setCursor(0,0); 
    lcd.print("SCORE       "); 
    lcd.setCursor(0,1);
    lcd.print("BALL            "); 
  }
  
  if(balls_left == 0)
  {
    lcd.setCursor(0,0);
    lcd.print("GAME OVER       "); 
    lcd.setCursor(0,1);
    lcd.print("TOTAL:          ");
    lcd.setCursor(7,1);
    lcd.print(homeScore); 
    delay(4000);
    setupScreen();
  }
  
  
   lcd.setCursor(6,0);
   lcd.print(homeScore); 
   lcd.setCursor(6, 1); 
   lcd.print(balls_left); 
}

byte shiftIn(int myDataPin, int myClockPin) { 

  int i;

  int temp = 0;

  int pinState;

  byte myDataIn = 0;

  pinMode(myClockPin, OUTPUT);

  pinMode(myDataPin, INPUT);

  for (i=7; i>=0; i--)

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
