// -----
// LimitedRotator.ino - Example for the RotaryEncoder library.
// This class is implemented for use with the Arduino environment.
// Copyright (c) by Matthias Hertel, http://www.mathertel.de
// This work is licensed under a BSD style license. See http://www.mathertel.de/License.aspx
// More information on: http://www.mathertel.de/Arduino
// -----
// 26.03.2017 created by Matthias Hertel
// -----

// This example checks the state of the rotary encoder in the loop() function.
// The current position is printed on output when changed.
// In addition to the SimplePollRotator example here the range of the rotator is limited to the range 0 - 16 and only incremental steps of 2 are realized.
// To implement this limit the boundaries are checked and eventually the current position is adjusted.
// The internal (physical) position of the rotary encoder library remains by stepping with the increment 1
// so the the logical position is calculated by applying the ROTARYSTEPS factor.

// Hardware setup:
// Attach a rotary encoder with output pins to A2 and A3.
// The common contact should be attached to ground.

#include <Arduino.h>

#include <RotaryEncoder.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define ROTARYSTEPS 1
#define ROTARYMIN 7
#define ROTARYMAX 12

//--- Setup a RoraryEncoder for pins A2 and A3:
RotaryEncoder encoder(A2, A3);

//--- Last known rotary position.
int lastPos = -1;

//--- Active track number (last selection) - initialize to lowest track
int tracknumActive = ROTARYMIN;
int tracknumDisplay;
int tracknumLast;

//---Setup Rotary Encoder switch on pin D2 with other side to ground - active low
int rotarySwitch = 2;

//---knob"___" -used to sense and track knob push switch - push to send trackNumActive to display and Turnout Control Arduino
int knobClick = 1;
int knobClickLast = 1;

bool knobMoving;



void setup()
{
  Serial.begin(115200);
  Serial.println("LimitedRotator example for the RotaryEncoder library.");
  encoder.setPosition(ROTARYMIN / ROTARYSTEPS); // start with the value of ROTARYMIN .

  pinMode(rotarySwitch, INPUT_PULLUP);
  
} // End setup()


void loop()
{
  encoder.tick();

  // get the current physical position and calc the logical position

  int newPos = encoder.getPosition() * ROTARYSTEPS;
  
   /*----------Use of ROTARYMAX inside the if statement: counter will roll from min to max and keep counting in a loop.  To make counter stop at lower limit use ROTARYMIN */
    
  if (newPos < ROTARYMIN)
  {
    encoder.setPosition(ROTARYMAX / ROTARYSTEPS);
    newPos = ROTARYMAX;
  }

  /*------------Use of ROTARYMIN inside the if statement: counter will roll from max to min and keep counting in a loop.  o make counter stop at upper limit use ROTARYMAX. */
  
  else if (newPos > ROTARYMAX)
  {
    encoder.setPosition(ROTARYMIN / ROTARYSTEPS);
    newPos = ROTARYMIN;

  }  // End if newPos
  

  if (lastPos != newPos)
  {
    if (newPos == ROTARYMAX)
    {
      Serial.print("REV LOOP");
      Serial.println();
    }
    else
    {
      Serial.print(newPos);
      Serial.println();
    }
    lastPos = newPos;
    tracknumDisplay = lastPos;

      Serial.print("tracknumDisplay: ");
      Serial.print(tracknumDisplay);
      Serial.println();

      Serial.print("tracknumActive: ");
      Serial.print(tracknumActive);
      Serial.println();
      
  } // End if lastPos

    //------Read the rotarySwitch for new track selection and update the active track 
    knobClick = digitalRead(rotarySwitch);   
    delay(10);
    if(knobClick != knobClickLast)          
    {
      tracknumActive = tracknumDisplay;
    } // End new active track selection    

    
  
} // loop ()

// The End