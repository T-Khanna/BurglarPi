#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <wiringPi.h>

#define PIRPIN  17
#define REDPIN  18
#define BLUEPIN 24
#define BUZZERPIN  22
#define TEST_BUZZER_TIME 2000
#define MAX_PASSWORD_LEN 10
#define MAX_BUFFER_SIZE 100

enum Alarm_state {
  ON,
  OFF
};


int introductionMenu();
int printMainMenu();
int getAuthentication();
char* printAlarmState();
void executeOption(int opt);
void printSettings();
void printLog();
void encrypt_decrypt();
int send_email();
void run_alarm(enum Alarm_state state);
int get_option(int min, int max);

int alarmState = OFF;
FILE *fptr = NULL;

int introductionMenu(){

  //clear menu screen
  system("clear");
  
  printf("Welcome to Burglar Alarm System\n\n\n");

  printf("Developed by Tarun Sabbineni, Vinamra Agrawal, ");
  printf("Tanmay Khanna, Balint Babik\n\n\n\n"); 
        
  delay(1000);

  return (getAuthentication());

}

int printMainMenu(){

  //clear menu screen
  system("clear");

  printf("Welcome \n\n\n");

  printf("Current Selected alarm State - %s\n\n\n", printAlarmState() );

  printf("Please select from one of these options \n\n");
  printf("1> Activate alarm \n");
  printf("2> Change alarm state \n");
  printf("3> Go to settings\n");
  printf("4> Print Log\n");
  printf("5> Exit\n\n");

  return get_option(1, 5);

}

char* printAlarmState() {
  
  if (alarmState == 0) {
    return "ON";
  }
  return "OFF";

// return (alarmState == 0) ? "ON" : "OFF";
}

int getAuthentication(){

  fptr = fopen("password.txt","r");

  if (fptr == NULL) {
    printf("Unable to password file\n");
    exit(1);
  }

  //decrypting after opening from file to compare with input
  char password[MAX_PASSWORD_LEN];
  fgets(password, MAX_PASSWORD_LEN, fptr);
  encrypt_decrypt(password);

  char input[MAX_BUFFER_SIZE];
  printf("Please enter your password\n");

  for (int i = 5; i > 0; i--) {
    fgets(input, MAX_BUFFER_SIZE, stdin);
    // Needed to remove newline character before comparing with stored password
    input[strcspn(input, "\n")] = '\0';
    if (!strcmp(input, password)) {
       fclose(fptr);
       return 1;
    }
    if (i - 1 > 0 ) {
      printf("Incorrect password %i attempts left until delay\n", i - 1);
    } else {
      delay(300000);
      getAuthentication();
    }
  }

  fclose(fptr);

  return 0;

}

void executeOption(int opt){

  switch (opt) {
    case 1:  run_alarm(alarmState); 
             break;
    case 2:  if(alarmState == OFF){
               alarmState = ON;
             } else {
               alarmState = OFF;
             }
             executeOption(printMainMenu());
             break;
    case 3:  printSettings();
             break;
    case 4:  printLog();
             break;
    case 5:  printf("exiting\n");
             digitalWrite(REDPIN, LOW);
             digitalWrite(BLUEPIN, LOW);
             digitalWrite(BUZZERPIN, LOW);
             exit(0);
             break;
    default: printf("Invalid option given");
  }

}

int get_option(int min, int max) {
  int option;  
  char buffer[MAX_BUFFER_SIZE]; 
  while (fgets(buffer, MAX_BUFFER_SIZE, stdin)) {
    if (strlen(buffer) != 2) {
      if (*buffer != '\n') {
        printf("Please enter a valid option\n");
      }
      continue;
    }
    option = atoi(buffer);
    if (option < min || option > max) {
      printf("Please enter a number between %d and %d\n", min, max);
      continue;
    }
    break;
  }
  return option;   
}

