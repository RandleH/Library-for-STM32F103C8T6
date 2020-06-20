#include "stm32f10x_spi.h"
#include "port.h"
#ifndef _SPI_H
#define _SPI_H



class SPI:public PORT{
public:
	SPI(SPI_TypeDef* base,uint32_t baudrate,bool polarity,uint8_t phase);
	SPI(){}
	uint16_t write(uint8_t data);
private:
	SPI_InitTypeDef spi_cfg;
	SPI_TypeDef* base;
	GPIO_TypeDef* pin_base;
};

#endif

