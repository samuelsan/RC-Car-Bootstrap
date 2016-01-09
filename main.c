/* 
 * File:   main.c
 * Author: Chris Hajduk
 *
 * Created on August 21, 2014, 11:32 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "GPS.h"
#include "main.h"
#include "HunterTruckAPI.h"
#include "debug.h"
#include "timer.h"
#include "OutputCompare.h"
#include "InterchipDMA.h"
#include "PWM.h"

_FOSCSEL(FNOSC_FRC); // Internal FRC oscillator
_FOSC(FCKSM_CSECMD & OSCIOFNC_OFF & POSCMD_NONE);
_FWDT(FWDTEN_OFF & WDTPOST_PS2048 & WDTPRE_PR128); //32,128
/*
 * 
 */

extern GPSData GPS;

void setDelay(int seconds);

int main(int argc, char** argv) {
    initTruck();
    while(TRUE){
        //This is how you move the car. Throttle goes from -100% to 100%. Steering goes from -100 to 100%.
        setThrottle(20);   //Note that the first -20%/20% is a safety buffer region. Anything less than 20% is equivalent to no throttle.
        setSteering(100);

//        This is an example of how you can print the GPS time to the debugging interface.
        char str[16];
        sprintf((char *)&str, "Time: %lu", getTime());
        debug((char *)&str);

        background();
    }
    void setDelay(int seconds){
        long pause;
        clock_t now,then;
    
        pause = seconds*(CLOCKS_PER_SEC);
        now = then = clock();
        while( (now-then) < pause )
            now = clock();
    }
    return (EXIT_SUCCESS);
}

