/**************************************************************
 * AUTHOR(S):    Morgan Visnesky
 * DATE:         04/10/2022
 * FILENAME:     microphone_test.ino
 * ORGANIZATION: Junior Design Team CHI
 * TEAM MEMBERS: 
 *              Chris Guiher 
 *              Alex Shuster
 *              Morgan Visnesky
 *              David Cramer
 *
 * DESCRIPTION: 
 *     Simple test code to ensure microphone functions properly.
 * NOTES:
 **************************************************************/

 boolean readFromMicrophone(int pAnalogPin)
{
  unsigned long startMillis = millis();  // Start of sample window
  const int sampleWindow    = 50; // Sample window width in mS (50 mS = 20Hz)
  int micVal                = 0;
  boolean cheer             = false;
  unsigned long startMillis = millis();  // Start of sample window
  unsigned int peakToPeak   = 0;   // peak-to-peak level
  unsigned int signalMax    = 0;
  unsigned int signalMin    = 1024;

  while (millis() - startMillis < sampleWindow){
    sample = analogRead(pAnalogPin);
    if (sample < 1024){  // toss out spurious readings
       if (sample > signalMax){
         signalMax = sample;  // save just the max levels
       }
       else if (sample < signalMin){
         signalMin = sample;  // save just the min levels
       }
     }
   }
   peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
   double micVal = (peakToPeak * 5.0) / 1024;  // convert to volts

   /* 
    *  For ambient noise, peakToPeak voltage tends to be near negligible. 
    *  When a user speaks near the microphone, peakToPeak increases significantly. 
    *  Can set a minimum threshold (2V?) to successfully show a user input
    */
    
  if (micVal > 2){cheer = true;}
  else{cheer = false;}

  return cheer;
}

const int micPin = 3;

void setup() {
    pinMode(micPin, INPUT);
}

void loop() {
    delay(1000);
    readFromMicrophone(micPin);
}