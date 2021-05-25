#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <stdbool.h>
#include "register.h"

/**
 * @brief Saves the input Fich/Dir by the user in the variable char* path
 * 
 * @param fichDir 
 */
void getFichDir(const char *fichDir);

/**
 * @brief Saves in the event's register file the info when SIGTERM is received (when the user asks the programm to end) and terminates the process
 * 
 * @param sig 
 */
void sigtermHandler(int sig);
/**
 * @brief Saves in the event's register file the info when SIGCONT is received (when the user asks the programm to continue)
 * 
 * @param sig 
 */
void sigcontHandler(int sig);
/**
 * @brief Process the signal SIGINT, when the user presses CTRL-C
 * 
 * @param sig 
 */
void sigHandler(int sig);
/**
 * @brief Saves in the event's register file the info of other signals
 * 
 * @param sig 
 */
void sigHandlerDefault(int sig);