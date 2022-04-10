#include <Wire.h>
#include "DFRobot_LCD.h"

char dtaUart[15];
char dtaLen = 0;

DFRobot_LCD lcd(16,2);  //16 characters and 2 lines of show

void setup() {
  Serial.begin(115200);
    lcd.init();
    lcd.setCursor(0,0);
    lcd.print("Pitt Traditions");
    lcd.setCursor(0,1);
    lcd.print("Score: ");
}

void loop() {
    if(dtaLen == 11) {
        int r = (dtaUart[0]-'0')*100 + (dtaUart[1] - '0')*10 + (dtaUart[2] - '0');          // get r
        int g = (dtaUart[4]-'0')*100 + (dtaUart[5] - '0')*10 + (dtaUart[6] - '0');
        int b = (dtaUart[8]-'0')*100 + (dtaUart[9] - '0')*10 + (dtaUart[10] - '0');
        
        dtaLen = 0;
        
        lcd.setRGB(r, g, b);
        lcd.stopBlink();
        lcd.noBlinkLED();
    }
    
    String num = String(millis()/1000);
    lcd.setCursor(0,1);
    lcd.print("Score: " + num);
}

void serialEvent() {
    while(Serial.available()) {
        dtaUart[dtaLen++] = Serial.read();
    }
}
