#include "global_variables.h"
//the pins of 4-digit 7-segment display attach to pin2-13 respectively
#include "pins.h"
//functions that display letter/number patterns when called
#include "letters.h"
//functions to display to a 4 digit 7 segment and menu items
#include "menu_display.h"

void setup()
{
  //set all the pins of the LED display as output
  pinMode(d1, OUTPUT);
  pinMode(d2, OUTPUT);
  pinMode(d3, OUTPUT);
  pinMode(d4, OUTPUT);
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(p, OUTPUT);

  //s1 and s2 are tactile switches, s3 is a tilt switch. All marked as input
  pinMode(s1, INPUT);
  pinMode(s2, INPUT);
  pinMode(s3, INPUT);
}
/***************************************/
void loop()
{
  //The display function decides what LED's on the display turn on based on values in the global variables digits array
  display();
  //The menu function checks for button presses and controls the rest of the global variables to navigate the menu, select options and roll the dice
  menu();
}
/**************************************/