#pragma once
#include <stdio.h>
#include <sys/stat.h> //int chmod(const char *pathname, mode_t mode);
#include <dirent.h>
#include <string.h>
#include <stdbool.h>

struct stat processMODE(int argc, char* argv[]);

struct stat processOCTALMODE(int argc, char* argv[]);

bool changePermissions(char *dir, struct stat stat_buf);