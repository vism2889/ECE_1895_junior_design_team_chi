/**************************************************************
 * AUTHOR(S):    Morgan Visnesky
 * DATE:         04/10/2022
 * FILENAME:     speaker_test.ino
 * ORGANIZATION: Junior Design Team CHI
 * TEAM MEMBERS: 
 *              Chris Guiher 
 *              Alex Shuster
 *              Morgan Visnesky
 *              David Cramer
 *
 * DESCRIPTION: 
 *     Simple test code to ensure speaker functions properly.
 * NOTES:
 *     Must wire a resistor between pin 11 and negative speaker lead
 *  or between pin 11 and the amplifier.
 **************************************************************/

#include <PCM.h>
#include <Wire.h>
#include "game-samples.h"      // Project Audio Samples

void setup() {
    pinMode(11, OUTPUT);
}

void loop() {
    delay(1000);
    startPlayback(hailToPittSample, sizeof(hailToPittSample));
}
