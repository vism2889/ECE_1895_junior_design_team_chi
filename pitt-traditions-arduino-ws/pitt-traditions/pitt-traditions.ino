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

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display


// ARRAYS TO HOLD GAME AUDIO
const unsigned char hailToPittSample[]        PROGMEM = {};
const unsigned char panthersNoseSample[]      PROGMEM = {};
const unsigned char victoryLightsSample[]     PROGMEM = {};
const unsigned char hailToPittWinningJingle[] PROGMEM = {};

// GAME MESSAGES FOR LCD DISPLAY 
// -> Some of these may need split into 2 strings so they fit onto the display properly
const String winningMessage       = "GAME OVER. YOU WON!";
const String loosingMessage       = "GAME OVER. YOU LOST!";
const String panthersNoseCommand  = "Rub the Panthers Nose!";
const String victoryLightsCommand = "Light the Victory Lights!";
const String hailToPittCommand    = "Cheer Hail to Pitt!";
const String welcomeMessage       = "PITT TRADITIONS";
const String startMessage         = "Press Start!";

// INPUT VARIABLES THAT MAP TO ARDUINO PINS
const int micPin           = 13;
const int joyStickPin      = 12;
const int photoResistorPin = 2;
const int startSwitch      = 8;

// OUTPUT VARIABLES THAT MAP TO ARDUINO PINS
const int speakerPin       = 4;
const int hexDisplayPin    = 7;

// 'RANDOM' VARIABLES THAT MAP TO ARDUINO PINS
const int randomPin        = 0;

// STATE VARIABLES
int curr_time              = 0;
int command_count          = 0;
int randomNumber;

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
  pinMode(lightDependentResistorPin, INPUT);
  pinMode(startSwitch,               INPUT);
  pinMode(speakerPin,                OUTPUT);
  pinMode(hexDisplayPin,             OUTPUT);

  int timeInterval = 1000 * 7; // seven second time interval to start 
  boolean game_started = false; // value to indicate whether game is active or not

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
  int    vCurrentTime   = millis();
  
  startPlaybackSample(panthersNoseSample, sizeof(panthersNoseSample));
     
  displayMessage(panthersNoseCommand); // Displays command on LCD
     
  if (nose_joy_stick == moved and millis() - vCurrentTime < currTimeInterval)
  {
    Score += 1; 
  }
  else
  {
    gameOver(loosingMessage);
  }
}

/*
 * Method to hold the functionality of the victory_lights command-action.
 */
void victory_lights()
{
  int    vCurrentTime   = millis();
  
  startPlaybackSample(victoryLightsSample, sizeof(victoryLightsSample));
     
  displayMessage(victoryLightsCommand); // Displays command on LCD
  
  if (lightSensorPin == HIGH and millis() - vCurrentTime < currTimeInterval)
  {
    Score += 1; 
  }
  else
  {
    gameOver(loosingMessage);
  }
}

/*
 * Method to hold the functionality of the hail_to_pitt command-action.
 */
void hail_to_pitt()
{
  int    vCurrentTime   = millis();
  
  startPlaybackSample(hailToPittSample, sizeof(hailToPittSample));
     
  displayMessage(hailToPittCommand); // Displays command on LCD
     
  if (microphonePin == HIGH and millis() - vCurrentTime < currTimeInterval)
  {
    Score += 1; 
  }
  else
  {
    gameOver(loosingMessage);
  }
}

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
String pickRamdomCommand()
{
  int random_command = random(3);  
  command_count += 1;
  return random_command;
}

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

}

/*
 * Method to hold the functionality to display current commands and game messages on the LCD display
 */
void displayMessage()
{

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
     
  while(game_started == true)
  {
    
    if (command_count >= 99)
    {
      startPlaybackSample(hailToPittWinningJingle, sizeof(hailToPittWinningJingle));
      displayMessage("GAME OVER. YOU WON!");
      game_started = false;
    }
    
    issuedCommand = pickRandomCommand();
    
    switch(issuedCommand)
    {
      case 0:
        hail_to_pitt();
        break;
      case 1:
        victory_lights();
        break;
      case 2;
        panthers_nose();
        break;
      default:
        raise_application_error();
        break;
    }    
  }
}
