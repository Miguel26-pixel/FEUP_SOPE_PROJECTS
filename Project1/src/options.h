#pragma once
#include <stdio.h>
#include <sys/stat.h> //int chmod(const char *pathname, mode_t mode);
#include <dirent.h>
#include <string.h>
#include <stdbool.h>
#include "utils.h"

/**
 * @brief Processes the options verbal mode (-v) and c-mode, applying changes if need be.
 * 
 * @param before 
 * @param after 
 * @param argc 
 * @param argv 
 */
void processOPTIONSvc(struct stat before, struct stat after,int argc,char* argv[]);
/**
 * @brief Prints the current permissions.
 * 
 * @param fileStat 
 */
void printPermissions(struct stat fileStat);
/**
 * @brief Checks whether the Permission is -R
 * 
 * @param argc 
 * @param argv 
 * @return true 
 * @return false 
 */
bool checkR(int argc, char* argv[]);
/**
 * @brief Checks whether the Permission is -v
 * 
 * @param argc 
 * @param argv 
 * @return true 
 * @return false 
 */
bool checkV(int argc, char *argv[]);
/**
 * @brief Checks whether the Permission is -c
 * 
 * @param argc 
 * @param argv 
 * @return true 
 * @return false 
 */
bool checkC(int argc, char *argv[]);