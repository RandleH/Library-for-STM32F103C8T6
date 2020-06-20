#include "port.h"

extern GPIO_TypeDef* GPIO_BASE[];

PORT::PORT(void* base,PTX_n pin,const char* operation){
	switch(__read__(operation)){

case i_want_to_("init_GPIO"):
    RCC_APB2PeriphClockCmd(SMT::RCC_GPIO[(GPIO_TypeDef*)base],ENABLE);
    this->config.GPIO_Pin   = PTn(pin);
    this->config.GPIO_Speed = GPIO_Speed_50MHz;
    this->config.GPIO_Mode  = GPIO_Mode_IN_FLOATING; 
    break;
case i_want_to_("SPI"):
    if((SPI_TypeDef*)base == SPI1)
        RCC_APB2PeriphClockCmd(	RCC_APB2Periph_SPI1,  ENABLE );
    else
    	RCC_APB1PeriphClockCmd(	SMT::RCC_SPI[(SPI_TypeDef*)base],  ENABLE );
    RCC_APB2PeriphClockCmd(SMT::RCC_GPIO[(GPIO_TypeDef*)SMT::PIN_SPI[(SPI_TypeDef*)base][SPI_PIN_BASE]], ENABLE);
    this->config.GPIO_Pin   = 0U
                            | SMT::PIN_SPI[(SPI_TypeDef*)base][SPI_SCK]
                            | SMT::PIN_SPI[(SPI_TypeDef*)base][SPI_MOSI]
                            | SMT::PIN_SPI[(SPI_TypeDef*)base][SPI_MISO];
    this->config.GPIO_Mode  = GPIO_Mode_AF_PP;
    this->config.GPIO_Speed = GPIO_Speed_50MHz; 
    GPIO_Init((GPIO_TypeDef*)SMT::PIN_SPI[(SPI_TypeDef*)base][SPI_PIN_BASE], &this->config);
    this->config.GPIO_Pin   = 0U|SMT::PIN_SPI[(SPI_TypeDef*)base][SPI_CS];
    this->config.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_Init((GPIO_TypeDef*)SMT::PIN_SPI[(SPI_TypeDef*)base][SPI_PIN_BASE], &this->config);
    break;
case i_want_to_("init_I2C"):
    RCC_APB2PeriphClockCmd(SMT::RCC_GPIO[ (GPIO_TypeDef*)SMT::PIN_I2C[(I2C_TypeDef*)base][I2C_PIN_BASE] ], ENABLE);
    RCC_APB1PeriphClockCmd(SMT::RCC_I2C[(I2C_TypeDef*)base],ENABLE);
    this->config.GPIO_Pin   = 0U
                            | SMT::PIN_I2C[(I2C_TypeDef*)base][I2C_SCK]
                            | SMT::PIN_I2C[(I2C_TypeDef*)base][I2C_SDA];
    this->config.GPIO_Mode  = GPIO_Mode_AF_OD;
    this->config.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init((GPIO_TypeDef*)SMT::PIN_I2C[(I2C_TypeDef*)base][I2C_PIN_BASE], &this->config);
    break;
case i_want_to_("init_ADC"):
    RCC_APB2PeriphClockCmd(SMT::RCC_GPIO[GPIO_BASE[PTX(pin)]],ENABLE);
    RCC_APB2PeriphClockCmd(SMT::RCC_ADC[(ADC_TypeDef*)base], ENABLE);
    this->config.GPIO_Pin   = PTn(pin);
    this->config.GPIO_Mode  = GPIO_Mode_AIN;
    GPIO_Init(GPIO_BASE[PTX(pin)],&this->config); 
    break;

	}
}