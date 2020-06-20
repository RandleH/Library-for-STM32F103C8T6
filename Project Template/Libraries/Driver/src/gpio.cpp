#include "gpio.h"
#include "interrupt.h"

GPIO_TypeDef* GPIO_BASE[] = {GPIOA,GPIOB,GPIOC,GPIOD,GPIOE};


GPIO::GPIO(PTX_n pin,GPIO_DirType dir,GPIO_LevelType defaultLevel):PORT(GPIO_BASE[PTX(pin)],pin,"init_GPIO"){
	this->base = GPIO_BASE[PTX(pin)];
	switch(dir){
		case GPO:   this->config.GPIO_Mode = GPIO_Mode_Out_PP;break;
		case GPIPD: this->config.GPIO_Mode = GPIO_Mode_IPD;break;
		case GPIPU: this->config.GPIO_Mode = GPIO_Mode_IPU;break;
		case GPIFL:   
		default:    this->config.GPIO_Mode = GPIO_Mode_IN_FLOATING;break;	
	}
	GPIO_Init(GPIO_BASE[PTX(pin)],&this->config);
	this->activePin = pin;
}

void GPIO::set(PTX_n pin,GPIO_LevelType level){
    level==0 ? this->base->BRR = PTn(pin):this->base->BSRR = PTn(pin);
    this->activePin = pin;
}

void GPIO::set(GPIO_LevelType level){
	level==0 ? this->base->BRR = PTn(this->activePin):this->base->BSRR = PTn(this->activePin);
}

bool GPIO::read(PTX_n pin){
    return (bool)(this->base->IDR & pin);
}

bool GPIO::read(void){
	return (bool)(this->base->IDR & PTn(this->activePin));
}

void GPIO::setInterrupt(PTX_n,GPIO_LevelAction action,void(*p)(void)){
    p = ISR::IRQ_FUNC[EXTI1_IRQn];
}

