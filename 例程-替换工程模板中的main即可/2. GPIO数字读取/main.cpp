#include "gpio.h"
#include "delay.h"

void SoftwareDelay(uint32_t Cnt){while(Cnt--);}

int main(void)
{
    delay_init(72);
    GPIO digital_1(A6,GPIPU);//上拉
    GPIO digital_2(A7,GPIPD);//下拉
    GPIO digital_3(A8,GPIFL);//浮空

    GPIO led(C13,GPO,GPL);//指示灯
    while(1){
        if(digital_2.read() == GPH)
            led.set(GPL);
        else
            led.set(GPH);
    }
}