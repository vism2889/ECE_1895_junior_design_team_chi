#define LED1 6
#define LED2 8
#define LED3 7

#define IN 4

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(IN, INPUT); 
}

// the loop function runs over and over again forever
void loop() 
{
  digitalWrite(LED1, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(LED2, LOW); 
   digitalWrite(LED3, LOW); 
 if(digitalRead(IN)==LOW)
  {
    digitalWrite(LED1, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);                       // wait for a second
    digitalWrite(LED1, LOW);    // turn the LED off by making the voltage LOW
    digitalWrite(LED2, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);                       // wait for a second
    digitalWrite(LED2, LOW);    // turn the LED off by making the voltage LOW
    digitalWrite(LED3, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);                       // wait for a second
    digitalWrite(LED3, LOW);    // turn the LED off by making the voltage LOW
  }// wait for a second
  digitalWrite(LED1, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(LED2, LOW); 
   digitalWrite(LED3, LOW); 
  
}
