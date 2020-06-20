#include <map>
#include "stm32f10x.h"
#ifndef _INTTERRUPT_H
#define _INTTERRUPT_H

#ifdef __cplusplus
extern "C"{
#endif
    void EXTI0_IRQHandler(void);
    void EXTI1_IRQHandler(void);
    void EXTI2_IRQHandler(void);
    void EXTI3_IRQHandler(void);
    void EXTI4_IRQHandler(void);

#ifdef STM32F10X_MD
    void EXTI9_5_IRQHandler(void);
    void EXTI15_10_IRQHandler(void);
#endif

#ifdef __cplusplus
}
#endif

using namespace std;
typedef map <IRQn_Type,void(*)(void)> IRQ_FUNC_MAP;

class ISR{
public:
    static IRQ_FUNC_MAP IRQ_FUNC;
    static IRQ_FUNC_MAP import_IRQ_FUNC(void){
    	IRQ_FUNC_MAP tmp_map;
    	tmp_map.insert(make_pair(EXTI0_IRQn,EXTI0_IRQHandler));
    	tmp_map.insert(make_pair(EXTI1_IRQn,EXTI1_IRQHandler));
    	tmp_map.insert(make_pair(EXTI2_IRQn,EXTI2_IRQHandler));
    	tmp_map.insert(make_pair(EXTI3_IRQn,EXTI3_IRQHandler));
    	tmp_map.insert(make_pair(EXTI4_IRQn,EXTI4_IRQHandler));
    	/* ... */
#ifdef STM32F10X_MD//stm32f103c8t6
        tmp_map.insert(make_pair(EXTI9_5_IRQn,EXTI9_5_IRQHandler));
        tmp_map.insert(make_pair(EXTI15_10_IRQn,EXTI15_10_IRQHandler));
#endif
    	return tmp_map;
    }
};

#endif





