#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h> //int chmod(const char *pathname, mode_t mode);
#include <sys/wait.h>
#include <dirent.h>
#include <string.h>
#include <stdbool.h>
#include "utils.h"
#include "permissions.h"
#include "register.h"
#include "options.h"

/**
 * @brief Processes the command, if it is not with the -R option.
 * 
 * @param argc 
 * @param argv 
 * @param envp 
 * @return int 
 */
int processSingle(int argc, char* argv[], char* envp[]);
/**
 * @brief Processes the command, only when it has the -R option.
 * 
 * @param argc 
 * @param argv 
 * @param envp 
 * @return int 
 */
int processR(int argc, char* argv[], char* envp[]);