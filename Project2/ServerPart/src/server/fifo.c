#include "fifo.h"

int create_publicFIFO(int argc, char* argv[]){
    char name[2000];
    snprintf(name, sizeof(name), "%s", argv[argc - 1]);
    if (mkfifo(name , 0666) < 0) {
        perror("ERROR");
        return -1;
    }
    return 0;
}


int unlink_publicFIFO(int argc, char* argv[]) {
    char name[2000];
    snprintf(name, sizeof(name), "%s", argv[argc - 1]);
    if (unlink(name)){
        perror("ERROR");
        return -1;
    }
    return 0;
}