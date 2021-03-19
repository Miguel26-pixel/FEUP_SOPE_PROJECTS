#include "utils.h"

extern char ** environ;

int convertDecimalToOctal(int decimalNumber) {
    int octalNumber = 0, i = 1;

    while (decimalNumber != 0)
    {
        octalNumber += (decimalNumber % 8) * i;
        decimalNumber /= 8;
        i *= 10;
    }

    return octalNumber;
}


void init_clock(char *envp[]){
    start = times(buf);
    char temp[50];
    sprintf(temp, "%ld", start);
    if(setenv("START_CLOCK",temp,0)==-1) perror("ERROR");
    ticks = sysconf(_SC_CLK_TCK);
}