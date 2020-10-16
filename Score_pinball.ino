#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);
int homeScore; 
int balls_left; 
const int buttonVisitorDownPin = 9;
const int buttonHomeDownPin = 7;
const int buttonHomePin = 8; 
const int buttonVisitorPin = 10; 
const int buttonResetPin = 13; 
int buttonState = 0;


void setup()
{
	// initialize the LCD
	lcd.begin(); 
	setupScreen();
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
  buttonState = digitalRead(buttonHomePin); 
  if(buttonState == HIGH) 
  { 
    for(int i = 0; i <= 2; i++)
    {
      homeScore++;
    }
    delay(500); 
  } 
    buttonState = digitalRead(buttonVisitorPin); 
  if(buttonState == HIGH) 
  { 
    for(int i = 0; i <= 6; i++)
    {
      homeScore++;
    }
    delay(500); 
  }

   buttonState = digitalRead(buttonResetPin); 
  if(buttonState == HIGH) 
  { 
    setupScreen();
   delay(1000); 
  }
  buttonState = digitalRead(buttonHomeDownPin);
  if(buttonState == HIGH)
  {
    balls_left--;
    delay(500);
  }
  buttonState = digitalRead(buttonVisitorDownPin);
  if(buttonState == HIGH)
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
