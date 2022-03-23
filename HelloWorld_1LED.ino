#define LED1 7
#define IN 4
// Chris Guiher 
// Alex Shuster
// Morgan Visnesky

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED1, OUTPUT);
  pinMode(IN,INPUT);
}

// the loop function runs over and over again forever
void loop() 
{
 digitalWrite(LED1, LOW);    // turn the LED off by making the voltage LOW
 if(digitalRead(IN)==LOW)
 {
    digitalWrite(LED1, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);                       // wait for a second
    // wait for a second
    digitalWrite(LED1, LOW);    // turn the LED off by making the voltage LOW
    delay(1000); 
 }
 digitalWrite(LED1,LOW);
}
