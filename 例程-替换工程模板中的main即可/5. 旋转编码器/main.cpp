


#include <string>
#include "gpio.h"
#include "oled.h"
#include "adc.h"
#include "encoder.h"
#include "delay.h"
#include "stm32f10x.h"

int main(void)
{
    delay_init(72);
    GPIO led(C13,GPO,GPL);
    
    uint16_t value = 0;
    OLED    screen(I2C1,128,64,0x78,"SSD1106");
    ENCODER encoder(A6,A7,A8);

    while(1){
        value = (uint16_t)encoder.read();
        screen.print(to_string(value).data);
    }
}


