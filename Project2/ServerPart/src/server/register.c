#include "register.h"


void register_message(struct message* sms, char * oper) {
    printf("%ld ; %d ; %d ; %ld ; %d ; %d ; %s\n", time(NULL), sms->rid, getpid(), pthread_self(), sms->tskload, sms->tskres, oper);
}