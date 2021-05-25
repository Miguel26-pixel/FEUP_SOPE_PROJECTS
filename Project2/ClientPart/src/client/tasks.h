#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "tasks.h"
#include <fcntl.h>
#include "string.h"
#include "utils.h"
#include "communication.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "fifo.h"

extern struct message m;

/**
 * @brief Struct that encapsulates the arguments that are passed to the threads.
 */
struct argCV {
    int argc;
    char **argv;
    int id;
};

/**
 * @brief Creates threads and its where the main process is done. 
 * @return Indication that it was successful.
 */
int process_tasks(int argc, char* argv[]);

/**
 * @brief Start routine that process all the threads.
 * @return void* 
 */
void * process_threads(void* arg);