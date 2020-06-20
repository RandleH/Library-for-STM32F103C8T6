
#include "misc.h"

#ifndef _DELAY_H
#define _DELAY_H

#ifdef __cplusplus
extern "C"{
#endif

void delay_init(uint8_t SYSCLK);
void delay_ms(uint16_t  nms);
void delay_us(uint32_t  nus);

#ifdef __cplusplus
}
#endif 

#endif