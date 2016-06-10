#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//#include<wiringPi.h>

#define PIRPIN  17
#define REDPIN  18
#define BLUEPIN 24
#define BUZZER  22

int introductionMenu();
int printMainMenu();
int getAuthentication();
char* printAlarmState();
void executeOption(int opt);
void printSettings();
void printLog();
void run_alarm(int delay_time, int loop_nums, int state);

enum Alarm_state {
 ON,
 OFF
};

int alarmState = OFF;
FILE *fptr = NULL;

int introductionMenu(){

   //clear menu screen
   system("clear");
   
   printf("Welcome to Burglar Alarm System\n\n\n");

   printf("Developed by Balint Babik, Tanmay Khanna, Tarun Sabbinieni and Vinamra Agrawal\n\n\n\n");

   //delay(1000);

   printf("Pease enter your password \n");

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

   int option;

   printf("Enter desired option number\n");
   scanf("%i",&option);

   while(option < 1 || option > 5){
      printf("Invalid option entered retry\n");
      scanf("%i",&option);
   }

   return option;
}

char* printAlarmState(){
   if(alarmState == 0){
      return "ON";
   }
   return "OFF";
}

int getAuthentication(){

   fptr = fopen("password.txt","r");

   if(fptr == NULL){
    printf("Unable to password file\n");
    exit(1);
   }

   char* password = malloc(sizeof(char) * 10);
   
   fscanf(fptr, "%s", password);

   char input[10];

   for (int i = 5; i > 0; i--){
      scanf("%s",input);
      if(!strcmp(input,password)){
         free(password);
         fclose(fptr);
         return 1;
      }
      printf("Incorrect password %i attempts left\n",i-1);
   }

   fclose(fptr);
   free(password);

   return 0;
}

void executeOption(int opt){

   switch(opt){
    
      case 1:run_alarm(1000, 22, alarmState); 
             break;
      case 2:if(alarmState == OFF){
                alarmState = ON;
             } else {
                alarmState = OFF;
                }
             executeOption(printMainMenu());
             break;
      case 3:printSettings();
             break;
      case 4:printLog();
             break;
      case 5:printf("exiting\n");
             //digitalWrite(REDPIN, LOW);
             //digitalWrite(BLUEPIN, LOW);
             exit(0);
             break;
      default: printf("Invalid option given");
               
   }

}

void printSettings(){
   system("clear");

   printf("Please select from one of these options \n\n");
   printf("1> Change password \n");
   printf("2> Change log list address \n");
   printf("3> Change administration email address\n");
   printf("4> Go back\n");

   
   int option;

   printf("Enter desired option number\n");
   scanf("%i",&option);

   while(option < 1 || option > 4){
      printf("Invalid option entered retry\n");
      scanf("%i",&option);
   }
   
   // executing options
   switch(option) {

      case 1: printf("Enter current password: \n");
              if(getAuthentication()){
                printf("Correct! Enter new password: \n");
                char password[10];
                scanf("%s",password);
                fptr = fopen("password.txt", "w");
                fwrite(password, sizeof(password), 1, fptr);
                fclose(fptr);
                printf("password changes successfully\n");
                //delay(1000);
                printf("Returning to main menu\n");
                //delay(500);
                executeOption(printMainMenu());
              }
              break;

       case 2: //TODO
              break;

       case 3: // oprning data file
               fptr = fopen("email.txt","r");

               if(fptr == NULL){
                 printf("Unable to password file\n");
                 exit(1);
               }
               char* email = malloc(sizeof(char)*50);
               fscanf(fptr, "%s", email);
         
               printf("Current email: %s\n", email);
              
               fclose(fptr);

 
               printf("Change email address (y/n)\n");
               getchar(); 
               char option;
               scanf("%c", &option);
              
               if (option == 'y'){
                  fptr = fopen("email.txt","w");
                  printf("Enter new administration email address:\n");
                  char input[50];
                  scanf("%s",input);
                  fwrite(email, sizeof(input), 1, fptr);
                  fclose(fptr);
               
                printf("email changes successfully\n");
                //delay(1000);
                }
                printf("Returning to main menu\n");
                //delay(500);
                free(email);
                executeOption(printMainMenu());
               break; 

       case 4: executeOption(printMainMenu());
               break;  
       default: printf("Error invalid option");
   }   
   
}
void printLog(){
 //TODO
}


void run_alarm(int delay_time, int loop_nums,int state) {
  
 
  // setting all pins to 0
  //wiringPiSetupGpio();

  // setting up output pins
  //pinMode(REDPIN, OUTPUT);
  //pinMode(BLUEPIN, OUTPUT);
  //pinMode(BUZZER, OUTPUT);
  
  // setting up input pin
  //pinMode(PIRPIN, INPUT);
  
  printf("Running alarm, current mode is:");
  
  // displaying mode setting
  if (state == ON) {
    printf("ON\n");
    //digitalWrite(REDPIN, HIGH);
    //digitalWrite(BLUEPIN, LOW);
  } else {
    printf("OFF\n");
    //digitalWrite(REDPIN, LOW);
    //digitalWrite(BLUEPIN, HIGH);
  }
  
  int curr_state = 0;
  int prev_state = 0;

  // settling
  printf("waiting for PIR to settle...\n");
  while (1){//digitalRead(PIRPIN) == 1) {
  }
  printf("ready\n");

  if (state == ON) {
    // service loop
    for(int i = 0; i < loop_nums; i++) {
      curr_state = 0;//digitalRead(PIRPIN);
      printf("%i\n", curr_state);
      if ((curr_state == 1) && (prev_state == 0)) {
        //digitalWrite(BUZZER, HIGH); 
        printf("I see you! .. Baka!\n");
        prev_state = 1;
      } else if((curr_state == 0) && (prev_state == 1)) {
        //digitalWrite(BUZZER, LOW);
        printf("Ready\n");
        prev_state = 0;       
      }
      
      //delay(delay_time);
      //digitalWrite(BUZZER, LOW);
    }   
  }
  
  printf("Setting alarm off\n");
  //digitalWrite(REDPIN, LOW);
  //digitalWrite(BLUEPIN, LOW);
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

 //run_alarm(1000, 22, alarmState);
 return 0;
} else {

 printf("Aborting system\n");
 return 1;
}
}
