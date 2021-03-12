#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <stdbool.h>

void getFichDir(char *fichDir);
void sigHandler(int sig);