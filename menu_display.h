//generates a dice roll given number of sides and number of rolls as type and quantity respectively
int generateNumber(int type, int quantity){
  int x=0;
  for (int i=0; i<quantity; i++){
    x += random(1,(type+1));
  }
  return x;
}

//Roll action and results logic
void roll()
{

//Switch to control display (via variable that is checked)
  switch (rolling)
  {
  default:
    break;
  case 0:
     //displays 'roll'
    digits[0] = 12;
    digits[1] = 13;
    digits[2] = 14;
    digits[3] = 14;
    break;
  case 1:
    //displays nothing (blank)
    digits[0] = -1;
    digits[1] = -1;
    digits[2] = -1;
    digits[3] = -1;
    break;
  case 2:
    //takes number up to 4 digits and splits it into 4 individual ints
    digits[0] = generatedNumber/1000;
    digits[1] = (generatedNumber/100)%10;
    digits[2] = (generatedNumber/10)%10;
    digits[3] = generatedNumber%10;
    break;
  }
  //read tilt switch
  int x = digitalRead(s3);
  //if in non default position
  if(x == 1){
    //check if there has been enough shakes quick enough, start generating numbers with each shake
    if(millis() - rtimestamp < 1000 & shake > 1000){
      //turn off the display  
      rolling = 1;
      //generate numbers based on number of dice and type
      generatedNumber = generateNumber(dice[selectedDice],selectedQuantity);
    };
    //take a new timestamp every roll
    rtimestamp = millis();
    //add to the shake meter (checked above, expect 10-50 or more per "shake" depending on your tilt switch)
    shake+=1;
  } else {
    //when in default position check if the last time there was a shake was atleast 3 seconds ago AND that there was atleast one shake before...
    if(millis() - rtimestamp > 3000 & rtimestamp != 0){
      //set mode to show result of generatedNumber
      rolling = 2;
      //reset shake meter so next roll takes some movement (so you can pick up the dice and read the result without clearing it)
      shake = 0;
    }
  }
}

//selecting the number of dice to roll logic
void selectQuantity()
{
  //display number of dice followed by "d" example would be 6d or 7d
  digits[0] = -1;
  digits[1] = -1;
  digits[2] = selectedQuantity;
  digits[3] = 10;
  
  //read first tactile switch
  int x = digitalRead(s1);
  //if the button state is the same as before, skip the rest of the code to prevent the function from going more than once per button press
  if (buttonPrevState3 == x)
  {
    return;
  }
  else
  {
    //record button state for above check
    buttonPrevState3 = x;
    //when button is pressed (1 is unpressed)
    if (x == 0)
    {   
      //if at limit, set back to 1  
      if (selectedQuantity == 9)
      {
        selectedQuantity = 1;
      }
      //otherwise progress quantity variable
      else
      {
        selectedQuantity++;
      }
    }
  }
}

//selecting the number of sides the dice has logic
void selectDice()
{

  //display "d" followed by space and number of dice sides based on value of selection
  digits[0] = 10;
  digits[1] = -1;
  switch (selectedDice)
  {
  default:
    break;
  case 0:
    digits[2] = 0;
    digits[3] = 2;
    break;
  case 1:
    digits[2] = 0;
    digits[3] = 4;
    break;
  case 2:
    digits[2] = 0;
    digits[3] = 6;
    break;
  case 3:
    digits[2] = 0;
    digits[3] = 8;
    break;
  case 4:
    digits[2] = 1;
    digits[3] = 0;
    break;
  case 5:
    digits[2] = 1;
    digits[3] = 2;
    break;
  case 6:
    digits[2] = 2;
    digits[3] = 0;
    break;
  }
  int x = digitalRead(s1);
  if (buttonPrevState1 == x)
  {
    return;
  }
  else
  {
    buttonPrevState1 = x;
    if (x == 0)
    {
      if (selectedDice == 6)
      {
        selectedDice = 0;
      }
      else
      {
        selectedDice++;
      }
    }
  }
}


void pickDigit(int x) //light up a 7-segment display
{
  //The 7-segment LED display is a common-cathode one. So also use digitalWrite to  set d1 as high and the LED will go out
  digitalWrite(d1, HIGH);
  digitalWrite(d2, HIGH);
  digitalWrite(d3, HIGH);
  digitalWrite(d4, HIGH);

  switch (x)
  {
  case 0:
    digitalWrite(d1, LOW); //Light d1 up
    break;
  case 1:
    digitalWrite(d2, LOW); //Light d2 up
    break;
  case 2:
    digitalWrite(d3, LOW); //Light d3 up
    break;
  default:
    digitalWrite(d4, LOW); //Light d4 up
    break;
  }
}
//The function is to control the 7-segment LED display to display numbers. Here x is the number to be displayed. It is an integer from 0 to 9
void pickNumber(int x)
{
  switch (x)
  {
  default:
    zero();
    break;
  case 1:
    one();
    break;
  case 2:
    two();
    break;
  case 3:
    three();
    break;
  case 4:
    four();
    break;
  case 5:
    five();
    break;
  case 6:
    six();
    break;
  case 7:
    seven();
    break;
  case 8:
    eight();
    break;
  case 9:
    nine();
    break;
  case 10:
    D();
    break;
  case 11:
    // Q();
    break;
  case 12:
    R();
    break;
  case 13:
    O();
    break;
  case 14:
    L();
    break;
  case -1:
    clearLEDs();
    break;
  }
}

void display()
{
  clearLEDs();           //clear the 7-segment display screen
  pickDigit(0);          //Light up 7-segment display d1
                         //  pickNumber((n/1000));// get the value of thousand
  pickNumber(digits[0]); // get the value of thousand
  

  clearLEDs();  //clear the 7-segment display screen
  pickDigit(1); //Light up 7-segment display d2
  pickNumber(digits[1]);


  clearLEDs();  //clear the 7-segment display screen
  pickDigit(2); //Light up 7-segment display d3
  pickNumber(digits[2]);


  clearLEDs();  //clear the 7-segment display screen
  pickDigit(3); //Light up 7-segment display d4
  pickNumber(digits[3]);

}

void menu()
{
  //menu selection based on variable, rolling is set to 0 when you switch to any other menu so "roll" is displayed when you get back to roll menu
  switch (currentMenu)
  {
  default:
    break;
  case 0:
    rolling = 0;
    selectQuantity();
    break;
  case 1:
    rolling = 0;
    selectDice();
    break;
  case 2:
    roll();
    break;
  }

  //read switch 2, this changes the menu globally on the device
  int x = digitalRead(s2);
  if (buttonPrevState2 == x)
  {
    return;
  }
  else
  {
    buttonPrevState2 = x;
    if (x == 0)
    {
      if (currentMenu == 2)
      {
        currentMenu = 0;
      }
      else
      {
        currentMenu++;
      }
    }
  }
}