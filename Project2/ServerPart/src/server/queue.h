#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "communication.h"

extern struct message m;

/**
 * @brief Initialize the queue where the messages are stored
 * 
 * @param max 
 */
void initQueue(int max);

/**
 * @brief Returns the element in front of the queue
 * 
 * @return struct message* 
 */
struct message* top();

/**
 * @brief Returns wheter the queue is empty or not
 * 
 * @return true 
 * @return false 
 */
bool isEmpty();


/**
 * @brief Returns true if the queue is full or false otherwise
 * 
 * @return true 
 * @return false 
 */
bool isFull();

/**
 * @brief Return the size of the queue
 * 
 * @return int 
 */
int size();

/**
 * @brief Inserts a message into the queue if the queue is not full
 * 
 * @param data 
 */
void insert(struct message* data);

/**
 * @brief Gets the next message and reduces the item count
 * 
 * @return struct message* 
 */

struct message* pop();

/**
 * @brief Free the memory previously allocated for the queue
 */
void freeQueue();

/**
 * @brief Return the number of elements in the queue
 * 
 * @return int 
 */
int getItemCount();

/**
 * @brief Get the total number of Messages
 * 
 * @return int 
 */
int getNumMessages();