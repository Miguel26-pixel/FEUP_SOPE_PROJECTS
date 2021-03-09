#include "register.h"


char* env_path(char *envp[]){
    char *file_name = {"LOG_FILENAME"};
    int i = 0;
    while (envp[i]!=NULL)
    {
        bool fake = true;
        for(int x = 0; x<strlen(file_name);x++){
            if(file_name[x]!=envp[i][x])
                fake = false;
        }
        if(fake){
            return envp[i];
        }
        i++;
    }
    return file_name;
}



void mke_register(enum event event,  pid_t pid, char *envp[], char* argv[], int argc, struct stat after_buf,struct stat before_buf)
{
    char buffer[1024]; 
    memset(buffer,0,strlen(buffer));
    int of = open(env_path(envp),O_CREAT|O_WRONLY|O_TRUNC, 0700);
    printf("td ok \n");
    if(of==-1)return;
    switch(event){
        case PROC_CREAT:
            mid = times(buf);
            sprintf(buffer, "%4.2f; ", (double)buf->tms_utime/ticks);
            sprintf(buffer, "%d; ", pid);
            sprintf(buffer, "PROC_CREAT; ");
            sprintf(buffer, "argumentos da linha de comandos que origina o processo;");
            write(of, buffer, strlen(buffer));
            break;
        case PROC_EXIT:
            mid = times(buf);
            sprintf(buffer, "%4.2f s; ", (double)buf->tms_utime/ticks);
            printf("td ok \n");
            sprintf(buffer, "%d; ", pid);
            sprintf(buffer, "PROC_EXIT; ");
            sprintf(buffer, "código de saída do processo");
            write(of, buffer, strlen(buffer));
            break;
        case FILE_MODF:
            mid = times(buf);
            sprintf(buffer, "%4.2f s; ", (double)buf->tms_utime/ticks);
            sprintf(buffer, "%d; ", pid);
            sprintf(buffer, "FILE_MODF; ");
            sprintf(buffer, "%s : ", argv[argc-1]);
            sprintf(buffer, "%d : ", convertDecimalToOctal(before_buf.st_mode)%1000);
            sprintf(buffer, "%d : ", convertDecimalToOctal(after_buf.st_mode)%1000);
            write(of, buffer, strlen(buffer));
            break;
    }
}