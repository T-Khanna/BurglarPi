#include<stdio.h>
#include<wiringPi.h>

#define PIRPIN  17
#define REDPIN  18
#define BLUEPIN 24
#define BUZZER  22


enum Alarm_state {
 ON,
 OFF
};

void run_alarm(int delay_time, int loop_nums, enum Alarm_state state) {
  
 
  // setting all pins to 0
  wiringPiSetupGpio();

  // setting up output pins
  pinMode(REDPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  
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
  
  int curr_state = 0;
  int prev_state = 0;

  // settling
  printf("waiting for PIR to settle...\n");
  while (digitalRead(PIRPIN) == 1) {
  }
  printf("ready\n");

  if (state == ON) {
    // service loop
    for(int i = 0; i < loop_nums; i++) {
      curr_state = digitalRead(PIRPIN);
      printf("%i\n", curr_state);
      if ((curr_state == 1) && (prev_state == 0)) {
        digitalWrite(BUZZER, HIGH); 
        printf("I see you! .. Baka!\n");
        prev_state = 1;
      } else if((curr_state == 0) && (prev_state == 1)) {
        digitalWrite(BUZZER, LOW);
        printf("Ready\n");
        prev_state = 0;       
      }
      
      delay(delay_time);
      digitalWrite(BUZZER, LOW);
    }   
  }
  
  printf("Setting alarm off\n");
  digitalWrite(REDPIN, LOW);
  digitalWrite(BLUEPIN, LOW);
}

int main(void){
 run_alarm(1000, 22, ON);
 return 0;
}
