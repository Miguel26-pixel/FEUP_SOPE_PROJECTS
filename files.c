 #include "files.h"

int processSingle(int argc, char* argv[], char* envp[]){
    struct stat after_buf,before_buf;
    init_file(envp);

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

    processOPTIONSvc(before_buf,after_buf,argc,argv);

    mke_register(FILE_MODF,  getpid(), envp, argv, argc, after_buf,before_buf);

    mke_register(PROC_EXIT,  getpid(), envp, argv, argc, after_buf,before_buf);

    return 0;
 }


int processR(int argc, char* argv[], char* envp[]) {
    DIR *dir;
    char* path = argv[argc - 1];
    struct dirent* direntp;

    if ((dir = opendir(argv[argc - 1])) == NULL) {
         perror("ERROR");
         return 1;
    }

    while((direntp = readdir(dir)) != NULL) {
        if (!strcmp(direntp->d_name, "..")) continue;
        for (int i = strlen(argv[argc - 1]) - 1; i > 0; i--) {
            if (argv[argc - 1][i] == '/')
                break;
            argv[argc - 1][i] = '\0';
        }
        strcat(argv[argc - 1], direntp->d_name);
        //printf("%s\n", argv[argc - 1]);
        processSingle(argc, argv, envp);
    }
    return 0;
}