#include "headfile.h"
#ifndef my_stm32_H
#define my_stm32_H

//数据类型声明
typedef unsigned char       uint8;   //  8 bits 
typedef unsigned short int  uint16;  // 16 bits 
typedef unsigned long int   uint32;  // 32 bits 
typedef unsigned long long  uint64;  // 64 bits 

typedef char                int8;    //  8 bits 
typedef short int           int16;   // 16 bits 
typedef long  int           int32;   // 32 bits 
typedef long  long          int64;   // 64 bits 

typedef volatile int8       vint8;   //  8 bits 
typedef volatile int16      vint16;  // 16 bits 
typedef volatile int32      vint32;  // 32 bits 
typedef volatile int64      vint64;  // 64 bits 

typedef volatile uint8      vuint8;  //  8 bits 
typedef volatile uint16     vuint16; // 16 bits 
typedef volatile uint32     vuint32; // 32 bits 
typedef volatile uint64     vuint64; // 64 bits 

typedef enum // 枚举管脚编号 
{
    //  A端口     //0~15
    A0,  A1,  A2,  A3,  A4,  A5,  A6,  A7,  A8,  A9,  A10, A11, A12, A13, A14, A15,
    
    //  B端口     //16~31
    B0,  B1,  B2,  B3,  B4,  B5,  B6,  B7,  B8,  B9,  B10, B11, B12, B13, B14, B15,

    //  C端口     //32~47
    C0,  C1,  C2,  C3,  C4,  C5,  C6,  C7,  C8,  C9,  C10, C11, C12, C13, C14, C15,
    
    //  D端口     //48~63
    D0,  D1,  D2,  D3,  D4,  D5,  D6,  D7,  D8,  D9,  D10, D11, D12, D13, D14, D15,
    
    //  E端口     //64~79
    E0,  E1,  E2,  E3,  E4,  E5,  E6,  E7,  E8,  E9,  E10, E11, E12, E13, E14, E15,
    
} PTX_n;
/*
（1）GPIO_Mode_AIN 模拟输入 
（2）GPIO_Mode_IN_FLOATING 浮空输入
（3）GPIO_Mode_IPD 下拉输入 
（4）GPIO_Mode_IPU 上拉输入 
（5）GPIO_Mode_Out_OD 开漏输出
（6）GPIO_Mode_Out_PP 推挽输出
（7）GPIO_Mode_AF_OD 复用开漏输出 
（8）GPIO_Mode_AF_PP 复用推挽输出
*/
void gpio_init(PTX_n ptx_n,uint8 ddr);
void gpio_set(PTX_n ptx_n,uint8 dat);//电平设置
void gpio_rev(PTX_n ptx_n);     //电平翻转
uint8 gpio_get(PTX_n ptx_n);    //电平读取
uint16 gpio_read(GPIO_TypeDef* GPIOx);//PORT电平读取
void gpio_write(GPIO_TypeDef* GPIOx, uint16_t PortVal);//PORT电平写入
uint8 gpio_getoutput(PTX_n ptx_n);//

#define ALL ((uint16_t)0xFFFF)
#define GPO_PP 0x10     //推挽输出
#define GPO_OD 0x14     //开漏输出
#define GPO_AF_PP 0x18  //复用推挽输出    
#define GPO_AF_OD 0x1C  //复用开漏输出
#define GPI_PU 0x48     //上拉输入
#define GPI_PD 0x28     //下拉输入
#define GPI_AN 0x00     //模拟输入
#define GPI_FL 0x04     //浮空输入




#endif