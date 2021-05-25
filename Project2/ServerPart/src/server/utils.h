#pragma once
#include <sys/times.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>

/**
 * @brief Starts the clock seeds the random number generator used by the function rand.
 */
void init_clock();

/**
 * @brief Checks if a timeout has already occurred for client.
 */
bool check_time(int argc, char* argv[]);

/**
 * @brief Gets the remaining time before timeout in seconds.
 * @return time remaining, in seconds.
 */
time_t get_remaining_time_secs(char * argv[]);

/**
 * @brief Gets the remaining time before timeout in microseconds.
 * @return time remaining, in microseconds.
 */
suseconds_t get_remaining_time_micro(char * argv[]);