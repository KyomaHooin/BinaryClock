
///////////////////////////////////////
// RTC Binary clock by Richard Bruna //
///////////////////////////////////////

#include <Time.h>

// LED array digital pins:
const int Col[4] = {2,3,4,5};
const int Row[4] = {6,7,9,8};

//Binary digits [0-9]:
int bin_digit[10][4] = {
  {0,0,0,0},
  {0,0,0,1},
  {0,0,1,0},
  {0,0,1,1},
  {0,1,0,0},
  {0,1,0,1},
  {0,1,1,0},
  {0,1,1,1},
  {1,0,0,0},
  {1,0,0,1}
};

//SETUP:
void setup() {
  //Init LED array:
  for (int Pin = 0; Pin < 4; Pin++) {
    pinMode(Row[Pin], OUTPUT);
    digitalWrite(Row[Pin], LOW);
    pinMode(Col[Pin], OUTPUT);
    digitalWrite(Col[Pin], HIGH);
  }
  //Set birth time:
  setTime(18,3,5,1,4,1982);
}

//MAIN:
void loop() {
  //Get RT:
  if (timeStatus() == timeSet) {
    //Store RT in array:
    int *bin_time[4] = {
      bin_digit[hour() / 10],
      bin_digit[hour() % 10],
      bin_digit[minute() / 10],
      bin_digit[minute() % 10]
    };
    //Scan the array and display the LED clock:
    for (int ColPin = 0; ColPin < 4; ColPin++) {
      //Power up the Col:
      digitalWrite(Col[ColPin], LOW);
      //Blink all the LED's in a Col:
      for (int RowPin = 0; RowPin < 4; RowPin++) {
        //Turn LED ON:
        if ( bin_time[ColPin][RowPin] == 1 ) {
          digitalWrite(Row[RowPin], HIGH);
          //POV delay:
          delay(1);
        }
        //Turn the LED OFF:
        digitalWrite(Row[RowPin], LOW);
      }
      //Power down the Col:
      digitalWrite(Col[ColPin], HIGH);
    }
  }
}

