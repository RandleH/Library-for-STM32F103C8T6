/**********************************  STM32F10x  *********************************
  * @�ļ���     �� my_stm32.c
  * @����       �� Randle_H
  * @��汾     �� V3.5.0
  * @�ļ��汾   �� V1.0.0
  * @����       �� 2019��04��06��
  * @ժҪ       �� �ҵĿ⺯�� - �������
  ******************************************************************************/
#include "my_stm32.h"

void gpio_init(PTX_n ptx_n,uint8 ddr)//                                            ��ͨ���ų�ʼ��������Ĭ��50MHz��
{//                                                                                 Sample:
  GPIO_InitTypeDef GPIO_InitStructure; //                                           gpio_init(P13,GPO_PP);
  GPIO_InitStructure.GPIO_Pin =  (uint16_t)1<<(ptx_n%16);
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = (GPIOMode_TypeDef)ddr;
  
  switch(ptx_n/16)
  {
case 0:
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  break;
case 1:
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  break;
case 2:
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  break;
case 3:
  GPIO_Init(GPIOD, &GPIO_InitStructure);
  break;
case 4:
  GPIO_Init(GPIOE, &GPIO_InitStructure);
  break;
  }
}

void gpio_set(PTX_n ptx_n,uint8 dat)//                                             �������ŵ�ƽ���ú���
{//                                                                                 Sample:
  switch(ptx_n/16)//                                                                gpio_set(C13,1);
  {
case 0:
  if(dat)
    GPIOA->BSRR = (uint16_t)1<<(ptx_n%16);
  else
    GPIOA->BRR = (uint16_t)1<<(ptx_n%16);
  break;
case 1:
  if(dat)
    GPIOB->BSRR = (uint16_t)1<<(ptx_n%16);
  else
    GPIOB->BRR = (uint16_t)1<<(ptx_n%16);
  break;
case 2:
  if(dat)
    GPIOC->BSRR = (uint16_t)1<<(ptx_n%16);
  else
    GPIOC->BRR = (uint16_t)1<<(ptx_n%16);
  break;
case 3:
  if(dat)
    GPIOD->BSRR = (uint16_t)1<<(ptx_n%16);
  else
    GPIOD->BRR = (uint16_t)1<<(ptx_n%16);
  break;
case 4:
  if(dat)
    GPIOE->BSRR = (uint16_t)1<<(ptx_n%16);
  else
    GPIOE->BRR = (uint16_t)1<<(ptx_n%16);
  break;
  }
}

void gpio_rev(PTX_n ptx_n)//                                                       �������ŵ�ƽ��ת����
{//                                                                                 Sample: 
  switch(ptx_n/16)//                                                                gpio_rev(C13);
  {
case 0:
  if(GPIO_ReadOutputDataBit(GPIOA,(uint16_t)1<<(ptx_n%16)))
    GPIOA->BRR = (uint16_t)1<<(ptx_n%16);
  else
    GPIOA->BSRR = (uint16_t)1<<(ptx_n%16);
  break;
case 1:
  if(GPIO_ReadOutputDataBit(GPIOB,(uint16_t)1<<(ptx_n%16)))
    GPIOB->BRR = (uint16_t)1<<(ptx_n%16);
  else
    GPIOB->BSRR = (uint16_t)1<<(ptx_n%16);
  break;
case 2:
  if(GPIO_ReadOutputDataBit(GPIOC,(uint16_t)1<<(ptx_n%16)))
    GPIOC->BRR = (uint16_t)1<<(ptx_n%16);
  else
    GPIOC->BSRR = (uint16_t)1<<(ptx_n%16);
  break;
case 3:
  if(GPIO_ReadOutputDataBit(GPIOD,(uint16_t)1<<(ptx_n%16)))
    GPIOD->BRR = (uint16_t)1<<(ptx_n%16);
  else
    GPIOD->BSRR = (uint16_t)1<<(ptx_n%16);
  break;
case 4:
  if(GPIO_ReadOutputDataBit(GPIOE,(uint16_t)1<<(ptx_n%16)))
    GPIOE->BRR = (uint16_t)1<<(ptx_n%16);
  else
    GPIOE->BSRR = (uint16_t)1<<(ptx_n%16);
  break;
  }
}

uint8 gpio_get(PTX_n ptx_n)//                                                      �������ŵ�ƽ��ȡ����
{//                                                                                 Sample:
    switch(ptx_n/16)//                                                              gpio_get(C13);
  {
case 0:
  return GPIO_ReadInputDataBit(GPIOA, 1<<ptx_n%16);
case 1:
  return GPIO_ReadInputDataBit(GPIOB, 1<<ptx_n%16);
case 2:
  return GPIO_ReadInputDataBit(GPIOC, 1<<ptx_n%16);
case 3:
  return GPIO_ReadInputDataBit(GPIOD, 1<<ptx_n%16);
case 4:
  return GPIO_ReadInputDataBit(GPIOE, 1<<ptx_n%16);
  }
}

uint16 gpio_read(GPIO_TypeDef* GPIOx)//                                            ��������������
{//                                                                                 Sample:
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));//                                        state = gpio_read(PORTC);
  return ((uint16_t)GPIOx->IDR);
}

void gpio_write(GPIO_TypeDef* GPIOx, uint16_t PortVal)//                           д������������
{//                                                                                 Sample:
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));//                                        gpio_write(0x55);
  GPIOx->ODR = PortVal;
}

uint8 gpio_getoutput(PTX_n ptx_n)//                                                �������������ֵ
{//                                                                                 Sample:
  uint8_t bitstatus = 0x00;//                                                       state = gpio_getoutput(C13);
  switch(ptx_n/16)                                                           
  {
case 0:
    bitstatus = GPIO_ReadOutputDataBit(GPIOA, 1<<(ptx_n%16));
    break;
case 1:
    bitstatus = GPIO_ReadOutputDataBit(GPIOB, 1<<(ptx_n%16));
    break;
case 2:
    bitstatus = GPIO_ReadOutputDataBit(GPIOC, 1<<(ptx_n%16));
    break;
case 3:
    bitstatus = GPIO_ReadOutputDataBit(GPIOD, 1<<(ptx_n%16));
    break;
case 4:
    bitstatus = GPIO_ReadOutputDataBit(GPIOE, 1<<(ptx_n%16));
    break;
  }
  return bitstatus;
}

void RCC_Configuration()                                                           //ʱ�����ú���
{
  /* ʹ��APB2ʱ�� */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB  | 
                         RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD  | 
                         RCC_APB2Periph_GPIOE | RCC_APB2Periph_AFIO , ENABLE);

#if 0
  /* ʹ��APB1ʱ�� */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

  /* ʹ��AHBʱ�� */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
#endif
}