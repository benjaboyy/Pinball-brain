
int bumpers;

//Configure the settings lights
void settings()
{
    settingArray[0] = "B" + balls_left + twoTargets + triTragets;
}

//When 2 targets are hit
void TwoTargetd()
{
    for (int i = 0; i <= 9; i++)
    {
      digitalWrite(latchPinOut, LOW); 
      shiftOut(dataPinOut, clockPinOut, LSBFIRST, B11111111); 
      shiftOut(dataPinOut, clockPinOut, LSBFIRST, B00000000);
      shiftOut(dataPinOut, clockPinOut, LSBFIRST, settingArray[0]);
      digitalWrite(latchPinOut, HIGH);
      tone(buzzer, 2000); // Send 1KHz sound signal...
      delay(350);
      digitalWrite(latchPinOut, LOW); 
      shiftOut(dataPinOut, clockPinOut, LSBFIRST, B00000000); 
      shiftOut(dataPinOut, clockPinOut, LSBFIRST, B00000000);
      shiftOut(dataPinOut, clockPinOut, LSBFIRST, B00000000);
      digitalWrite(latchPinOut, HIGH);
      noTone(buzzer);     // Stop sound...
      delay(350);
    }
}

//When 2 targets are hit
void TwoTarget()
{   
    int myBits[] = {B1,B0,B10,B00,B100,B000,B1000,B0000,B10000,B00000,B100000,B000000,B1000000,B0000000,B10000000,B00000000};
    int Tone;
    Tone = 2000;
    delayAll = 15;
    for (int i = 0; i <= 5; i++)
    {
      for (int i = 0; i <= 15; i++) {
        digitalWrite(latchPinOut, LOW); 
        shiftOut(dataPinOut, clockPinOut, LSBFIRST, myBits[i]); 
        digitalWrite(latchPinOut, HIGH);
        tone(buzzer, Tone); // Send 'Tone' sound signal...
        Tone = Tone - 10;
        delay(delayAll);
      }
    }
    noTone(buzzer);     // Stop sound...
}

////Start game
//void startGameTune()
//{   
//  digitalWrite(latchPinOut, LOW); 
//  shiftOut(dataPinOut, clockPinOut, LSBFIRST, myBits[i]); 
//  digitalWrite(latchPinOut, HIGH);
//  tone(buzzer, Tone); // Send 1KHz sound signal...
//  Tone = Tone + 10;
//}
