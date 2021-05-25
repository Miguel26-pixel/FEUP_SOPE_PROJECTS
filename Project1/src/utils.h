#pragma once
#include <sys/times.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/times.h>
#include <string.h>
#include <stdbool.h>
extern clock_t start;    // Type capable of represents the process running time of implementation
extern long ticks;       // Number of clock ticks per second
extern struct tms *buf;  // describes CPU time used by a process and its children
/**
 * @brief This function receives a decimal number and converts it to the corresponding octal number
 * 
 * 
 * @param decimalNumber 
 * @return int 
 */
int convertDecimalToOctal(int decimalNumber);

/**
 * @brief Stars the clock and saves the number of clock ticks per second
 * 
 */
void init_clock();