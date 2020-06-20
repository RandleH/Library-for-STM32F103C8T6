#include <string>
#include "adc.h"
#include "oled.h"
#include "delay.h"


int main(void)
{
    delay_init(72);
    volatile uint16_t analogVoltage = 0; 

    ADC     adc_module(ADC1,1,&analogVoltage);
    OLED    screen(I2C1,128,64,0x78,"SSD1106");
    while(1){
        screen.print(to_string(analogVoltage).data());
        delay_ms(10);
    }
}
