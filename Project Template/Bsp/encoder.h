#include "gpio.h"


#define __CHECK_ENCODER_LOCKED  do{\
                                   this->count = 0;\
                                   while(this->A.read()==GPL && this->count<60000){\
           	                       this->count++;this->locked = true;delay_us(20);\
                                   }               \
                               }while(0)


typedef enum{
    __NONE_EXTI,
}EncoderTrigger;

typedef enum{
    __ENCODER_NONE_OPERATION  = 0,
    __ENCODER_CLOCK_WISE      = 1,
    __ENCODER_ANTI_CLOCK_WISE = 2,
    __ENCODER_PRESS_DOWN      = 3,
}EncoderOperationType;

class ENCODER{
public:
	ENCODER(PTX_n pinA,PTX_n pinB,PTX_n pinC,bool dir = true);
	ENCODER(PTX_n pinA,PTX_n pinB,PTX_n pinC,EncoderTrigger triger,bool dir = true);
    EncoderOperationType read(void);
//private:
	bool     dir;
	bool     locked;
	uint16_t count;
	GPIO A;
	GPIO B;
	GPIO C;
};