#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "string.h"
#include "utils.h"


/**
 * @brief Creates the publicFIFO.
 *
 * @param argc 
 * @param argv 
 * @return Whether it was successful or not. 
 */
int create_publicFIFO(int argc, char* argv[]);

/**
 * @brief Unlinks the publicFifo
 * 
 * @param argc 
 * @param argv 
 * @return Whether it was successful or not.
 */
int unlink_publicFIFO(int argc, char* argv[]);