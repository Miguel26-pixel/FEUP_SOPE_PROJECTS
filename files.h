#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h> //int chmod(const char *pathname, mode_t mode);
#include <dirent.h>
#include <string.h>
#include <stdbool.h>
#include "utils.h"
#include "permissions.h"
#include "register.h"
#include "options.h"

int processSingle(int argc, char* argv[], char* envp[]);

int processR(int argc, char* argv[], char* envp[]);