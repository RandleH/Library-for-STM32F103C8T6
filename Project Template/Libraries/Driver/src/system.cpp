#include "system.h"

RCC_GPIO_MAP SMT::RCC_GPIO = import_RCC_GPIO();
RCC_SPI_MAP  SMT::RCC_SPI  = import_RCC_SPI();
RCC_I2C_MAP  SMT::RCC_I2C  = import_RCC_I2C();
RCC_ADC_MAP  SMT::RCC_ADC  = import_RCC_ADC();

PIN_SPI_MAP  SMT::PIN_SPI  = import_PIN_SPI();
PIN_I2C_MAP  SMT::PIN_I2C  = import_PIN_I2C();
PIN_ADC_MAP  SMT::PIN_ADC  = import_PIN_ADC();



//Keep Globe...
SMT system_module_table;

