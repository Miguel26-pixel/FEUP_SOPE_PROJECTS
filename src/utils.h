#pragma once
#include <sys/times.h>
#include <unistd.h>
extern clock_t start;
extern long ticks;
extern struct tms *buf;

int convertDecimalToOctal(int decimalNumber);

void init_clock();

