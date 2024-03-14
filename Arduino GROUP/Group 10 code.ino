#include <Servo.h> 
// assign LEDs and buttons for player one
int ledPin[] = {5,6,7};
int playerOneButton = 2;
int redLED = 4;
int buttonStateOne = 0;
int yellowLED5 = 0;
int yellowLED6 = 0;
int yellowLED7 = 0;
int counterScoreOne = 0;

// assign LEDs and buttons for player two
int LedPinTwo[] = {8,9,10};
int playerTwoButton = 3;
int buttonStateTwo = 0;
int greenLED8 = 0;
int greenLED9 = 0;
int greenLED10 = 0;
int blueLED = 11;
int counterScoreTwo = 0;

// declare variables
int delayTime; // time delay between lights on/off
int randNumber;
int redLEDOn; 
int blueLEDOn;
int servoPin = 12;
const int buzzer = 13;

// create a servo object 
Servo Servo1;

//setup interrupt, button input and LED outputs
//player one
void setup() {
  Serial.begin(9600);
  counterScoreOne = 0;
  counterScoreTwo = 0;
  Servo1.attach(servoPin);
  attachInterrupt(0, playerOneInput, FALLING); // specify interrupt routine 
  for (int i=0; i<3; i++) {
    pinMode(ledPin[i], OUTPUT);
  }
  pinMode(playerOneButton, INPUT);
  pinMode(redLED, OUTPUT);
  pinMode(buzzer, OUTPUT); 

  //player two
  attachInterrupt(1, playerTwoInput, FALLING); // specify interrupt routine 
  for (int i=0; i<3; i++) {
    pinMode(LedPinTwo[i], OUTPUT);
  }
  pinMode(playerTwoButton, INPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(buzzer, OUTPUT); 
}

//run main program loop
void loop() {
  delayTime = 1000;
  buttonStateOne = digitalRead(playerOneButton);
  buttonStateTwo = digitalRead(playerTwoButton);
  randNumber = random(3); // select a random number
  digitalWrite(ledPin[randNumber], HIGH);
  digitalWrite(LedPinTwo[randNumber], HIGH); // lights the LED with this number at random times 
  delay(delayTime);
  digitalWrite(ledPin[randNumber], LOW);
  digitalWrite(4, LOW);  //explicitly turning the red and the yellow LED's off
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(LedPinTwo[randNumber], LOW);
  digitalWrite(8, LOW);   //explicitly turning the blue and the green LED's off
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  delay(delayTime);

  redLEDOn = digitalRead(redLED);
  if(redLEDOn==HIGH){
  digitalWrite(redLED, LOW);  //if redLED on = turn it off
  }
  blueLEDOn = digitalRead(blueLED); // if blueLED on = turn it off
  if (blueLEDOn == HIGH) {
    digitalWrite(blueLED ,LOW);
  }

  if (counterScoreOne >= 10) {  //checks the score for player one
    //turns all the LED's on
    digitalWrite(5, HIGH);   
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    delay(delayTime);      
    Servo1.write(0);            //turns the servo towards player one
    Serial.println("PLAYER 1 WINS!");
  }
  if (counterScoreTwo >= 10) {    //chceks the score for player twp  
    //turns all the LED's on    
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);    
    digitalWrite(10, HIGH);
    delay(delayTime);
    Servo1.write(180);             //turns the servo towards player two
    Serial.println("PLAYER 2 WINS!");
  }

  if (counterScoreOne >= 10) {
    //turns all the LED's off
    digitalWrite(4, LOW);  
    digitalWrite(5, LOW);  
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    tone(buzzer, 4000); // Sends 4KHz sound signal three times to indicate that the game is over
    delay(500);
    noTone(buzzer);     // stops the sound
    delay(500);            
    tone(buzzer, 4000); 
    delay(500);
    noTone(buzzer);     
    delay(500);           
    tone(buzzer, 4000); 
    delay(500);        
    noTone(buzzer);     
    delay(500);       
    exit(0);
  }
  if (counterScoreTwo >= 10) {
    //turns all the LED'S off
    digitalWrite(8, LOW);   
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    tone(buzzer, 4000); // Sends 4KHz sound signal three times to indicate that the game is over
    delay(500);
    noTone(buzzer);     // stops the sound
    delay(500);            
    tone(buzzer, 4000); 
    delay(500);
    noTone(buzzer);     
    delay(500);           
    tone(buzzer, 4000); 
    delay(500);        
    noTone(buzzer);     
    delay(500);       
    exit(0);
  }

  if (buttonStateOne == LOW && (yellowLED5 != HIGH && yellowLED6 != HIGH && yellowLED7 != HIGH) && 4 != HIGH) { //checks if the button is pressed and the yellow LED'S and the red LED is off
    tone(buzzer, 200); // makes a sound when the button is pressed at an incorrect time
    delay(200);
    noTone(buzzer);     // stops the sound        
  }
  if (buttonStateTwo == LOW && (greenLED8 != HIGH && greenLED9 != HIGH && greenLED10 != HIGH) && 11 != HIGH) { //checks if the button is pressed and the green LED'S and the blue LED is off
    tone(buzzer, 200); 
    delay(200);
    noTone(buzzer);     // stops the sound      
  }            
}
  
void playerOneInput() {
  buttonStateOne = digitalRead(playerOneButton);
  Servo1.write(90);
  yellowLED5 = digitalRead(5);
  yellowLED6 = digitalRead(6);
  yellowLED7 = digitalRead(7);
  if (buttonStateOne == LOW && (yellowLED5 == HIGH || yellowLED6 == HIGH || yellowLED7 == HIGH)) {
    counterScoreOne = counterScoreOne +1;   //counts the score if the button is pressed and if any one of the LED lights are on
    Serial.println(counterScoreOne);
    digitalWrite(redLED, HIGH);
  }
}

void playerTwoInput() {
  buttonStateTwo = digitalRead(playerTwoButton);
  Servo1.write(90);
  greenLED8 = digitalRead(8);
  greenLED9 = digitalRead(9);
  greenLED10 = digitalRead(10);
  if (buttonStateTwo == LOW && (greenLED8 == HIGH || greenLED9 == HIGH || greenLED10 == HIGH)) {
    counterScoreTwo = counterScoreTwo +1;          //counts the score if the button is pressed and if any one of the LED lights are on
    Serial.println(counterScoreTwo);
    digitalWrite(blueLED, HIGH);
  }
}