#include <stdio.h>
#include <sys/times.h>

#include "tasks.h"
#include "fifo.h"
#include "utils.h"

clock_t start, end;
struct tms t;

int main(int argc, char* argv[]) {
	if (!(argc == 4 || argc == 6)) {
		printf("usage: s <-t nsecs> [-l bufsz] fifoname\n");
        return 0;
	}

	init_clock();

	create_publicFIFO(argc, argv);

	process_tasks(argc, argv);

	return 0;
}