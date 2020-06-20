#include "adc.h"
#include "stm32f10x_dma.h"

uint8_t ADC::NbrOfChannel = 0;

static const PTX_n ADCx_n[] = {A0     ,A1      ,A2      ,A3      ,A4      ,A5      ,A6      ,A7     ,\
                               B0     ,B1      ,C0      ,C1      ,C2      ,C3      ,C4      ,C5     };

ADC::ADC(ADC_TypeDef* base,PTX_n pin,ADC_SampleTime st):ADC(base,SMT::PIN_ADC[pin],st){
}

ADC::ADC(ADC_TypeDef* base,uint8_t channel,ADC_SampleTime st):PORT(base,ADCx_n[channel%(sizeof(ADCx_n)/sizeof(*ADCx_n)-1)],"init_ADC"){
    ADC_DeInit(base);
	this->adc_cfg.ADC_Mode = ADC_Mode_Independent;//

	this->adc_cfg.ADC_ScanConvMode = ENABLE;
    this->adc_cfg.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    this->adc_cfg.ADC_DataAlign = ADC_DataAlign_Right;
    this->adc_cfg.ADC_NbrOfChannel = (++ADC::NbrOfChannel);
    ADC_Init(base,&this->adc_cfg);
    ADC_Cmd(base,ENABLE);

    ADC_RegularChannelConfig(base,channel,ADC::NbrOfChannel,(uint8_t)st);
    ADC_GetResetCalibrationStatus(base);
    while(ADC_GetResetCalibrationStatus(base));
    ADC_StartCalibration(base);
    while(ADC_GetCalibrationStatus(base));
    ADC_SoftwareStartConvCmd(base,ENABLE);

    this->base    = base;
    this->channel = channel;
    this->value   = 0;
    this->DMA     = false;
    this->st      = st;
}

ADC::ADC(ADC_TypeDef* base,PTX_n pin,volatile uint16_t* storage,DMA_Channel_TypeDef* dma_ch,ADC_SampleTime st){

}

ADC::ADC(ADC_TypeDef* base,uint8_t channel,volatile uint16_t* storage,DMA_Channel_TypeDef* dma_ch,ADC_SampleTime st):\
PORT(base,ADCx_n[channel%(sizeof(ADCx_n)/sizeof(*ADCx_n)-1)],"init_ADC"){
    DMA_InitTypeDef dma_cfg;
    DMA_DeInit(dma_ch);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
    dma_cfg.DMA_PeripheralBaseAddr = (uint32_t)(&base->DR);
    storage==NULL?dma_cfg.DMA_MemoryBaseAddr = (uint32_t)&this->value:\
                  dma_cfg.DMA_MemoryBaseAddr = (uint32_t)storage;
    dma_cfg.DMA_DIR                = DMA_DIR_PeripheralSRC;
    dma_cfg.DMA_BufferSize         = 1;
    dma_cfg.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
    dma_cfg.DMA_MemoryInc          = DMA_MemoryInc_Enable;
    dma_cfg.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    dma_cfg.DMA_MemoryDataSize     = DMA_MemoryDataSize_HalfWord;
    dma_cfg.DMA_Mode               = DMA_Mode_Circular;
    dma_cfg.DMA_Priority           = DMA_Priority_High;
    dma_cfg.DMA_M2M                = DMA_M2M_Disable;
    DMA_Init(dma_ch,&dma_cfg);
    DMA_Cmd(dma_ch,ENABLE);

    //RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    this->adc_cfg.ADC_Mode = ADC_Mode_Independent; 
    this->adc_cfg.ADC_ScanConvMode = ENABLE;
    this->adc_cfg.ADC_ContinuousConvMode = ENABLE; 
    this->adc_cfg.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    this->adc_cfg.ADC_DataAlign = ADC_DataAlign_Right;
    this->adc_cfg.ADC_NbrOfChannel = (++ADC::NbrOfChannel); 
    ADC_Init(base,&this->adc_cfg);
    ADC_RegularChannelConfig(base,channel,ADC::NbrOfChannel,(uint8_t)st);
    ADC_DMACmd(base,ENABLE);
    ADC_Cmd(base,ENABLE);

    ADC_RegularChannelConfig(base,channel,ADC::NbrOfChannel,(uint8_t)st);
    while(ADC_GetResetCalibrationStatus(base));
    ADC_StartCalibration(base);
    while(ADC_GetCalibrationStatus(base));
    ADC_SoftwareStartConvCmd(base,ENABLE);
    
    this->base    = base;
    this->channel = channel;
    this->DMA     = true;
    this->st      = st;

}

uint16_t ADC::read(void){
    ADC_RegularChannelConfig(this->base,this->channel,1,this->st);
    ADC_SoftwareStartConvCmd(this->base,ENABLE);
    while(!ADC_GetFlagStatus(this->base,ADC_FLAG_EOC));
    return ADC_GetConversionValue(this->base);
}






