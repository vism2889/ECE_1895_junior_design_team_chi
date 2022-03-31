/**************************************************************
 * AUTHOR(S):    Morgan Visnesky
 * DATE:         03/18/2022
 * FILENAME:     pitt-traditions.ino
 * ORGANIZATION: Junior Design Team CHI
 * TEAM MEMBERS: 
 *              Chris Guiher 
 *              Alex Shuster
 *              Morgan Visnesky
 *              David Cramer
 *
 * DESCRIPTION: 
 *     Driver file for Pitt-Traditions "Bop-it" Arduino application.
 **************************************************************/

// IMPORTED CODE
#include <PCM.h>               // Library for MP3 playback
#include <LiquidCrystal_I2C.h> // Library for I2C LCD display 
#include "pin-mapping.h"       // Project Pin-mapping Definitions
#include "game-samples.h"      // Project Audio Samples
#include "game-messages.h"     // Project game messages

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

// STATE VARIABLES
int currTime      = 0;
int command_count = 0;
int userScore     = 0;
int randomNumber;
int timeInterval = 1000 * 7; // seven second time interval to start 
boolean game_started = false; // value to indicate whether game is active or not

/*
 * Method to hold the base pinMappings to from the arduinos inputs and outputs
 * along with class 'state' variables.
 */
void setup()
{
  // Sets the random seed from noise when analog pin 0 is disconnected
  // Will generate a different seed number each time the application is run
  randomSeed(analogRead(randomPin)); 
  
  pinMode(micPin,                    INPUT);
  pinMode(joyStickPin,               INPUT);
  pinMode(photoResistorPin,          INPUT);
  pinMode(startSwitch,               INPUT);
  pinMode(speakerPin,                OUTPUT);
  pinMode(hexDisplayPin,             OUTPUT);

  // I2C LCD INIT
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print(welcomeMessage);
  lcd.setCursor(2,1);
  lcd.print(startMessage);
}

/*
 * Method to hold the functionality of the panthers_nose command-action.
 */
void panthers_nose()
{
  boolean completedTaskInTime = false;
  startPlayback(panthersNoseSample, sizeof(panthersNoseSample));
  displayMessage(panthersNoseCommand); // Displays command on LCD
  
  currTime = millis();
     
  while (millis() - currTime < timeInterval)
  {
    if (joyStickPin == HIGH)
    {
      userScore += 1; 
      completedTaskInTime = true;
    }
  }

  if (!completedTaskInTime)
  {
    gameOver(loosingMessage);
  }
}

/*
 * Method to hold the functionality of the victory_lights command-action.
 */
void victory_lights()
{
  boolean completedTaskInTime = false;
  startPlayback(victoryLightsSample, sizeof(victoryLightsSample));
  displayMessage(victoryLightsCommand); // Displays command on LCD
  
  currTime = millis();

  while (millis() - currTime < timeInterval)
  {
    if (photoResistorPin == HIGH)
    {
      userScore += 1; 
      completedTaskInTime = true;
    }
  }
    
  if (!completedTaskInTime)
  {
    gameOver(loosingMessage);
  }
}

/*
 * Method to hold the functionality of the hail_to_pitt command-action.
 */
void hail_to_pitt()
{
  boolean completedTaskInTime = false;
  startPlayback(hailToPittSample, sizeof(hailToPittSample));
  displayMessage(hailToPittCommand); // Displays command on LCD
  currTime = millis();
  
  while (millis() - currTime < timeInterval)
  {   
    if (readFromMicrophone())
    {
      userScore += 1; 
      completedTaskInTime = true;
    }
  }
  
  if (!completedTaskInTime)
  {
    gameOver(loosingMessage);
  }
}

/*
 * Method to hold functionality that is executed when the game ends
 */
void gameOver(String pMessage)
{
  game_started = false;
  displayMessage(pMessage);
  displayScore();
}

/*
 * Method to hold functionality that chooses a command at random from a list of
 * predefined commands.
 */
int pickRandomCommand()
{
  int random_command = random(3);  
  command_count += 1;
  return random_command;
}

/*
 * Method to hold functionality that is executed when an application error is raised
 */
void raise_application_error()
{
  Serial.print("Application Error Encountered");
}

/*
 * Method to hold the functionality to play the 'Hail to Pitt' song once the game has been won
 */
void playWinningJingle()
{

}

/*
 * Method to hold the functionality to display the current score
 */
void displayScore()
{
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Pitt Traditions");
  lcd.setCursor(2,1);
  lcd.print("Score: " + userScore);
}

/*
 * Method to hold the functionality to display current commands and game messages on the LCD display
 */
void displayMessage(String pMessage)
{
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print(pMessage);
  lcd.setCursor(2,1);
  lcd.print("Score: " + userScore);
}

/*
 * Method to hold the functionality to read an analog value from the microphone
 */
boolean readFromMicrophone()
{
  int micVal = 0;
  boolean cheer = false;
  micVal     = analogRead(micPin);
  if (micVal > 600) 
  {
    cheer = true;
  }
  else 
  {
    cheer = false;
  }

  return cheer;
}

/*
 * Main application loop that holds the overarching logic flow for the pitt-traditions
 * Bop-It game.
 */
void loop()
{
  if (startSwitch == HIGH)
  {
    game_started = true;
  }
  else
  {
    game_started = false;
  }

  // GAME PLAY LOGIC FLOW
  while(game_started == true)
  {
    if (command_count >= 99)
    {
      //startPlaybackSample(hailToPittWinningJingle, sizeof(hailToPittWinningJingle));
      displayMessage("GAME OVER. YOU WON!");
      game_started = false;
    }
    else
    {
      int issuedCommand = pickRandomCommand();
    
      switch(issuedCommand)
      {
        case 0:
          hail_to_pitt();
          break;
        case 1:
          victory_lights();
          break;
        case 2:
          panthers_nose();
          break;
        default:
          raise_application_error();
          break;
      } 
    }
  }
}
