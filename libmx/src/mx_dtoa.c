#include <libmx.h>

char *mx_dtoa(float d, int precision){
    float temp = d;
    for (int i = 0; i < precision; i++)
    {
        temp *= 10;
    }

    char *d_str = mx_itoa((int)temp);

    mx_realloc(d_str, 1);
    int len = mx_strlen(d_str);

    for (int i = len + 1; i >= len - precision; i--)
    {
        if (i == len - precision)
        {
            d_str[i] = '.';
            break;

        } else {

        d_str[i] = d_str[i - 1];

        }
    }
    
    return d_str;
}
