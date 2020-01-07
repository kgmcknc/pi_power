#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <wiringPi.h>

#define SLEEP_MICROSECONDS 50000

#define POWER_SIGNAL_GPIO 0
#define POWER_SWITCH_NOT_PRESSED 1
#define POWER_SWITCH_PRESSED 0

#define RESET_SIGNAL_GPIO 3
#define RESET_SWITCH_NOT_PRESSED 0
#define RESET_SWITCH_PRESSED 1

#define POWER_LED_GPIO 2

void turn_on_led(void);
void turn_off_led(void);

int main(int argc, char **argv) {
   int power_switch = POWER_SWITCH_NOT_PRESSED;
   int reset_switch = RESET_SWITCH_NOT_PRESSED;
   
   printf("Starting Pi Power Monitor\n");
   
   wiringPiSetup();
   
   turn_on_led();
   
   // setup power switch gpio
   pinMode(POWER_SIGNAL_GPIO, INPUT);
   pullUpDnControl(POWER_SIGNAL_GPIO, PUD_UP);

   // setup reset switch gpio
   pinMode(RESET_SIGNAL_GPIO, INPUT);
   pullUpDnControl(RESET_SIGNAL_GPIO, PUD_DOWN);
   
   while(1){
      if(power_switch == POWER_SWITCH_PRESSED){
         turn_off_led();
         printf("Received Power Signal! Shutting Down\n");
         system("shutdown now");
      }
      if(reset_switch == RESET_SWITCH_PRESSED){
         turn_off_led();
         printf("Received Reset Signal! Shutting Down\n");
         system("reboot now");
      }
      power_switch = digitalRead(POWER_SIGNAL_GPIO);
      reset_switch = digitalRead(RESET_SIGNAL_GPIO);
      usleep(SLEEP_MICROSECONDS);
   };   
   
   return 0;
}

void turn_on_led(void){
   pinMode(POWER_LED_GPIO, OUTPUT);
}

void turn_off_led(void){
   pinMode(POWER_LED_GPIO, INPUT);
}

