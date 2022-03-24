// AUTHOR(S):    Morgan Visnesky
// DATE:         03/18/2022
// FILENAME:     pitt-traditions.ino
// ORGANIZATION: Junior Design Team CHI
//
// DESCRIPTION: 
//      Driver file pitt-traditions Bop-it arduino application

// LIBRARY IMPORTS

// INPUT VARIABLES
const int micPin           = 13;
const int joyStickPin      = 12;
const int photoResistorPin = 2;
const int startButton      = 8;

// OUTPUT VARIABLES
const int speakerPin       = 4;
const int hexDisplayPin    = 7;

// STATE VARIABLES
int curr_time              = 0;
int command_count          = 0;

/*
 * Method to hold the base pinMappings to from the arduinos inputs and outputs
 * along with class 'state' variables.
 */
void setup()
{
  pinMode(micPin, INPUT);
  pinMode(joyStickPin, INPUT);
  pinMode(lightDependentResistorPin, INPUT);
  pinMode(startButton, INPUT);

  pinMode(speakerPin, OUTPUT);
  pinMode(hexDisplayPin, OUTPUT);

  int timeInterval = 1000 * 7; // seven second time interval to start 
  boolean game_started = false; // value to indicate whether game is active or not
}

/*
 * Method to hold the functionality of the panthers_nose command-action.
 */
void panthers_nose()
{
  int    vCurrentTime   = millis();
  String vIssuedCommand = "Rub the Panthers Nose!";
     
  speakCommand(vIssuedCommand);
     
  if (nose_joy_stick == moved and getTime() - Time < currTimeInterval)
  {
    Score += 1; 
  }
  else
  {
    displayScore();
    game_started = false;
  }
}

/*
 * Method to hold the functionality of the victory_lights command-action.
 */
void victory_lights()
{
  int    vCurrentTime   = millis();
  String vIssuedCommand = "Light the Victory Lights!";
     
  speakCommand(vIssuedCommand);
  if (lightSensorPin == HIGH and getTime() - Time< currTimeInterval)
  {
    Score += 1; 
  }
  else
  {
    displayScore();
    game_started = false;
  }
}

/*
 * Method to hold the functionality of the hail_to_pitt command-action.
 */
void hail_to_pitt()
{
  int    vCurrentTime   = millis();
  String vIssuedCommand = "Cheer Hail to Pitt!";
     
  speakCommand(vIssuedCommand);
     
  if (microphonePin == HIGH and getTime() - Time < currTimeInterval)
  {
    Score += 1; 
  }
  else
  {
    displayScore();
    game_started = false;
  }
}

/*
 * Method to hold functionality that allows  game to speak commands to the player.
 */
void speakCommand()
{
  
}

/*
 * Method to hold functionality that chooses a command at random from a list of
 * predefined commands.
 */
String pickRamdomCommand()
{
  String random_command = random(hail_to_pitt(), 
                                 victory_lights(), 
                                 panthers_nose());  
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
 * Main application loop that holds the overarching logic flow for the pitt-traditions
 * Bop-It game.
 */
void loop()
{
  if (startButton == HIGH)
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
      playWinningJingle();
      game_started = false;
    }
    issuedCommand = pickRandomCommand();
    switch(issuedCommand)
    {
      case HAIL_TO_PITT:
        hail_to_pitt();
        break;
      case VICTORY_LIGHTS:
        victory_lights();
        break;
      case PANTHERS_NOSE;
        panthers_nose();
        break;
      default:
        raise_application_error();
        break;
    }
      
       
    }
  }
}
