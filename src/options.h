#pragma once
#include <stdio.h>
#include <sys/stat.h> //int chmod(const char *pathname, mode_t mode);
#include <dirent.h>
#include <string.h>
#include <stdbool.h>
#include "utils.h"

void processOPTIONSvc(struct stat before, struct stat after,int argc,char* argv[]);

void printPermissions(struct stat fileStat);

bool checkR(int argc, char* argv[]);

bool checkV(int argc, char *argv[]);

bool checkC(int argc, char *argv[]);