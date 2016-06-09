#include<stdio.h>
#include<wiringPi.h>
#include<assert.h>

// Define Pins
#define PIRPIN 17
#define REDPIN 18
#define BLUEPIN 24
#define BUZZERPIN 22
#define MAX_ATTEMPTS 5

enum Alarm_state {
  ON,
  OFF
};


int check_passcode(void) {
 delay(1000); 
 return 1; 
 // for (int i = 0; i < MAX_ATTEMPTS; i++) {
 //   printf("Type in your password below. This is attempt number %i out of %i.\n", i, MAX_ATTEMPTS);
 //   scanf()
 // }  
}

void run_alarm(enum Alarm_state state) {

  // setting all pins to 0
  wiringPiSetupGpio();

  // setting up output pins
  pinMode(REDPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
  pinMode(BUZZERPIN, OUTPUT);

  //setting up input pin
  pinMode(PIRPIN, INPUT);

  printf("Running alarm, current mode is:");

  // displaying mode setting
  if (state == ON) {
    printf("ON\n");
    digitalWrite(REDPIN, HIGH);
    digitalWrite(BLUEPIN, LOW);
  } else {
    printf("OFF\n");
    digitalWrite(REDPIN, LOW);
    digitalWrite(BLUEPIN, HIGH);
  }
  digitalWrite(BUZZERPIN, LOW);


  // settling 
  printf("waiting for PIR to settle...\n");
  while (digitalRead(PIRPIN) == 1) {
  }
  printf("ready\n");


  if(state == ON){   
    while(1) {
      // PRE: Someone walks in.
      if(digitalRead(PIRPIN) == 1) {
        digitalWrite(BUZZERPIN, HIGH);
        if (check_passcode()) {
        digitalWrite(BUZZERPIN, LOW);
        }  
        break;
      }
    }
  } else {
    check_passcode();
  }
  
  digitalWrite(REDPIN, LOW);
  digitalWrite(BLUEPIN, LOW);
  
}


int main(){
  run_alarm(OFF);
}
