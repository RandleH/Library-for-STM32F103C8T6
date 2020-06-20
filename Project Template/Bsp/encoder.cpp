#include "encoder.h"
#include "delay.h"

/*
 * ---------------------------------------------------------------------- *
 *     C    |    A    |    B    |    dir    |    EncoderOperationType     *      B G A 
 * ---------------------------------------------------------------------- *      | | |
 *     1    |    0    |    0    |   false   | __ENCODER_CLOCK_WISE        *     /=====\
 *     1    |    0    |    1    |   false   | __ENCODER_ANTI_CLOCK_WISE   *     | [+] |
 *     1    |    0    |    0    |   true    | __ENCODER_ANTI_CLOCK_WISE   *     |_____|
 *     1    |    0    |    1    |   true    | __ENCODER_CLOCK_WISE        *       | |
 *     0    |    X    |    X    |     X     | __ENCODER_PRESS_DOWN        *       G C
 *     1    |    1    |    X    |     X     | __ENCODER_NONE_OPERATION    *
 * ---------------------------------------------------------------------- *
 */



ENCODER::ENCODER(PTX_n pinA,PTX_n pinB,PTX_n pinC,bool dir):\
A(pinA,GPI),B(pinB,GPI),C(pinC,GPI){
    this->locked = false;
}

EncoderOperationType ENCODER::read(void){
	EncoderOperationType result = __ENCODER_NONE_OPERATION;
	GPIO_LevelType b;

    if(this->A.read()==GPH)
    	this->locked = false;

    if(this->A.read()==GPL && this->locked == false){
    	delay_us(10);
        b = (GPIO_LevelType)this->B.read();
        //delay_ms(3);
        if(this->A.read()==GPL){
        	//result = (EncoderOperationType)(((bool)(b)^(bool)(this->dir))+1);
        	if(b==GPL)
        		result = __ENCODER_CLOCK_WISE;
        	else
        		result = __ENCODER_ANTI_CLOCK_WISE;

        	this->count = 0;
            while(this->A.read()==GPL && this->count<60000){
           	    this->count++;
           	    this->locked = true;
           	    delay_us(20);
            }   
        }
    }
    if(this->C.read()==GPL && this->locked == false){
    	delay_ms(20);
    	if(this->C.read()==GPL)
    		result = __ENCODER_PRESS_DOWN;
    }
    return result;
}
