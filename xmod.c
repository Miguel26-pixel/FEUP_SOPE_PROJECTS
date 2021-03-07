#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h> //int chmod(const char *pathname, mode_t mode);
#include <dirent.h>
#include <string.h>
#include <stdbool.h>
#include "permissions.h"
#include "options.h"

int oct(mode_t num) {
    int i;
    char buffer[7], buffer2[4];
    snprintf(buffer, 8, "%o", num);
    for(i = 0; i < strlen(buffer2); i++)
        buffer2[i] = buffer[i + 2];
    return strtol(buffer2, NULL, 10);
}

int main(int argc, char* argv[], char* envp[]) {
    if (argc < 3) { //without OPTIONS
        printf("usage: xmod [OPTIONS] MODE FILE/DIR\n");
        return 0;
    }

    struct stat after_buf,before_buf;

    lstat(argv[argc - 1], &before_buf);

    if (argv[argc-2][0] == '0') after_buf = processOCTALMODE(argc,argv);
    else after_buf = processMODE(argc,argv);

    if (after_buf.st_mode == -1){
        printf("ERROR: can't change permissions");
        return 1;
    }

    

    
    if (changePermissions(argv[argc-1],after_buf)) 
        printf("Succeed");
    else printf("Can't change Permissions!");

    lstat(argv[argc - 1], &after_buf);

    processOPTIONSvc(before_buf,after_buf,argc,argv);

    printf("before: %d ; after: %d ;\n",before_buf.st_mode, after_buf.st_mode);

    if (before_buf.st_mode == after_buf.st_mode)
        printf("Nothing was changed\n");

    return 0;
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
