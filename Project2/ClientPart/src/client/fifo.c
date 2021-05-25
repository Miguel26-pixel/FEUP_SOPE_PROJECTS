#include "fifo.h"


int public_fifo;

int open_publicFIFO(int argc, char* argv[]){
    while ((public_fifo = open(argv[argc - 1], O_WRONLY)) < 0 && check_time(argv)) ;
    return 0;
}

int create_privateFIFO(struct message *sms) 
{
    char name[2000];
    snprintf(name,2000, "/tmp/%d.%ld", sms->pid, sms->tid);
    if (mkfifo(name , 0666) < 0) {
        perror("ERROR");
        return -1;
    }
    return 0;
}

int eliminate_privateFIFO(struct message *sms)
{
    char name[2000];
    snprintf(name, 2000, "/tmp/%d.%ld", sms->pid, sms->tid);
    if (unlink(name)){
        perror("ERROR");
        return -1;
    }
    return 0;
}