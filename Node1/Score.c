#include <stdint.h>
#include <time.h>
#include "CAN.h"
#include "Score.h"

uint16_t Score_calculate(uint8_t mode){
    if(mode){
        if(score){
            return -1;
        }
        clock_t t;
        clock_t t2; 
        t = clock(); 
        t2 = clock() - t; 
        uint16_t time_taken = ((uint16_t)t)/CLOCKS_PER_SEC;
        return time_taken;
    }else{
        return score;
    }
}