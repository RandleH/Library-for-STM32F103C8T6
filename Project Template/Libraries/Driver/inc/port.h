#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "common.h"
#include "system.h"


#ifndef _PORT_H
#define _PORT_H
#define PORT_InitTypeDef GPIO_InitTypeDef


using namespace std;


class PORT{
protected:
	PORT_InitTypeDef  config;
public:
    PORT(void* base,PTX_n pin,const char* operation);
    PORT(){}
	~PORT();
private:
	
};

#endif

//GPIO LED(C13,GPO,High);

//SPI  OLED(SPI1,)

