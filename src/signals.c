#include "signals.h"

unsigned nftot = 0, nfmod = 0;
bool signal_sent = false;
char* path;
int current_pid = 0;
extern pid_t pid;

void getFichDir(const char *fichDir){
        path = malloc(strlen(fichDir)+1);
        strcpy(path,fichDir);
}

void sigcontHandler(int sig) {
    mke_register_w_signal(SIGNAL_SENT,  getpid(), sig, 0);
    mke_register_w_signal(SIGNAL_RECV,  getpid(), sig, 0);
    
}

void sigtermHandler(int sig) {
    mke_register_w_signal(SIGNAL_SENT,  getpid(), sig, 0);
    mke_register_w_signal(SIGNAL_RECV,  getpid(), sig, 0);
    mke_register_w_signal(PROC_EXIT,  getpid(),0, 0);
    exit(0);
} 

void sigHandlerDefault(int sig) {
    mke_register_w_signal(SIGNAL_RECV,  getpid(), sig, 0);
}

void sigHandler(int sig) {
    mke_register_w_signal(SIGNAL_SENT,  getpid(), sig, 0);
    mke_register_w_signal(SIGNAL_RECV,  getpid(), sig, 0);
    if (getpid() == getpgrp()) {
        char answer;
        printf("\n Programmed paused...\n");
        printf("pid: %d; fich/dir: %s; nftot: %d; nfmod: %d\n",getpid(),path,nftot,nfmod);
        if(signal_sent){signal_sent=false;}
        printf("Would you like to continue? Enter y or n: \n");
        scanf(" %c", &answer);
        if (answer == 'y') {
            kill(0, SIGCONT);
            mke_register_w_signal(PROC_EXIT,  getpid(),0 , 0);
        }
        else{
            kill(0, SIGTERM);
            mke_register_w_signal(PROC_EXIT,  getpid(),0 , 0);
            exit(0);
        }
        signal(SIGINT, sigHandler);
        signal_sent = true;
        return;
    }
    else {
        printf("pid: %d; fich/dir: %s; nftot: %d; nfmod: %d\n",getpid(),path,nftot,nfmod);
        signal(SIGCONT, sigcontHandler);
        signal(SIGTERM, sigtermHandler);
        pause();
    }
}