#pragma once

#include <stdio.h>
#include <sys/stat.h> //int chmod(const char *pathname, mode_t mode);
#include <dirent.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/times.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include "utils.h"
#include "signal.h"

enum event{PROC_CREAT, PROC_EXIT, SIGNAL_RECV, SIGNAL_SENT, FILE_MODF};

extern struct tms *buf;
extern clock_t start,mid,end;
extern long ticks;
/**
 * @brief Reads the path passed in the parameter.
 * 
 * @param envp 
 */
void env_path(char *envp[]);
/**
 * @brief Registers an event without signal, saving the time it took to process.
 * 
 * @param event 
 * @param pid 
 * @param envp 
 * @param argv 
 * @param argc 
 * @param after_buf 
 * @param before_buf 
 */
void mke_register_wout_signal(enum event event,  pid_t pid, char *envp[], char* argv[], int argc, struct stat after_buf,struct stat before_buf);
/**
 * @brief Registers an event with signal, saving the time it took to process.
 * 
 * @param event 
 * @param pid 
 * @param signo 
 * @param exit_c 
 */
void mke_register_w_signal(enum event event,  pid_t pid, int signo, int exit_c);
/**
 * @brief Opens file ("parent" process).
 * 
 * @param envp 
 */
void init_file(char *envp[]);
/**
 * @brief Opens file ("Child" process).
 * 
 * @param envp 
 */
void init_file_children(char *envp[]);
