 #include "process.h"

extern int current_pid, nftot, nfmod;
extern bool signal_sent;
extern pid_t pid;
extern char **environ;

int processSingle(int argc, char* argv[], char* envp[]){
    struct stat after_buf,before_buf;

    lstat(argv[argc - 1], &before_buf);

    if (argv[argc-2][0] == '0') after_buf = processOCTALMODE(argc,argv);
    else after_buf = processMODE(argc,argv);

    if (after_buf.st_mode == -1){
        printf("ERROR: can't change permissions");
        return 1;
    }

    

    if (!changePermissions(argv[argc-1],after_buf)) 
        printf("Can't change Permissions!");

    lstat(argv[argc - 1], &after_buf);

    nftot++;

    if (after_buf.st_mode != before_buf.st_mode)
        nfmod++;

    processOPTIONSvc(before_buf,after_buf,argc,argv);

    mke_register_wout_signal(FILE_MODF,  getpid(), envp, argv, argc, after_buf,before_buf);

    return 0;
}


int processR(int argc, char* argv[], char* envp[]) {
    DIR *dir;
    struct dirent* direntp;
    struct stat stat_buf;
    int status;
    struct stat;

    processSingle(argc,argv,envp);

    if ((dir = opendir(argv[argc - 1])) == NULL)
        return 0;

    if (argv[argc - 1][strlen(argv[argc - 1]) - 1] != '/') {
        argv[argc - 1][strlen(argv[argc - 1]) + 1] = '\0';
        argv[argc - 1][strlen(argv[argc - 1])] = '/';
    }

     while((direntp = readdir(dir)) != NULL) {

        if (!strcmp(direntp->d_name, "..")) continue;
        if (!strcmp(direntp->d_name, ".")) continue;
        for (int i = strlen(argv[argc - 1]) - 1; i > 0; i--) {
            if (argv[argc - 1][i] == '/')
                break;
            argv[argc - 1][i] = '\0';
        }

        strcat(argv[argc - 1], direntp->d_name);
        if (lstat(argv[argc - 1], &stat_buf) != 0) {
            printf("%s\n", argv[argc - 1]);
            perror("ERROR"); //a)
        }


        if (S_ISLNK(stat_buf.st_mode)) {
            if (checkV(argc,argv))
                printf("neither symbolic link %s nor referent has been changed\n", argv[argc - 1]);
        }

        else if (!S_ISDIR(stat_buf.st_mode)) {
            processSingle(argc, argv, envp);
        }

        else if (S_ISDIR(stat_buf.st_mode)) {

            int id = fork();
            
            if (id == 0 && strcmp(direntp->d_name, ".") != 0) {
                execve(argv[0], argv, environ);
                mke_register_w_signal(PROC_EXIT,  getpid(),0, 0);
                exit(0);
            }
            else if (id == 0 && strcmp(direntp->d_name, ".") == 0) {
                processSingle(argc, argv, envp);
            }
            else waitpid(id,&status,0);
        }

    }

    if (getpid() == pid && closedir(dir) < 0)
        perror("ERROR");

    return 0;
}