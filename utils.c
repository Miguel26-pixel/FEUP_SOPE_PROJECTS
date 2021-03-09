#include "utils.h"
int convertDecimalToOctal(int decimalNumber)
{
    int octalNumber = 0, i = 1;

    while (decimalNumber != 0)
    {
        octalNumber += (decimalNumber % 8) * i;
        decimalNumber /= 8;
        i *= 10;
    }

    return octalNumber;
}


void init_clock(){
    start = times(buf);
    ticks = sysconf(_SC_CLK_TCK);
}