#include <libmx.h>

float mx_round(float num, int precision){
    float base = 1;

    for (int i = 0; i < precision; i++)
    {
        base *= 10;
    }
    
    num *= base;

    if (num < 0.0)
        return ((int)(num - 0.5)) / base;
    else
        return ((int)(num + 0.5) ) / base;
    
}
