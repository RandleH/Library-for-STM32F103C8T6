#include "gpio.h"
#include "delay.h"

void SoftwareDelay(uint32_t Cnt){while(Cnt--);}

int main(void)
{
    delay_init(72);
    GPIO led(C13,GPO,GPL);//指示灯

    while(1){
        led.set(GPH);
        delay(1000000);
        led.set(GPL);
        delay(1000000);
    }
}