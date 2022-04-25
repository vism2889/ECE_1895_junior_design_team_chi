/**************************************************************
 * AUTHOR(S):    Morgan Visnesky
 * DATE:         04/10/2022
 * FILENAME:     lcd_messages.h
 * ORGANIZATION: Junior Design Team CHI
 * TEAM MEMBERS: 
 *              Chris Guiher 
 *              Alex Shuster
 *              Morgan Visnesky
 *              David Cramer
 *
 * DESCRIPTION: 
 *     Stores the different messages to be displayed with the LCD
 * NOTES:
 **************************************************************/

#include <Wire.h>
#include "DFRobot_LCD.h"

DFRobot_LCD lcd(16,2);  //16 characters and 2 lines of show

const int score = 25;

 void hailToPittMessage(){
    lcd.init();
    lcd.setCursor(5,0);
    lcd.print("CHEER");
    lcd.setCursor(0,1);
    lcd.print("HAIL TO PITT");
 }

 void lightVictoryLightMessage(){
    lcd.init();
    lcd.setCursor(3,0);
    lcd.print("Light the");
    lcd.setCursor(1,1);
    lcd.print("Victory Light");
 }

 void panthersNoseMessage(){
    lcd.init();
    lcd.setCursor(4,0);
    lcd.print("Rub the");
    lcd.setCursor(1,1);
    lcd.print("Panthers Nose");
 }

void welcomeMessage(){
    lcd.init();
    lcd.setCursor(0,0);
    lcd.print("Pitt Traditions");
    lcd.setCursor(2,1);
    lcd.print("Bop-It Game");
}

void roundSuccessMessage(int pScore){
    lcd.init();
    lcd.setCursor(5,0);
    lcd.print("HORRAY");
    lcd.setCursor(2,1);
    String score_ = String(pScore);
    lcd.print("Score: " + score_);
}

void roundFailMessage(int pScore){
    lcd.init();
    lcd.setCursor(0,0);
    lcd.print("OOPS! Try Again!");
    lcd.setCursor(2,1);
    String score_ = String(pScore);
    lcd.print("Score: " + score_);
}

void gameWonMessage(int pScore){
    lcd.init();
    lcd.setCursor(4,0);
    lcd.print("YOU WON!");
    lcd.setCursor(0,1);
    String score_ = String(pScore);
    lcd.print("Score: " + score_);
}

void gameOverMessage(int pScore){
    lcd.init();
    lcd.setCursor(4,0);
    lcd.print("GAME OVER");
    lcd.setCursor(0,1);
    String score_ = String(pScore);
    lcd.print("Score: " + score_);
}
