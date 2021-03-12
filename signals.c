#include "signals.h"

unsigned nftot = 0, nfmod = 0;
bool paused = false;
bool signal_sent = false;
char* path;
int current_pid = 0;

void getFichDir(char *fichDir){
        path = fichDir;
}


void sigHandler(int sig)
{
    char answer;
    printf("\n Programmed paused...\n");
    printf("pid: %d; fich/dir: %s; nftot: %d; nfmod: %d",getpid(),path,nftot,nfmod);
    if(signal_sent){signal_sent=false;}
    printf("\nWould you like to continue? Enter y or n: ");
    scanf(" %c", &answer);
    if (answer == 'y')
    {
        paused = false;
    }
    else
        exit(0);
    signal(SIGINT, sigHandler); // reinstall handler
    signal_sent = true;
    current_pid = getpid();
    return;
}