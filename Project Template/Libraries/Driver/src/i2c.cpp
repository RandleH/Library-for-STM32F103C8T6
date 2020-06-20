#include "i2c.h"



I2C::I2C(I2C_TypeDef* base,uint32_t baudrate):PORT(base,N_A,"init_I2C"){
	I2C_DeInit(base);
	this->i2c_cfg.I2C_Mode        = I2C_Mode_I2C;
	this->i2c_cfg.I2C_DutyCycle   = I2C_DutyCycle_2;
	this->i2c_cfg.I2C_OwnAddress1 = 0x30;
	this->i2c_cfg.I2C_Ack         = I2C_Ack_Enable;
	this->i2c_cfg.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	this->i2c_cfg.I2C_ClockSpeed  = 400000;
    this->base = base;
	
	base->CR1 |= CR1_PE_Set;//I2C_Cmd(base, ENABLE);
	I2C_Init(base, &this->i2c_cfg);
}

void I2C::write(uint8_t slaveAddr,uint8_t addr,uint8_t data){
    while(I2C_GetFlagStatus(this->base, I2C_FLAG_BUSY));
	
	I2C_GenerateSTART(this->base, ENABLE);
	while(!I2C_CheckEvent(this->base, I2C_EVENT_MASTER_MODE_SELECT));

	I2C_Send7bitAddress(this->base, slaveAddr, I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(this->base, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	I2C_SendData(this->base, addr);
	while (!I2C_CheckEvent(this->base, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	I2C_SendData(this->base, data);
	while (!I2C_CheckEvent(this->base, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	I2C_GenerateSTOP(this->base, ENABLE);
}
