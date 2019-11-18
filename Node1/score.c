#include <stdint.h>
#include "CAN.h"
#include "score.h"

uint16_t score_calculate(uint8_t mode){
    if(mode){
        if(score){
            return -1;
        }
        
        return score;
    }else{
        return score;
    }
}