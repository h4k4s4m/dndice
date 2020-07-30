//the pins of 4-digit 7-segment display attach to pin2-13 respectively
int a = 2;
int b = 3;
int c = 4;
int d = 5;
int e = 6;
int f = 7;
int g = 8;
int p = 9;

int d4 = 10;
int d3 = 11;
int d2 = 12;
int d1 = 13;

int s1 = A0;
int s2 = A1;
int s3 = A2;

int digits[4] = {10, -1, 0, 2};
int buttonPrevState1 = 2;
int buttonPrevState2 = 2;
int buttonPrevState3 = 2;
int buttonPrevState4 = 2;
int dice[] = {2, 4, 6, 8, 10, 12, 20};
int selectedDice = 0;
int selectedQuantity = 1;
int currentMenu = 0;
bool rolling = false;
bool justSwitched = true;
unsigned long rtimestamp = millis();

int del = 0; //Set del as 5; the value is the degree of fine tuning for the clock

void setup()
{
  //set all the pins of the LED display as output
  Serial.begin(9600);
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
  pinMode(s1, INPUT);
  pinMode(s2, INPUT);
  pinMode(s3, INPUT);
}
/***************************************/
void loop()
{
  display();
  menu();
}
/**************************************/

void menu()
{
  switch (currentMenu)
  {
  default:
    break;
  case 0:
    rolling = false;
    selectQuantity();
    break;
  case 1:
    rolling = false;
    selectDice();
    break;
  case 2:
    roll();
    break;
  }

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

// void roll()
// {

//   // digits[0] = -1;
//   // digits[1] = -1;
//   // digits[2] = selectedQuantity;
//   // digits[3] = 12;
//   if (!rolling)
//   {
//     digits[0] = 12;
//     digits[1] = 13;
//     digits[2] = 14;
//     digits[3] = 14;
//   }
//   else {
    
//       digits[0] = -1;
//       digits[1] = -1;
//       digits[2] = -1;
//       digits[3] = -1;
//   }

//   int x = digitalRead(s3);
//   if (buttonPrevState4 == x)
//   {
//     return;
//   }
//   else
//   {
//     buttonPrevState4 = x;
//     Serial.println(millis());
//     Serial.println(rtimestamp);
//     Serial.println(millis()-rtimestamp);
//     if (millis() - rtimestamp < 2000)
//     {
//       rtimestamp = millis();
//       rolling = true;
//     }
//     else
//     {
//       rolling = true;
      
//     }
//   }
// }


void roll()
{
   int x = digitalRead(s3);
    if (justSwitched)
  {
    digits[0] = 12;
    digits[1] = 13;
    digits[2] = 14;
    digits[3] = 14;
    justSwitched=!justSwitched;
  }else{
      if(millis()-rtimestamp > 2000){
    rolling = false;
    digits[0] = -1;
    digits[1] = -1;
    digits[2] = -1;
    digits[3] = -1;
  }

  if(x != buttonPrevState4){
    buttonPrevState4 = x;
    Serial.println(millis() - rtimestamp);
    if(millis()-rtimestamp < 2000){
      rolling = true;
    }
    rtimestamp = millis();
  }



}
void selectQuantity()
{
  digits[0] = -1;
  digits[1] = -1;
  digits[2] = selectedQuantity;
  digits[3] = 10;

  int x = digitalRead(s1);
  if (4 == x)
  {
    return;
  }
  else
  {
    buttonPrevState3 = x;
    if (x == 0)
    {
      if (selectedQuantity == 9)
      {
        selectedQuantity = 1;
      }
      else
      {
        selectedQuantity++;
      }
    }
  }
}

void selectDice()
{
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

void display()
{
  clearLEDs();           //clear the 7-segment display screen
  pickDigit(0);          //Light up 7-segment display d1
                         //  pickNumber((n/1000));// get the value of thousand
  pickNumber(digits[0]); // get the value of thousand
  delay(del);            //delay 5ms

  clearLEDs();  //clear the 7-segment display screen
  pickDigit(1); //Light up 7-segment display d2
  pickNumber(digits[1]);
  delay(del); //delay 5ms

  clearLEDs();  //clear the 7-segment display screen
  pickDigit(2); //Light up 7-segment display d3
  pickNumber(digits[2]);
  delay(del); //delay 5ms

  clearLEDs();  //clear the 7-segment display screen
  pickDigit(3); //Light up 7-segment display d4
  pickNumber(digits[3]);
  delay(del); //delay 5ms
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

void clearLEDs() //clear the 7-segment display screen
{
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
  digitalWrite(p, LOW);
}

void zero() //the 7-segment led display 0
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, LOW);
}

void one() //the 7-segment led display 1
{
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}

void two() //the 7-segment led display 2
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, LOW);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, LOW);
  digitalWrite(g, HIGH);
}

void three() //the 7-segment led display 3
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, HIGH);
}

void four() //the 7-segment led display 4
{
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void five() //the 7-segment led display 5
{
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void six() //the 7-segment led display 6
{
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void seven() //the 7-segment led display 7
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}

void eight() //the 7-segment led display 8
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void nine() //the 7-segment led display 9
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void D() //the 7-segment led display d
{
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, LOW);
  digitalWrite(g, HIGH);
  digitalWrite(p, HIGH);
}

void R() //the 7-segment led display d
{
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, HIGH);
  digitalWrite(f, LOW);
  digitalWrite(g, HIGH);
  digitalWrite(p, LOW);
}

void O() //the 7-segment led display d
{
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, LOW);
  digitalWrite(g, HIGH);
  digitalWrite(p, LOW);
}

void L() //the 7-segment led display d
{
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
  digitalWrite(p, LOW);
}
