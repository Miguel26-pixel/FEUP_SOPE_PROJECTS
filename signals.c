#include "signals.h"

unsigned nftot = 0, nfmod = 0;
bool signal_sent = false;
char* path;
int current_pid = 0;
extern pid_t pid;

void getFichDir(const char *fichDir){
        path = malloc(sizeof(fichDir));
        strcpy(path,fichDir);
}

void sigcontHandler(int sig) {
    mke_register_w_signal(SIGNAL_RECV,  getpid(), sig);
}

void sigHandler(int sig) {
    mke_register_w_signal(SIGNAL_SENT,  getpid(), sig);
    printf("td ok");
    mke_register_w_signal(SIGNAL_RECV,  getpid(), sig);
    if (getpid() == pid) {
        char answer;
        printf("\n Programmed paused...\n");
        printf("pid: %d; fich/dir: %s; nftot: %d; nfmod: %d",getpid(),path,nftot,nfmod);
        if(signal_sent){signal_sent=false;}
        printf("\nWould you like to continue? Enter y or n: ");
        scanf(" %c", &answer);
        if (answer == 'y') {
            mke_register_w_signal(SIGNAL_SENT,  getpid(), SIGCONT);
            kill(0, SIGCONT);
        }
        else
            exit(0);
        signal(SIGINT, sigHandler);
        signal_sent = true;
        current_pid = getpid();
        return;
    }
    else {
        signal(SIGCONT, sigcontHandler);
        pause();
    }
}