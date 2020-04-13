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

#define ROTARYSTEPS 1
#define ROTARYMIN 7
#define ROTARYMAX 12

// Setup a RoraryEncoder for pins A2 and A3:
RotaryEncoder encoder(A2, A3);

// Last known rotary position.
int lastPos = -1;
int testNewPos = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println("LimitedRotator example for the RotaryEncoder library.");
  encoder.setPosition(7 / ROTARYSTEPS); // start with the value of 7.

  
} // setup()

// Read the current position of the encoder and print out when changed.

void loop()
{
  encoder.tick();

  // get the current physical position and calc the logical position

  int newPos = encoder.getPosition() * ROTARYSTEPS;
  int testNewPos = newPos;

  if (newPos < ROTARYMIN)
  {
    /*----------Use of ROTARYMAX here(both lines below): counter will roll from min to max and keep counting in a loop.  Use ROTARYMIN, in both lines to make counter stop at lower limit
    -------------*/

    encoder.setPosition(ROTARYMAX / ROTARYSTEPS);
    newPos = ROTARYMAX;
  }

  else if (newPos > ROTARYMAX)
  {
    /*------------Use of ROTARYMIN here(both lines below): counter will roll from max to min and keep counting in a loop.  Use ROTARYMAX to make counter stop at upper limit.
    --------------*/

    encoder.setPosition(ROTARYMIN / ROTARYSTEPS);
    newPos = ROTARYMIN;
  }
  // if

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
  } // if
} // loop ()

// The End