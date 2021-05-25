#include <stdio.h>
#include <sys/times.h>
#include <pthread.h>
#include "utils.h"
#include "tasks.h"

clock_t start, end;
struct tms t;

int main(int argc, char* argv[], char* envp[]) {
    if (argc != 4) { 
        printf("usage: c <-t nsecs> fifoname\n");
        return 0;
    }

    init_clock();

    open_publicFIFO(argc,argv);

    process_tasks(argc,argv);

    return 0;
}