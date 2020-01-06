#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <wiringPi.h>

#define PI_POWER_GPIO
#define SLEEP_MICROSECONDS 50000
#define POWER_SIGNAL_GPIO 3

int main(int argc, char **argv) {
   int power_signal_captured = 0;
   
   printf("Starting Pi Power Monitor\n");
   
   wiringPiSetup();
   
   pinMode(POWER_SIGNAL_GPIO, INPUT);
   pullUpDnControl(POWER_SIGNAL_GPIO, PUD_OFF);
   
   while(1){
      if(power_signal_captured){
         printf("Received Signal!\n");
      } else {
         power_signal_captured = digitalRead(POWER_SIGNAL_GPIO);
      }
      usleep(SLEEP_MICROSECONDS);
   };   
   
   return 0;
}