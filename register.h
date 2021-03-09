#pragma once
#include <stdio.h>
#include <sys/stat.h> //int chmod(const char *pathname, mode_t mode);
#include <dirent.h>
#include <string.h>
#include <stdbool.h>
#include <sys/times.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include "utils.h"

enum event{PROC_CREAT, PROC_EXIT, SIGNAL_RECV, SIGNAL_SENT, FILE_MODF};

extern struct tms *buf;
extern clock_t start,mid,end;
extern long ticks;

void env_path(char *envp[], char* file);

void mke_register(enum event event,  pid_t pid, char *envp[], char* argv[], int argc, struct stat after_buf,struct stat before_buf);
