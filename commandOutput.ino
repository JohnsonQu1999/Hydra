#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;
int dormant_signal = 2;
int d_increase_signal = 3;


void setup() 
{     
    //Signal Input Setup
    pinMode(2,INPUT);
    pinMode(3,INPUT);
    pinMode(4,INPUT);
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);  
    lcd.setRGB(245, 176, 65);
    // Print a message to the LCD.
    lcd.print("SYSTEM ACTIVATED");
    delay(2000);
}

void loop() 
{
  if(digitalRead(3)==HIGH){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.setRGB(255, 0, 0);
    lcd.print("SYSTEM STATE:");
    lcd.setCursor(0,1);
    lcd.print("DISTANCE HIGH");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.setRGB(255, 0, 0);
    lcd.print("TRUCK STATE:");
    lcd.setCursor(0,1);
    lcd.print("DANGER STATUS");
    delay(1000);
   }
   else if(digitalRead(2) == HIGH){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.setRGB(0, 255, 0);
    lcd.print("SYSTEM STATE:");
    lcd.setCursor(0,1);
    lcd.print("NORMAL CONDITIONS");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.setRGB(0, 255, 0);
    lcd.print("TRUCK STATE:");
    lcd.setCursor(0,1);
    lcd.print("IDEAL STATUS");
    delay(1000);
   }
   else{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.setRGB(245, 0, 219  );
    lcd.print("NO CONNECTION!");
    lcd.setCursor(0,1);
    lcd.print("SIGNAL LOST");
    delay(1000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.setRGB(245, 0, 219);
    lcd.print("TRUCK STATE:");
    lcd.setCursor(0,1);
    lcd.print("UNKOWN!UNKOWN!");
    delay(1000);
   }
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
