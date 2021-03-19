#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <stdbool.h>
#include "utils.h"
#include "permissions.h"
#include "register.h"
#include "options.h"
#include "process.h"
#include "signals.h"

struct tms *buf;
clock_t start, end, mid;
long ticks;
pid_t pid;
extern int current_pid;
extern bool signal_sent;
extern int nfmod, nftot;

int main(int argc, char* argv[], char* envp[]) {
    int exit_c = 0;
    nftot = 0;
    nfmod = 0;
    if (argc < 3) { //without OPTIONS
        printf("usage: xmod [OPTIONS] MODE FILE/DIR\n");
        return 0;
    }

    struct stat a,b;

    init_clock();

    if (getpid() == getpgrp())
        init_file(envp);
    else init_file_children(envp);

    mke_register_wout_signal(PROC_CREAT,  getpid(), envp, argv, argc, a, b);

    getFichDir(argv[argc-1]);

    pid = getpid();
    
    signal(SIGHUP, sigHandlerDefault);
    signal(SIGQUIT, sigHandlerDefault);
    signal(SIGUSR1, sigHandlerDefault);
    signal(SIGSEGV, sigHandlerDefault);
    signal(SIGUSR2, sigHandlerDefault);
    signal(SIGPIPE, sigHandlerDefault);
    signal(SIGALRM, sigHandlerDefault);
    signal(SIGCHLD, sigHandlerDefault);

    signal(SIGINT, sigHandler);

    signal_sent = true;
    current_pid = getpid();

    if (!checkR(argc,argv))
        exit_c = processSingle(argc, argv, envp);
    else exit_c = processR(argc, argv, envp);

    mke_register_w_signal(PROC_EXIT,  getpid(),0, exit_c);

    return exit_c;
}

//#define S_IRWXU 0000700 // RWX mask for owner 
//#define S_IRUSR 0000400 // R for owner 
//#define S_IWUSR 0000200 // W for owner 
//#define S_IXUSR 0000100 // X for owner 

//#define S_IRWXG 0000070 // RWX mask for group 
//#define S_IRGRP 0000040 // R for group 
//#define S_IWGRP 0000020 // W for group 
//#define S_IXGRP 0000010 // X for group 

//#define S_IRWXO 0000007 // RWX mask for other 
//#define S_IROTH 0000004 // R for other 
//#define S_IWOTH 0000002 // W for other 
//#define S_IXOTH 0000001 // X for other 

//#define S_ISUID 0004000 // set user id on execution 
//#define S_ISGID 0002000 // set group id on execution 
//#define S_ISVTX 0001000 // save swapped text even after use 
