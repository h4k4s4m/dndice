//this array represents the 4 digit display, characters above 9 are letters (see letters.h)
int digits[4] = {10, -1, 0, 2};
//Button previous states are initialized to an invalid value and store changes in button presses as they happen. These are used to fire functions only once per press
int buttonPrevState1 = 2;
int buttonPrevState2 = 2;
int buttonPrevState3 = 2;

//Dice stores the potential dice available for rolls
int dice[] = {2, 4, 6, 8, 10, 12, 20};
//Selected dice is represented by an index value relative to the array above
int selectedDice = 0;
//The quantity of dice to roll is stored as a value from 1-9
int selectedQuantity = 1;
//There are 3 menus represented by 0,1 and 2
int currentMenu = 0;
//Rolling causes random numbers to be generated with each shake which gets stored here
int generatedNumber = 0;
//The roll menu has mode 0 (display "roll"), mode 1 (display nothing), and mode 2 (display value of generatedNumber above)
int rolling = 0;
//In order to decrease roll sensitivity to allow people to pick up the dice, we require a number of shakes stored here
int shake = 0;
//timestamps are used to control time based events of detecting the start and stop of a player rolling
unsigned long rtimestamp = millis();