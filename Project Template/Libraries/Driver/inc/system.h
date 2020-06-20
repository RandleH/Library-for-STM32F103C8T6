#include <map>
#include "common.h"
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#ifndef _SYSTEM_H
#define _SYSTEM_H
using namespace std;

//All pin definitions are listed at default(no-remap) condition.
typedef uint32_t PIN_Array;
typedef enum               {      SPI_SCK ,SPI_MOSI ,SPI_MISO ,SPI_CS  ,SPI_PIN_BASE   }SPI_n;
static const PIN_Array SPI1_n[] = {(1<<5)  ,(1<<7)   ,(1<<6)   ,(1<<4)  ,(uint32_t)GPIOA};
static const PIN_Array SPI2_n[] = {(1<<13) ,(1<<15)  ,(1<<14)  ,(1<<12) ,(uint32_t)GPIOB};

typedef enum                      {I2C_SCK ,I2C_SDA  ,I2C_SBMA ,I2C_PIN_BASE   }I2C_n;
static const PIN_Array I2C1_n[] = {(1<<6)  ,(1<<7)   ,(1<<5)   ,(uint32_t)GPIOB};
static const PIN_Array I2C2_n[] = {(1<<10) ,(1<<11)  ,(1<<12)  ,(uint32_t)GPIOB};

typedef enum                      {ADC_CH0,ADC_CH1 ,ADC_CH2 ,ADC_CH3 ,ADC_CH4 ,ADC_CH5 ,ADC_CH6 ,ADC_CH7,\
                                   ADC_CH8,ADC_CH9 ,ADC_CH10,ADC_CH11,ADC_CH12,ADC_CH13,ADC_CH14,ADC_CH15}ADC_n;


typedef map < GPIO_TypeDef* , uint32_t   > RCC_GPIO_MAP;
typedef map < SPI_TypeDef*  , uint32_t   > RCC_SPI_MAP;
typedef map < I2C_TypeDef*  , uint32_t   > RCC_I2C_MAP;
typedef map < ADC_TypeDef*  , uint32_t   > RCC_ADC_MAP;

typedef map < SPI_TypeDef*  , const PIN_Array* > PIN_SPI_MAP;
typedef map < I2C_TypeDef*  , const PIN_Array* > PIN_I2C_MAP;
typedef map < PTX_n  , ADC_n >        PIN_ADC_MAP;


class SMT{    //System Module Table
public:
	SMT(){}
	static  RCC_GPIO_MAP  RCC_GPIO;
	static  RCC_GPIO_MAP  import_RCC_GPIO(void){
        RCC_GPIO_MAP tmp_map;
        tmp_map.insert(make_pair(GPIOA,RCC_APB2Periph_GPIOA));
        tmp_map.insert(make_pair(GPIOB,RCC_APB2Periph_GPIOB));
        tmp_map.insert(make_pair(GPIOC,RCC_APB2Periph_GPIOC));
        tmp_map.insert(make_pair(GPIOD,RCC_APB2Periph_GPIOD));
        tmp_map.insert(make_pair(GPIOE,RCC_APB2Periph_GPIOE));
        return tmp_map;
    }
    static  RCC_SPI_MAP  RCC_SPI;
    static  RCC_SPI_MAP  import_RCC_SPI(void){
    	RCC_SPI_MAP tmp_map;
    	tmp_map.insert(make_pair(SPI1,RCC_APB2Periph_SPI1));
    	tmp_map.insert(make_pair(SPI2,RCC_APB1Periph_SPI2));
    	tmp_map.insert(make_pair(SPI3,RCC_APB1Periph_SPI3));
    	return tmp_map;
    }
    static  RCC_I2C_MAP  RCC_I2C;
    static  RCC_I2C_MAP  import_RCC_I2C(void){
        RCC_I2C_MAP tmp_map;
        tmp_map.insert(make_pair(I2C1,RCC_APB1Periph_I2C1));
        tmp_map.insert(make_pair(I2C2,RCC_APB1Periph_I2C2));
        return tmp_map;
    }
    static  RCC_ADC_MAP  RCC_ADC;
    static  RCC_ADC_MAP  import_RCC_ADC(void){
        RCC_ADC_MAP tmp_map;
        tmp_map.insert(make_pair(ADC1,RCC_APB2Periph_ADC1));
        tmp_map.insert(make_pair(ADC2,RCC_APB2Periph_ADC2));
        tmp_map.insert(make_pair(ADC3,RCC_APB2Periph_ADC3));
        return tmp_map;
    }

    

    static PIN_SPI_MAP  PIN_SPI;
    static PIN_SPI_MAP  import_PIN_SPI(void){
    	PIN_SPI_MAP tmp_map;
    	tmp_map.insert(make_pair(SPI1,SPI1_n));
    	tmp_map.insert(make_pair(SPI2,SPI2_n));
    	return tmp_map;
    }
    static PIN_I2C_MAP  PIN_I2C;
    static PIN_I2C_MAP  import_PIN_I2C(void){
        PIN_I2C_MAP tmp_map;
        tmp_map.insert(make_pair(I2C1,I2C1_n));
        tmp_map.insert(make_pair(I2C2,I2C2_n));
        return tmp_map;
    }
    static PIN_ADC_MAP  PIN_ADC;
    static PIN_ADC_MAP  import_PIN_ADC(void){
        PIN_ADC_MAP tmp_map;
        tmp_map.insert(make_pair(A0,ADC_CH0));
        tmp_map.insert(make_pair(A1,ADC_CH1));
        tmp_map.insert(make_pair(A2,ADC_CH2));
        tmp_map.insert(make_pair(A3,ADC_CH3));
        tmp_map.insert(make_pair(A4,ADC_CH4));
        tmp_map.insert(make_pair(A5,ADC_CH5));
        tmp_map.insert(make_pair(A6,ADC_CH6));
        tmp_map.insert(make_pair(A7,ADC_CH7));
        tmp_map.insert(make_pair(B0,ADC_CH8));
        tmp_map.insert(make_pair(B1,ADC_CH9));
        tmp_map.insert(make_pair(C0,ADC_CH10));
        tmp_map.insert(make_pair(C1,ADC_CH11));
        tmp_map.insert(make_pair(C2,ADC_CH12));
        tmp_map.insert(make_pair(C3,ADC_CH13));
        tmp_map.insert(make_pair(C4,ADC_CH14));
        tmp_map.insert(make_pair(C5,ADC_CH15));
        return tmp_map;
    }
};


#endif


