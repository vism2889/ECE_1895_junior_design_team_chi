/**************************************************************
 * AUTHOR(S):    Morgan Visnesky and Chris Guiher
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
// #include <LiquidCrystal_I2C.h> // Library for I2C LCD display 
#include "pin-mapping.h"       // Project Pin-mapping Definitions
#include "game-samples.h"      // Project Audio Samples
#include "lcd_messages.h"      // Methods that hold LCD messages


// STATE VARIABLES
char dtaUart[15];
char dtaLen = 0;
int currTime      = 0;
int command_count = 0;
int userScore     = 0;
int randomNumber;
int timeInterval = 1000 * 4; // four second time interval to start 
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
  Serial.begin(115200);
  lcd.init();
  welcomeMessage();
}

/*
 * Method to hold the functionality of the panthers_nose command-action.
 */
void panthers_nose()
{
  boolean completedTaskInTime = false;
  startPlayback(panthersNoseSample, sizeof(panthersNoseSample));
  panthersNoseMessage(); // Displays command on LCD
  currTime = millis();
  while (millis() - currTime < timeInterval)
  {
    if (joyStickPin == HIGH)
    {
      userScore += 1; 
      completedTaskInTime = true;
      roundSuccessMessage(userScore);
      delay(1000);
      break;
    }
  }
  if (!completedTaskInTime)
  {
    game_started = false;
    roundFailMessage(userScore);
    
  }
  timeInterval -= 20;
}

/*
 * Method to hold the functionality of the victory_lights command-action.
 */
void victory_lights()
{
  boolean completedTaskInTime = false;
  startPlayback(victoryLightsSample, sizeof(victoryLightsSample));
  lightVictoryLightMessage(); // Displays command on LCD
  currTime = millis();
  while (millis() - currTime < timeInterval)
  {
    //int photoTransState = analogRead(2);
    if (photoResistorPin == HIGH)
    {
      userScore += 1; 
      completedTaskInTime = true;
      roundSuccessMessage(userScore);
      delay(1000);
      break;
    }
  }
  if (!completedTaskInTime)
  {
    game_started = false;
    roundFailMessage(userScore);
  }
  timeInterval -= 20;
}

/*
 * Method to hold the functionality of the hail_to_pitt command-action.
 */
void hail_to_pitt()
{
  boolean completedTaskInTime = false;
  startPlayback(hailToPittSample, sizeof(hailToPittSample));
  hailToPittMessage(); // Displays command on LCD
  currTime = millis();
  while (millis() - currTime < timeInterval)
  {   
    if (readFromMicrophone())
    {
      userScore += 1; 
      completedTaskInTime = true;
      roundSuccessMessage(userScore);
      delay(1000);
      break;
    }
  }
  if (!completedTaskInTime)
  {
    game_started = false;
    roundFailMessage(userScore);
  }
  timeInterval -= 20;
}


/*
 * Method to hold functionality that chooses a command at random from a list of
 * predefined commands.
 */
int pickRandomCommand()
{
  int random_command = random(0,2);  
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
 * Method to hold the functionality to read an analog value from the microphone
 */
boolean readFromMicrophone()
{
  unsigned long startMillis= millis();  // Start of sample window
  const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
  double micVal = 0;
  boolean cheer = false;
  startMillis= millis();  // Start of sample window
  unsigned int peakToPeak = 0;   // peak-to-peak level
  unsigned int signalMax = 0;
  unsigned int signalMin = 1024;
  while (millis() - startMillis < sampleWindow) // collect data for 50 mS
  {
    int sample = analogRead(0);
    if (sample < 1024)  // toss out spurious readings
    {
      if (sample > signalMax)
      {
        signalMax = sample;  // save just the max levels
      }
      else if (sample < signalMin)
      {
        signalMin = sample;  // save just the min levels
      }
    }
  }
  peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
  micVal = (peakToPeak * 5.0) / 1024;  // convert to volts 
  if (micVal > 2) 
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
  if(dtaLen == 11) { // Setups LCD for correct display settings
    int r = (dtaUart[0]-'0')*100 + (dtaUart[1] - '0')*10 + (dtaUart[2] - '0'); 
    int g = (dtaUart[4]-'0')*100 + (dtaUart[5] - '0')*10 + (dtaUart[6] - '0');
    int b = (dtaUart[8]-'0')*100 + (dtaUart[9] - '0')*10 + (dtaUart[10] - '0');
    dtaLen = 0;
    lcd.setRGB(r, g, b);
    lcd.stopBlink();
    lcd.noBlinkLED();
  }// END LCD display settings

  int startState = digitalRead(startSwitch);
  if (startState == HIGH)
  {
    Serial.print("game started");
    game_started = true;
  }
  // else
  // {
  //   game_started = false;
  // }

  // GAME PLAY LOGIC FLOW
  while(game_started == true)
  {
    if (userScore >= 99)
    {
      gameWonMessage(userScore);
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
//        case 2:
//          panthers_nose();
//          break;
        default:
          raise_application_error();
          break;
      } 
    }
  }
}
