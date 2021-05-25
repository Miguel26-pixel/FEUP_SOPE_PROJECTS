#pragma once
#include <stdio.h>
#include <sys/stat.h> //int chmod(const char *pathname, mode_t mode);
#include <dirent.h>
#include <string.h>
#include <stdbool.h>

/**
 * @brief Processes the mode in normal format and updates the stat struct
 * 
 * @param argc 
 * @param argv 
 * @return struct stat 
 */
struct stat processMODE(int argc, char* argv[]);
/**
 * @brief Processes the mode in octal format and updates the stat struct.
 * 
 * @param argc 
 * @param argv 
 * @return struct stat 
 */
struct stat processOCTALMODE(int argc, char* argv[]);
/**
 * @brief Changes the permissions to the ones given in the parameters.
 * 
 * @param dir 
 * @param stat_buf 
 * @return true 
 * @return false 
 */
bool changePermissions(char *dir, struct stat stat_buf);