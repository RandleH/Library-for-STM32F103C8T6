
#include "oled.h"
#include "delay.h"

void SoftwareDelay(uint32_t Cnt){while(Cnt--);}

int main(void)
{
    delay_init(72);
    OLED screen(I2C1,128,64,0x78,"SSD1106");
    screen.print("Hello world");
    screen.print("This is an OLED test");
    screen.print("I hope you enjoy it");
    screen.print("Ready to scroll...");
    delay_ms(2000);
    screen.print("a");delay_ms(500);
    screen.print("b");delay_ms(500);
    screen.print("c");delay_ms(500);
    screen.print("d");delay_ms(500);
    screen.print("e");delay_ms(500);
    screen.print("f");delay_ms(500);
    screen.print("g");delay_ms(500);
    screen.print("h");delay_ms(500);
    screen.print("i");delay_ms(500);
    screen.print("j");delay_ms(500);
    while(1){
    }
}


