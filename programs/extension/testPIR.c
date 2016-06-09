#include<stdio.h>
#include<wiringPi.h>

#define PIRPIN 17

int main() {
  wiringPiSetupGpio();
 
  pinMode(PIRPIN, INPUT);

  while (1) {
    printf("%i\n", digitalRead(PIRPIN));
    delay(100);
  }

return 0; 
}
