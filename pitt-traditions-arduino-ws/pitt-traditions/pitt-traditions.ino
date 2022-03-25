// AUTHOR(S):    Morgan Visnesky
// DATE:         03/18/2022
// FILENAME:     pitt-traditions.ino
// ORGANIZATION: Junior Design Team CHI
//
// DESCRIPTION: 
//      Driver file pitt-traditions Bop-it arduino application

// LIBRARY IMPORTS

// INPUT VARIABLES
Const int micPin           = 13;
Const int joyStickPin      = 12;
Const int photoResistorPin = 2;
Const int startButton      = 8;

// OUTPUT VARIABLES
Const int speakerPin       = 4;
Const int hexDisplayPin    = 7;

// STATE VARIABLES
Int curr_time              = 0;
Int command_count          = 0;

void setup()
{
    pinMode(micPin, INPUT);
    pinMode(joyStickPin, INPUT);
    pinMode(lightDependentResistorPin, INPUT);
    pinMode(startButton, INPUT);

    pinMode(speakerPin, OUTPUT);
    pinMode(hexDisplayPin, OUTPUT);

    timeInterval = getCurrTime();
}

void panthers_nose()
{
     Time = currTime;
     Command = rubNose;
     SpeakCommand();
     if (nose_joy_stick == moved and getTime() - Time < currTimeInterval)
     {
          Score += 1; 
      }
      else
     {
          displayFinalScore();
          game_started = false;
     }
}

void victory_lights()
{
     Time = currTime;
     Command = victoryLights;
     Speak-command();
     if (lightSensorPin == HIGH and getTime() - Time< currTimeInterval)
     {
          Score += 1; 
      }
      else
     {
          displayFinalScore();
          game_started = false;
     }
}

void hail_to_pitt()
{
     Time = currTime;
     Command = hailToPitt;
     Speak-command();
     if (microphonePin == HIGH and getTime() - Time < currTimeInterval)
     {
          Score += 1; 
      }
      else
     {
          displayFinalScore();
          game_started = false;
     }
}

void pickRamdomCommand()
{
    Random_command = random(
                                     hail_to_pitt(), 
                                     victory_lights(), 
                                      panthers_nose());  
    Command_count += 1;
    Return random_command;
}

void loop()
{
     while(game_started == true)
    {
        if (command_count <= 99)
        {
              playWinningJingle();
              Game_started = false;
         }
        Command = pickRandomCommand();
     }
}