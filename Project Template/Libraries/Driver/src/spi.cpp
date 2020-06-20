#include "spi.h"


SPI::SPI(SPI_TypeDef* base,uint32_t baudrate,bool polarity,uint8_t phase):PORT(base,N_A,"SPI"){
	this->spi_cfg.SPI_Direction  = SPI_Direction_2Lines_FullDuplex;
	this->spi_cfg.SPI_Mode       = SPI_Mode_Master;
	this->spi_cfg.SPI_DataSize   = SPI_DataSize_8b;
	this->spi_cfg.SPI_CPOL       = SPI_CPOL_High;
	this->spi_cfg.SPI_CPHA       = SPI_CPHA_2Edge;
	this->spi_cfg.SPI_NSS        = SPI_NSS_Soft;
	this->spi_cfg.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
	this->spi_cfg.SPI_FirstBit   = SPI_FirstBit_MSB;
	this->spi_cfg.SPI_CRCPolynomial=7;
	SPI_Cmd(base, ENABLE);
	SPI_Init(base,&this->spi_cfg);
	this->base = base;
	switch((uint32_t)this->base){
		case SPI1_BASE:this->pin_base = GPIOA;break;
		case SPI2_BASE:this->pin_base = GPIOB;break;
	}
}

uint16_t SPI::write(uint8_t data){
    while(!SPI_I2S_GetFlagStatus(this->base, SPI_I2S_FLAG_TXE));
	SPI_I2S_SendData(this->base,data);
	while(!SPI_I2S_GetFlagStatus(this->base, SPI_I2S_FLAG_RXNE));
	return SPI_I2S_ReceiveData(this->base);
}