#include "stm32f10x_gpio.h"
#include "port.h"


#ifndef _GPIO_H
#define _GPIO_H

typedef enum{
	__ZERO,
	__ONE,
    __RISING_EDGE,
    __FALLING_EDGE
}GPIO_LevelAction;

typedef enum {
	GPIFL = 0,
	GPIPD = 1,
	GPIPU = 2,
	GPO   = 3,
	GPI   = 0,
}GPIO_DirType;

typedef enum {
	GPL = 0,
    GPH = 1,
}GPIO_LevelType;


class GPIO:public PORT{
public:
	GPIO(PTX_n pin,GPIO_DirType dir,GPIO_LevelType defaultLevel = GPL);
	GPIO(){}

	bool read(PTX_n pin);
	bool read(void);
	void set(PTX_n pin,GPIO_LevelType);
	void set(GPIO_LevelType level);
	void setInterrupt(PTX_n,GPIO_LevelAction action,void(*p)(void));
private:
	GPIO_TypeDef* base;
	PTX_n         activePin;
};

class GPIOs{
public:
	GPIOs(PTX_n* pin,size_t size,GPIO_DirType dir,GPIO_LevelType defaultLevel = GPL){};
};

#endif