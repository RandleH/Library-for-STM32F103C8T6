#include <cmath>
#include <cstdint>


#define EPSILON 0.00001

class MATH{
public: 
    static uint32_t map(register uint32_t value,register uint32_t i_max,register uint32_t o_max){
    	if(i_max == 0||o_max == 0||value>i_max) 
    		return 0;
    	return (uint32_t)(value*o_max/i_max);
    }
    static float normalization(register uint32_t value,register uint32_t i_min,register uint32_t i_max){
    	if(i_min > i_max||value > i_max||value < i_min) 
    		return 0.0;
    	return (value/((float)(i_max-i_min)));
    }
};

