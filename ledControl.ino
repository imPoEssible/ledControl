/*
  Shift Register Example
 for 74HC595 shift register

 This sketch turns reads serial input and uses it to set the pins
 of a 74HC595 shift register.

 Hardware:
 * 74HC595 shift register attached to pins 2, 3, and 4 of the Arduino,
 as detailed below.
 * LEDs attached to each of the outputs of the shift register

 Created 22 May 2009
 Created 23 Mar 2010
 by Tom Igoe

 */

//Pin connected to latch pin (ST_CP) of 74HC595
const int glatchPin = 7;
//Pin connected to clock pin (SH_CP) of 74HC595
const int gclockPin = 4;
////Pin connected to Data in (DS) of 74HC595
const int gdataPin = 9;

//Pin connected to latch pin (ST_CP) of 74HC595
const int blatchPin = 6;
//Pin connected to clock pin (SH_CP) of 74HC595
const int bclockPin = 3;
////Pin connected to Data in (DS) of 74HC595
const int bdataPin = 10;

//Pin connected to latch pin (ST_CP) of 74HC595
const int rlatchPin = 5;
//Pin connected to clock pin (SH_CP) of 74HC595
const int rclockPin = 2;
////Pin connected to Data in (DS) of 74HC595
const int rdataPin = 11;

void setup() {
  //set pins to output because they are addressed in the main loop
  pinMode(glatchPin, OUTPUT);
  pinMode(gdataPin, OUTPUT);
  pinMode(gclockPin, OUTPUT);
  pinMode(blatchPin, OUTPUT);
  pinMode(bdataPin, OUTPUT);
  pinMode(bclockPin, OUTPUT);
  pinMode(rlatchPin, OUTPUT);
  pinMode(rdataPin, OUTPUT);
  pinMode(rclockPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("reset");
}

void loop() {
  if (Serial.available() > 0) {
    // ASCII '0' through '9' characters are
    // represented by the values 48 through 57.
    // so if the user types a number from 0 through 9 in ASCII, 
    // you can subtract 48 to get the actual value:
    int bitToSet = Serial.parseInt();

    if (bitToSet == 24){
      reset_LEDs();
    }
    else {
    // write to the shift register with the correct bit set high:
    registerWrite(bitToSet, HIGH);
    }
  }
}

// This method sends bits to the shift register:

void registerWrite(int whichPin, int whichState) {
// the bits you want to send
  byte bitsToSend = 0;

  if (whichPin >= 0 && whichPin <= 7){
    // turn off the output so the pins don't light up
    // while you're shifting bits:
    digitalWrite(glatchPin, LOW);
  
    // turn on the next highest bit in bitsToSend:
    bitWrite(bitsToSend, whichPin, whichState);
  
    // shift the bits out:
    shiftOut(gdataPin, gclockPin, MSBFIRST, bitsToSend);
  
    // turn on the output so the LEDs can light up:
    digitalWrite(glatchPin, HIGH);
  }

  if (whichPin >= 8 && whichPin <= 15){
    // turn off the output so the pins don't light up
    // while you're shifting bits:
    digitalWrite(blatchPin, LOW);

    whichPin = map(whichPin, 8, 15, 0, 7);
  
    // turn on the next highest bit in bitsToSend:
    bitWrite(bitsToSend, whichPin, whichState);
  
    // shift the bits out:
    shiftOut(bdataPin, bclockPin, MSBFIRST, bitsToSend);
  
    // turn on the output so the LEDs can light up:
    digitalWrite(blatchPin, HIGH);
  }

  if (whichPin >= 16 && whichPin <= 23){
    // turn off the output so the pins don't light up
    // while you're shifting bits:
    digitalWrite(rlatchPin, LOW);

    whichPin = map(whichPin, 16, 23, 0, 7);
  
    // turn on the next highest bit in bitsToSend:
    bitWrite(bitsToSend, whichPin, whichState);
  
    // shift the bits out:
    shiftOut(rdataPin, rclockPin, MSBFIRST, bitsToSend);
  
    // turn on the output so the LEDs can light up:
    digitalWrite(rlatchPin, HIGH);
  }
}

void reset_LEDs() {
  for (int i = 0; i < 24; i++){
    registerWrite(i, LOW);
  }
}
