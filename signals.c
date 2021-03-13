#include "signals.h"

unsigned nftot = 0, nfmod = 0;
bool paused = false;
bool signal_sent = false;
char* path;
int current_pid = 0;
extern pid_t pid;
bool cont = false;

void getFichDir(char *fichDir){
        path = fichDir;
}

void sigcontHandler(int sig) {
    //signal continuar
    cont = true;
}


void sigHandler(int sig) {
    //send Ctrl-C
    //signal CTrl-C
    cont = false;
    if (getpid() == pid) {
        char answer;
        printf("\n Programmed paused...\n");
        printf("pid: %d; fich/dir: %s; nftot: %d; nfmod: %d",getpid(),path,nftot,nfmod);
        if(signal_sent){signal_sent=false;}
        printf("\nWould you like to continue? Enter y or n: ");
        scanf(" %c", &answer);
        if (answer == 'y') {
            paused = false;
            //send signal to child
            kill(0, SIGCONT);
            cont = true;
        }
        else
            exit(0);
        signal(SIGINT, sigHandler); // reinstall handler
        signal_sent = true;
        current_pid = getpid();
        return;
    }
    else {
        signal(SIGCONT, sigcontHandler);
        pause();
    }
}