void printSettings() {

  system("clear");

  printf("Please select from one of these options \n\n");
  printf("1> Change password \n");
  printf("2> Change log list address \n");
  printf("3> Change administration email address\n");
  printf("4> Go back\n\n");

  int option = get_option(1, 4);
  
  // executing options
  switch(option) {
    case 1:  if (getAuthentication()) {
               printf("Correct! Enter new password: \n");
               char password[MAX_PASSWORD_LEN];
               scanf("%s",password);

               //encrypting before storing in file
               encrypt_decrypt(password);
               fptr = fopen("password.txt", "w");
               fwrite(password, sizeof(password), 1, fptr);
               fclose(fptr);

               printf("Password changes successfully\n");
               delay(1000);
               printf("Returning to main menu\n");
               delay(500);
               executeOption(printMainMenu());
             }
             break;
    case 2:  //TODO: Implement log lists  
             break;

    case 3:  // oprning data file
             fptr = fopen("email.txt","r");

             if (fptr == NULL) {
               printf("Unable to open email file\n");
               exit(1);
             }
             char *email = malloc(sizeof(char)*50);
             fscanf(fptr, "%s", email);
             //encrypt_decrypt(email);
      
             printf("Current email: %s\n", email);
           
             fclose(fptr);

 
             printf("Change email address (y/n)\n");
             getchar(); 
             char option;
             scanf("%c", &option);
           
             if (option == 'y') {
               fptr = fopen("email.txt","w");
               printf("Enter new administration email address:\n");
               char input[50];
               scanf("%s",input);
               //encrypt_decrypt(input);
               fwrite(email, sizeof(input), 1, fptr);
               fclose(fptr);
               printf("email changes successfully\n");
               delay(1000);
             }

             printf("Returning to main menu\n");
             delay(500);
             free(email);
             executeOption(printMainMenu());
             break; 
    case 4:  executeOption(printMainMenu());
             break;  
    default: printf("Error invalid option");
  }   
  
}
void printLog(){
 //TODO
}

void encrypt_decrypt(char *password){
 
  char key[] = "AHFLSHENDHSOGKNASBBKJKDVVKASHDASHBDASLLUHSC"; 
	
	for(int i = 0; i < strlen(password); i++) {

		password[i] = password[i] ^ key[i % (sizeof(key)/sizeof(char))];

	}

}

int send_email() {

  //obtaining email stored in file
  char* email = malloc(sizeof(char)*50);
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

  //working code to help debug
  /*system("curl --url \"smtps://smtp.gmail.com:465\" --ssl-reqd \
                 --mail-from \"burglarpi@gmail.com\" \
                 --mail-rcpt \"tsabbineni@gmail.com\" \
                 --upload-file mail.txt \
                 --user \"burglarpi@gmail.com:imperial15\" --insecure \
                 &>/dev/null &");
  */
  free(email);
  puts("ATTENTION: The homeowner has been notified of this incident.");

  return 0;

}


void run_alarm(enum Alarm_state state) {
 
  // setting all pins to 0
  wiringPiSetupGpio();

  // setting up output pins
  pinMode(REDPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
  pinMode(BUZZERPIN, OUTPUT);
  
  // setting up input pin
  pinMode(PIRPIN, INPUT);
 
  system("clear");
 
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

  if (state == ON) {   
    // settling
    printf("waiting for PIR to settle...\n");
    while (digitalRead(PIRPIN) == 1) {}
    printf("ready\n");

    while(1) {
      // PRE: Someone walks in.
      send_email();
      if (digitalRead(PIRPIN) == 1) {
        digitalWrite(BUZZERPIN, HIGH);

        printf("To deactivate the alarm:\n");
        if (getAuthentication()) {
          digitalWrite(BUZZERPIN, LOW);
        }  
        break; 
      }
    }
  } else {
    printf("To deactivate the alarm:\n");
    if (!getAuthentication()) {
      digitalWrite(BUZZERPIN, HIGH);
    }
  }
     
  delay(TEST_BUZZER_TIME);
  digitalWrite(BUZZERPIN, LOW);
  
  printf("Setting alarm off\n");
  digitalWrite(REDPIN, LOW);
  digitalWrite(BLUEPIN, LOW);
}

int main(void){
  // options
  // activate
  // change state
  // settigns (change password, log list ,email)
  // print loglist
  // Exit
 
  // print introduction and check for inital authentication
  if (introductionMenu()){
    // choose the menu option
    int menuOpt = printMainMenu();
    executeOption(menuOpt);
    return EXIT_SUCCESS;
  } else {
    printf("Wrong passcode.\nAborting system\n");
    return EXIT_FAILURE;
  }
}
