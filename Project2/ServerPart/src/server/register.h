#pragma once
#include <stdio.h>
#include "communication.h"

extern struct message m;

/**
 * @brief Registers a message operation
 * 
 * @param sms 
 * @param oper 
 */
void register_message(struct message* sms, char * oper);
