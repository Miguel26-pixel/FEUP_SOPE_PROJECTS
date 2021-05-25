#pragma once
#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>

#include "utils.h"
#include "communication.h"
#include "queue.h"
#include "lib.h"
#include "fifo.h"


/**
 * @brief Struct that encapsulates the arguments that are passed to the threads.
 */
struct argCV {
    int argc;
    char **argv;
    struct message * msg;
};

/**
 * @brief Creates threads and its where the main process is done. 
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int process_tasks(int argc, char* argv[]);

/**
 * @brief Start routine that process all the producers threads.
 * 
 * @param arg 
 * @return void* 
 */
void* process_threads(void *arg);

/**
 * @brief Start routine that process the consumer thread.
 * 
 * @param arg 
 * @return void* 
 */
void* process_sc(void *arg);

/**
 * @brief Free the allocated memory for the message in the parameter
 * 
 * @param sms 
 */
void free_message(struct message * sms, char * path);

