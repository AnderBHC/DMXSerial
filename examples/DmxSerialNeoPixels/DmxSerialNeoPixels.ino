// - - - - -
// DmxSerialNeoPixels.ino: Sample DMX application for retrieving 3 DMX values:
//
// Copyright (c) 2016 by Matthias Hertel, http://www.mathertel.de
// This work is licensed under a BSD style license. See http://www.mathertel.de/License.aspx
//
// Documentation and samples are available at http://www.mathertel.de/Arduino
// 25.07.2011 creation of the DmxSerial library.
// 10.07.2014 creation of example with NeoPixels
// 04.09.2016 minor improvements and addes as an example to DMXSerial.

// - - - - -

#include <Arduino.h>
#include <DMXSerial.h>

#include "ws2812.h"

// Constants for demo program

const int RedPin =    9;  // PWM output pin for Red Light.
const int GreenPin =  6;  // PWM output pin for Green Light.
const int BluePin =   5;  // PWM output pin for Blue Light.

const int DebugPin =  10;  

#define RedDefaultLevel   5 // 100
#define GreenDefaultLevel 0 // 200
#define BlueDefaultLevel  0 // 255

// number of RGB neopixels, RGB channels are transfered
// warning: try with 12 first and scale up carefully.
#define PIXELS 8

// first DMX start address
#define DMXSTART 1

// number of DMX channels used
#define DMXLENGTH (PIXELS*3)

// Initialize DMXSerial and neo pixel output
void setup () {
  int n;
  DMXSerial.init(DMXProbe);

  // enable pwm outputs
  pinMode(RedPin,   OUTPUT); // sets the digital pin as output
  pinMode(GreenPin, OUTPUT);
  pinMode(BluePin,  OUTPUT);
  
  pinMode(DebugPin,  OUTPUT);

  digitalWrite(10, 1);
  delay(300);
  digitalWrite(10, 0);
  
  DMXSerial.maxChannel(DMXLENGTH); // after 3 * pixel channels, the onUpdate will be called when new data arrived.

  // setup the neopixel output
  setupNeopixel();

  // give them a decent color...
  n = 1;
  for (int p = 0; p < PIXELS; p++) {
    DMXSerial.write(n++, 5);
    DMXSerial.write(n++, 10);
    DMXSerial.write(n++, 20);
  }
  updateNeopixel(DMXSerial.getBuffer() + DMXSTART, PIXELS);

} // setup ()



// do something
void loop() {
  // wait for an incomming DMX packet.
  DMXSerial.receive();

  // read recent DMX values 1..3 and set pwm levels
  analogWrite(RedPin,   DMXSerial.read(1));
  analogWrite(GreenPin, DMXSerial.read(2));
  analogWrite(BluePin,  DMXSerial.read(3));
  
  updateNeopixel(DMXSerial.getBuffer() + DMXSTART, PIXELS);
} // loop()

// The End.



