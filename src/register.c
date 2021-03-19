#include "register.h"
char file[1024];

extern int current_pid;
char file1[1024];


void env_path(char *envp[]){
    char *file_name = {"LOG_FILENAME"};
    memset(file1,0,strlen(file1));
    int i = 0;
    bool fake = true;
    while (envp[i]!=NULL)
    {
        fake = true;
        for(int x = 0; x<strlen(file_name);x++){
            if(file_name[x]!=envp[i][x])
                fake = false;
        }
        if(fake){
            break;
        }
        i++;
    }
    if (fake == false) {
        printf("LOG_FILENAME doesn't exist.\n");
        exit(1);
    }
    fake = false;
    for (int j = 0; j < strlen(envp[i]); j++) {
        if (fake)
            sprintf(file1+strlen(file1), "%c", envp[i][j]);
        if (envp[i][j] == '=')
            fake = true;
    }
}

void init_file(char *envp[]) {
    memset(file1,0,strlen(file1));
    env_path(envp);
    int of = open(file1,O_CREAT|O_RDWR|O_TRUNC,0777);
    if (of == -1){ 
        perror("ERROR"); 
        return;
    }
    close(of);
}

void init_file_children(char *envp[]) {
    memset(file1,0,strlen(file1));
    env_path(envp);
    int of = open(file1,O_CREAT|O_RDWR,0777);
    if (of == -1){ 
        perror("ERROR"); 
        return;
    }
    close(of);
}

void mke_register_wout_signal(enum event event,  pid_t pid, char *envp[], char* argv[], int argc, struct stat after_buf,struct stat before_buf) {
    char buffer[1024]; 
    char*ptr;
    memset(buffer,0,strlen(buffer));
    int of = open(file1,O_CREAT|O_RDWR|O_APPEND,0777);
    if (of == -1){ 
        perror("ERROR");
        return;
    }
    switch(event){
        case PROC_CREAT:
            mid = times(buf);
            sprintf(buffer, "%f ms; ", (double)(mid-strtol(getenv("START_CLOCK"),&ptr,10))/ticks*10*10*10);
            sprintf(buffer+strlen(buffer), "%d; ", pid);
            sprintf(buffer+strlen(buffer), "PROC_CREAT; ");
            for(int i = 0;i < argc ; i++){
                sprintf(buffer+strlen(buffer), "%s;", argv[i]);
            }
            sprintf(buffer+strlen(buffer), "\n");
            write(of, buffer, strlen(buffer));
            break;
        case FILE_MODF:
            mid = times(buf);
            sprintf(buffer, "%4.5f ms; ", (double)(mid-strtol(getenv("START_CLOCK"),&ptr,10))/ticks*10*10*10);
            sprintf(buffer+strlen(buffer), "%d; ", pid);
            sprintf(buffer+strlen(buffer), "FILE_MODF; ");
            sprintf(buffer+strlen(buffer), "%s : ", argv[argc-1]);
            sprintf(buffer+strlen(buffer), "0%d : ", convertDecimalToOctal(before_buf.st_mode)%1000);
            sprintf(buffer+strlen(buffer), "0%d;\n", convertDecimalToOctal(after_buf.st_mode)%1000);
            write(of, buffer, strlen(buffer));
            break;
        default: 
            break;
    }
    close(of);
}

void mke_register_w_signal(enum event event,  pid_t pid, int signo, int exit_c) {
    char buffer[1024]; 
    char *ptr;
    memset(buffer,0,strlen(buffer));
    int of = open(file1,O_CREAT|O_RDWR|O_APPEND,0777);
    if (of == -1){ 
        perror("ERROR");
        return;
    }
    switch(event){
        case PROC_EXIT:
            mid = times(buf);
            sprintf(buffer, "%4.5f ms; ", (double)(mid-strtol(getenv("START_CLOCK"),&ptr,10))/ticks*10*10*10);
            sprintf(buffer+strlen(buffer), "%d; ", pid);
            sprintf(buffer+strlen(buffer), "PROC_EXIT; ");
            sprintf(buffer+strlen(buffer), "%d\n", exit_c);
            write(of, buffer, strlen(buffer));
            break;
        case SIGNAL_RECV:
            mid = times(buf);
            sprintf(buffer, "%4.5f ms; ", (double)(mid-strtol(getenv("START_CLOCK"),&ptr,10))/ticks*10*10*10);
            sprintf(buffer+strlen(buffer), "%d; ", pid);
            sprintf(buffer+strlen(buffer), "SIGNAL_RECV; ");
            sprintf(buffer+strlen(buffer), "%d\n", signo);
            write(of, buffer, strlen(buffer));
            break;
        case SIGNAL_SENT:
            mid = times(buf);
            sprintf(buffer, "%4.5f ms; ", (double)(mid-strtol(getenv("START_CLOCK"),&ptr,10))/ticks*10*10*10);
            sprintf(buffer+strlen(buffer), "%d; ", current_pid);
            sprintf(buffer+strlen(buffer), "SIGNAL_SENT; ");
            sprintf(buffer+strlen(buffer), "%d : ", signo);
            sprintf(buffer+strlen(buffer), "%d\n", pid);
            write(of, buffer, strlen(buffer));
            break;
        default:
            break;
    }
    close(of);
}
