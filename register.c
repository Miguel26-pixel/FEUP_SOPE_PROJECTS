#include "register.h"

extern unsigned nfmod;
extern int current_pid;

void env_path(char *envp[]){
    char *file_name = {"LOG_FILENAME"};
    memset(file,0,strlen(file));
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
            sprintf(file+strlen(file), "%c", envp[i][j]);
        if (envp[i][j] == '=')
            fake = true;
    }
}

void init_file(char *envp[]) {
    memset(file,0,strlen(file));
    env_path(envp);
    int of = open(file,O_CREAT|O_RDWR|O_TRUNC,0777);
    if (of == -1){ 
        perror("ERROR: ");
        return;
    }
    close(of);
}



void mke_register_wout_signal(enum event event,  pid_t pid, char *envp[], char* argv[], int argc, struct stat after_buf,struct stat before_buf)
{
    char buffer[1024]; 
    memset(buffer,0,strlen(buffer));
    int of = open(file,O_CREAT|O_RDWR|O_APPEND,0777);
    if (of == -1){ 
        perror("ERROR: ");
        return;
    }
    switch(event){
        case PROC_CREAT:
            mid = times(buf);
            sprintf(buffer, "%4.5f sec; ", (double)(mid-start)/ticks);
            sprintf(buffer+strlen(buffer), "%d; ", pid);
            sprintf(buffer+strlen(buffer), "PROC_CREAT; ");
            sprintf(buffer+strlen(buffer), "argumentos da linha de comandos que origina o processo;\n");
            write(of, buffer, strlen(buffer));
            break;
        case PROC_EXIT:
            mid = times(buf);
            sprintf(buffer, "%4.5f sec; ", (double)(mid-start)/ticks);
            sprintf(buffer+strlen(buffer), "%d; ", pid);
            sprintf(buffer+strlen(buffer), "PROC_EXIT; ");
            sprintf(buffer+strlen(buffer), "código de saída do processo\n");
            write(of, buffer, strlen(buffer));
            break;
        case FILE_MODF:
            mid = times(buf);
            sprintf(buffer, "%4.5f sec; ", (double)(mid-start)/ticks);
            sprintf(buffer+strlen(buffer), "%d; ", pid);
            sprintf(buffer+strlen(buffer), "FILE_MODF; ");
            sprintf(buffer+strlen(buffer), "%s : ", argv[argc-1]);
            sprintf(buffer+strlen(buffer), "0%d : ", convertDecimalToOctal(before_buf.st_mode)%1000);
            sprintf(buffer+strlen(buffer), "0%d;\n", convertDecimalToOctal(after_buf.st_mode)%1000);
            write(of, buffer, strlen(buffer));
            nfmod++;
            break;
    }
    close(of);
}

void mke_register_w_signal(enum event event,  pid_t pid, int signo)
{
    char buffer[1024]; 
    memset(buffer,0,strlen(buffer));
    int of = open(file,O_CREAT|O_RDWR|O_APPEND,0777);
    if (of == -1){ 
        perror("ERROR: ");
        return;
    }
    switch(event){
        case SIGNAL_RECV:
            mid = times(buf);
            sprintf(buffer, "%4.5f sec; ", (double)(mid-start)/ticks);
            sprintf(buffer+strlen(buffer), "%d; ", pid);
            sprintf(buffer+strlen(buffer), "PROC_EXIT; ");
            sprintf(buffer+strlen(buffer), "%d", signo);
            write(of, buffer, strlen(buffer));
            break;
        case SIGNAL_SENT:
            mid = times(buf);
            sprintf(buffer, "%4.5f sec; ", (double)(mid-start)/ticks);
            sprintf(buffer+strlen(buffer), "%d; ", pid);
            sprintf(buffer+strlen(buffer), "PROC_EXIT; ");
            sprintf(buffer+strlen(buffer), "%d :", signo);
            sprintf(buffer+strlen(buffer), "%d", current_pid);
            write(of, buffer, strlen(buffer));
            break;
    }
    close(of);
}
