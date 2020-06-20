#include "common.h"
#include <iostream>

hash_t __read__(char const* str)  {  
  hash_t ret{basis};   
  while(*str){  
    ret ^= *str;  
    ret *= prime;  
    str++;  
  }  
  return ret;
} 

