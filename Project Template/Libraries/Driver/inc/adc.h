#include "common.h"
#include "port.h"
#include "stm32f10x_adc.h"

typedef enum{
   ADC_1Cycles5   ,
   ADC_7Cycles5   ,
   ADC_13Cycles5  ,
   ADC_28Cycles5  ,
   ADC_41Cycles5  ,
   ADC_55Cycles5  ,
   ADC_71Cycles5  ,
   ADC_239Cycles5 ,
}ADC_SampleTime;


class ADC :public PORT{
public:
	ADC(ADC_TypeDef* ADCx,PTX_n pin       ,ADC_SampleTime st = ADC_28Cycles5);
	ADC(ADC_TypeDef* base,uint8_t channel ,ADC_SampleTime st = ADC_28Cycles5);
	ADC(ADC_TypeDef* ADCx,PTX_n pin       ,volatile uint16_t* storage,DMA_Channel_TypeDef* dma_ch = DMA1_Channel1,\
		ADC_SampleTime st = ADC_28Cycles5);
	ADC(ADC_TypeDef* base,uint8_t channel ,volatile uint16_t* storage,DMA_Channel_TypeDef* dma_ch = DMA1_Channel1,\
		ADC_SampleTime st = ADC_28Cycles5);
	uint16_t read(void);
    volatile uint16_t value;
private:
	static uint8_t   NbrOfChannel;
    ADC_TypeDef*     base;
    uint8_t          channel;
    ADC_InitTypeDef  adc_cfg;
    ADC_SampleTime   st;
    bool             DMA;
};
