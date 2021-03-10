 #include "process.h"

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

    processOPTIONSvc(before_buf,after_buf,argc,argv);

    mke_register(FILE_MODF,  getpid(), envp, argv, argc, after_buf,before_buf);

    mke_register(PROC_EXIT,  getpid(), envp, argv, argc, after_buf,before_buf);

    return 0;
 }


int processR(int argc, char* argv[], char* envp[]) {
    printf("ENTREI R\n");

    DIR *dir;
    char* path = argv[argc - 1];
    struct dirent* direntp;
    struct stat stat_buf;
    int status;

    if ((dir = opendir(argv[argc - 1])) == NULL) {
         perror("ERROR1");
         return 1;
    }

    while((direntp = readdir(dir)) != NULL) {
        //if (!strcmp(direntp->d_name, "..")) continue;
        for (int i = strlen(argv[argc - 1]) - 1; i > 0; i--) {
            if (argv[argc - 1][i] == '/')
                break;
            argv[argc - 1][i] = '\0';
        }
        strcat(argv[argc - 1], direntp->d_name);
        lstat(argv[argc - 1], &stat_buf); 
        printf("file: %s - st_mode = %d\n",direntp->d_name, stat_buf.st_mode);
        if (!S_ISDIR(stat_buf.st_mode))
            processSingle(argc, argv, envp);
    }
    if (closedir(dir) < 0)
        perror("ERROR2");

    argv[argc - 1] = path;

    if ((dir = opendir(argv[argc - 1])) == NULL) {
         perror("ERROR3");
         return 1;
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
        lstat(argv[argc - 1], &stat_buf); 
        if (S_ISDIR(stat_buf.st_mode)) {
            int id = fork();
            if (id == 0 && strcmp(direntp->d_name, ".") != 0) {
                


                char** new_argv = malloc((argc+1) * sizeof *new_argv);
                for(int i = 0; i < argc; ++i)
                {
                    size_t length = strlen(argv[i])+1;
                    new_argv[i] = malloc(length);
                    memcpy(new_argv[i], argv[i], length);
                }
                new_argv[argc] = NULL;


                strcat(new_argv[argc - 1], "/");
                processR(argc, new_argv, envp);
            }
            else waitpid(id,&status,0);
        }
    }
    return 0;
}