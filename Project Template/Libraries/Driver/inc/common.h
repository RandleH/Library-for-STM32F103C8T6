#include <cstdint>
#include <cstring>
#include <cstddef>

#ifndef _COMMON_H
#define _COMMON_H

typedef std::uint64_t hash_t; 
constexpr hash_t prime = 0x100000001B3ull;  
constexpr hash_t basis = 0xCBF29CE484222325ull; 

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

typedef enum{
//0~15
    A0,  A1,  A2,  A3,  A4,  A5,  A6,  A7,  A8,  A9,  A10, A11, A12, A13, A14, A15,
//16~31
    B0,  B1,  B2,  B3,  B4,  B5,  B6,  B7,  B8,  B9,  B10, B11, B12, B13, B14, B15,
//32~47
    C0,  C1,  C2,  C3,  C4,  C5,  C6,  C7,  C8,  C9,  C10, C11, C12, C13, C14, C15,
//48~63
    D0,  D1,  D2,  D3,  D4,  D5,  D6,  D7,  D8,  D9,  D10, D11, D12, D13, D14, D15,
//64~79
    E0,  E1,  E2,  E3,  E4,  E5,  E6,  E7,  E8,  E9,  E10, E11, E12, E13, E14, E15,
//AF_PIN
    N_A,
} PTX_n;

#define PTX(PTX_n)  (PTX_n>>4)  // PTX_n/16
#define PTn(PTX_n)  ((uint16_t)(1<<(PTX_n&0x0f)))// 1<<(PTX_n%16)


#define MAKE_INTERVAL_UINT8(x,y)  (x<y?(uint8_t)((0xff<<(y+1))|(~(0xff<<(x)))):(uint32_t)((0xff<<(x+1))|(~(0xff<<(y)))))
#define MAKE_INTERVAL_UINT16(x,y) (x<y?(uint16_t)((0xffff<<(y+1))|(~(0xffff<<(x)))):(uint16_t)((0xffff<<(x+1))|(~(0xffff<<(y)))))
#define MAKE_INTERVAL_UINT32(x,y) ((x)<(y)?(uint32_t)((0xffffffff<<((y)+1))|(~(0xffffffff<<(x)))):(uint32_t)((0xffffffff<<((x)+1))|(~(0xffffffff<<(y)))))

constexpr hash_t i_want_to_(char const* str, hash_t last_value = basis)
{  return *str ? i_want_to_(str+1, (*str ^ last_value) * prime) : last_value;  }  
hash_t __read__(char const* str);

template <typename T, int N>                                                                                                                                                                  
size_t ArraySize (T (&arr)[N]) {return N;}

#endif
