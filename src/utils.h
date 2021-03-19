#pragma once
#include <sys/times.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/times.h>
#include <string.h>
#include <stdbool.h>
extern clock_t start;
extern long ticks;
extern struct tms *buf;

int convertDecimalToOctal(int decimalNumber);

void init_clock();