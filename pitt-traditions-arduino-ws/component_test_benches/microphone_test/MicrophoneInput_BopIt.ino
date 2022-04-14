//Base logic to translate voltage from input to outpt

const int channel1 = 0; // declare pin for input channel 1

const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;

void setup() 
{
   Serial.begin(9600);
}


void loop() 
{
   unsigned long startMillis= millis();  // Start of sample window
   unsigned int peakToPeak = 0;   // peak-to-peak level

   unsigned int signalMax = 0;
   unsigned int signalMin = 1024;

   // collect data for 50 mS
   while (millis() - startMillis < sampleWindow)
   {
      sample = analogRead(0);
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
   double volts = (peakToPeak * 5.0) / 1024;  // convert to volts
   if(volts < 2)
   {
     Serial.println(false);
   }
   else
   {
    Serial.println(true);
   }

   /* 
    *  For ambient noise, peakToPeak voltage tends to be near negligible. 
    *  When a user speaks near the microphone, peakToPeak increases significantly. 
    *  Can set a minimum threshold (2V?) to successfully show a user input
    */
   Serial.println(volts); 
  
}
