#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <wiringPi.h>
#include "terminate.h"

extern int terminated;

int send_email() {

  //obtaining email stored in file
  char *email = malloc(sizeof(char)*50);
  FILE *fptr;
  fscanf(fptr, "%s", email);
  fclose(fptr);


  //constructing appropriate command to send email
  char cmd[500];

  strcat(cmd, "curl --url \"smtps://smtp.gmail.com:465\" --ssl-reqd \
               --mail-from \"burglarpi@gmail.com\" \
               --mail-rcpt \"");

  strcat(cmd, email);

  strcat(cmd, "\" \
               --upload-file mail.txt \
               --user \"burglarpi@gmail.com:imperial15\" --insecure \
               &>/dev/null &");


  //calling appropriate command to send email
  system(cmd);

  puts("ATTENTION: The homeowner has been notified of this incident.");

  return 0;
}


int main() {

  delay(30000);

  //if it hasn't be deactivated, send an email
  if(terminated == 0){
    send_email;
    return 0;
  }

  return 0;
}
