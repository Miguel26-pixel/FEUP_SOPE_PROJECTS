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
    mke_register_w_signal(SIGNAL_SENT,  getpid(), sig);
    mke_register_w_signal(SIGNAL_RECV,  getpid(), sig);
}

void sigkillHandler(int sig) {
    printf("td ok");
    mke_register_w_signal(SIGNAL_SENT,  getpid(), sig);
    mke_register_w_signal(SIGNAL_RECV,  getpid(), sig);
    exit(0);
} 

void sigHandler(int sig) {
    mke_register_w_signal(SIGNAL_SENT,  getpid(), sig);
    mke_register_w_signal(SIGNAL_RECV,  getpid(), sig);
    if (getpid() == pid) {
        char answer;
        printf("\n Programmed paused...\n");
        printf("pid: %d; fich/dir: %s; nftot: %d; nfmod: %d",getpid(),path,nftot,nfmod);
        if(signal_sent){signal_sent=false;}
        printf("\nWould you like to continue? Enter y or n: ");
        scanf(" %c", &answer);
        if (answer == 'y') {
            current_pid = getpid();
            printf("%d",current_pid);
            //mke_register_w_signal(SIGNAL_SENT,  getpid(), SIGCONT);
            kill(0, SIGCONT);
        }
        else{
            kill(0, SIGTERM);
            exit(0);
        }
        signal(SIGINT, sigHandler);
        signal_sent = true;
        return;
    }
    else {
        signal(SIGCONT, sigcontHandler);
        signal(SIGKILL, sigkillHandler);
        pause();
    }
}