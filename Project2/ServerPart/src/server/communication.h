#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include "tasks.h"
#include <sys/time.h>
#include "utils.h"
#include "register.h"
#include <sys/select.h>


/**
 * @brief struct that will contain the message.
 * RID - request id
 * PID - process id
 * TID - thread id
 * TSKLOAD - task load
 * TSKRES - task result
 */
struct message {
	int rid;	// request id
	pid_t pid;	// process id
	pthread_t tid;	// thread id
	int tskload;	// task load
	int tskres;	// task result
};

/**
 * @brief Updates the process ID and the thread ID of the struct message
 * 
 * @param sms 
 */
void update_message(struct message * sms);

/**
 * @brief Function used to receive a message from client
 * 
 * @param argc 
 * @param argv 
 * @param sms 
 * @return Whether it was successful or not
 */
int recieve_message(int argc,char* argv[], struct message * sms);

/**
 * @brief Inserts the message to the queue
 * 
 * @param sms 
 * @return Whether it was successful or not
 */
int insert_message(struct message * sms);

/**
 * @brief Send the message to client and calls the operation register to save the operation info 
 * 
 * @param sms 
 * @param path 
 * @return Whether it was successful or not
 */
int send_message(struct message * sms, char * path);

/**
 * @brief Notify the finish of the process by sending a message with a specific negative tskres in struct message
 * 
 * @return Whether it was successful or not
 */
int notify_finish();


