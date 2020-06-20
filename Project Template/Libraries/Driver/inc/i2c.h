#include "stm32f10x_i2c.h"
#include "port.h"
#include "common.h"
#ifndef _I2C_H
#define _I2C_H 

class I2C:public PORT{
public:
	I2C(I2C_TypeDef* base,uint32_t baudrate);
	I2C(PTX_n SCK,PTX_n SDA);
	I2C(){}
protected:
	void write(uint8_t slaveAddr,uint8_t addr,uint8_t data);
private:
	I2C_InitTypeDef  i2c_cfg;
	I2C_TypeDef*     base;
};

/* I2C SPE mask */
#define CR1_PE_Set              ((uint16_t)0x0001)
#define CR1_PE_Reset            ((uint16_t)0xFFFE)

#endif


