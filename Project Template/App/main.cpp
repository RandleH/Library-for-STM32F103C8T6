
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
        //value = (uint16_t)encoder.read();
        if(encoder.A.read()==false){
            delay_us(20);
            value = (uint16_t)(encoder.A.read()-encoder.B.read());
            led.set(GPH);
        }
        else{
            value = 0;
            led.set(GPL);
        }
     
        //screen.print(to_string(value).data());
    }
}







/*
#include <string>
#include "gpio.h"
#include "oled.h"
#include "adc.h"
#include "encoder.h"
#include "delay.h"
#include "stm32f10x.h"
void SoftwareDelay(uint32_t Cnt)
{
  while(Cnt--);
}
string  tmp("--------");
string& p = tmp;
int main(void)
{
    delay_init(72);
    GPIO led(C13,GPO,GPL);
    GPIO dip(A8,GPIPU);
    SoftwareDelay(10000000);
    led.set(GPH);
    SoftwareDelay(10000000);

    
    volatile uint16_t     val = 0;
    uint16_t              en  = 0;
    OLED    screen(I2C1,128,64,0x78,"SSD1106");
    ADC     joyStick(ADC1,1,&val);
    ENCODER encoder(A6,A7,A9);

    ScreenLabel tag[6];
    tag[0].name  = "Vano:";
    tag[0].value = (uint16_t*)&val;
    tag[0].unit  = "raw";
    
    tag[1].name  = NULL;
    tag[1].value = NULL;
    tag[1].unit  = NULL;

    tag[2].name  = "Vm:";
    tag[2].value = (uint16_t*)&val;
    tag[2].unit  = "V";

    tag[3].name  = NULL;
    tag[3].value = NULL;
    tag[3].unit  = NULL;

    tag[4].name  = "a:";
    tag[4].value = (uint16_t*)&encoder;
    tag[4].unit  = "m/s2";

    tag[5].name  = NULL;
    tag[5].value = NULL;
    tag[5].unit  = NULL;

    screen.GUIConfig(tag,6,__COLUMN_CHART);
    

    while(1){
    if(dip.read()==GPH)
        led.set(GPL);
  	else
        led.set(GPH);
    switch(encoder.read()){
        case __ENCODER_CLOCK_WISE:      en>4096?en=4096:en++;break;
        case __ENCODER_ANTI_CLOCK_WISE: en==0 ?en=0  :en--;break;
        case __ENCODER_PRESS_DOWN:break;
    }
    //SoftwareDelay(1000000);
    screen.showResult();
    
  }
}
*/

