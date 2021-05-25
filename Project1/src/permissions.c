#include "permissions.h"

struct stat processMODE(int argc, char* argv[]) {
    char user, permissions[3], operator;
    int j = 0;

    for (size_t i = 0; i < strlen(argv[argc - 2]); i++) {
        if (argv[argc - 2][i] == 'u' || argv[argc - 2][i] == 'g' || argv[argc - 2][i] == 'o' || argv[argc - 2][i] == 'a')
            user = argv[argc - 2][i];
        else if (argv[argc - 2][i] == '+' || argv[argc - 2][i] == '-' || argv[argc - 2][i] == '=') 
            operator = argv[argc - 2][i];
        else if (argv[argc - 2][i] == 'r' || argv[argc - 2][i] == 'w' || argv[argc - 2][i] == 'x') {
            permissions[j] = argv[argc - 2][i];             
            j++;
        }
        else {
            struct stat a; 
            a.st_mode = -1;
            return a;
        }
    }

    struct stat stat_buf;
    stat(argv[argc - 1], &stat_buf);


    if (operator == '=') 
        switch(user) {
            case 'a':
                stat_buf.st_mode = 0; 
                break;
            case 'o':
                stat_buf.st_mode = stat_buf.st_mode & ~S_IROTH & ~S_IWOTH & ~S_IXOTH;
                break;
            case 'u':
                stat_buf.st_mode = stat_buf.st_mode & ~S_IRUSR & ~S_IWUSR & ~S_IXUSR;
                break;
            case 'g':
                stat_buf.st_mode = stat_buf.st_mode & ~S_IRGRP & ~S_IWGRP & ~S_IXGRP;
                break;
        }

    for (int i = 0; i < 3; i++)
        switch(permissions[i]){
            case 'r':
                switch (user) {
                    case 'a':
                        if (operator == '+' || operator == '=') stat_buf.st_mode = stat_buf.st_mode | S_IRUSR | S_IRGRP | S_IROTH;
                        if (operator == '-') stat_buf.st_mode = stat_buf.st_mode & ~S_IRUSR & ~S_IRGRP & ~S_IROTH;
                        break;
                    case 'u':
                        if (operator == '+' || operator == '=') stat_buf.st_mode = stat_buf.st_mode | S_IRUSR;
                        if (operator == '-') stat_buf.st_mode = stat_buf.st_mode & ~S_IRUSR;
                        break;
                    case 'g':
                        if (operator == '+' || operator == '=') stat_buf.st_mode = stat_buf.st_mode | S_IRGRP;
                        if (operator == '-') stat_buf.st_mode = stat_buf.st_mode & ~S_IRGRP;
                        break;
                    case 'o':
                        if (operator == '+' || operator == '=') stat_buf.st_mode = stat_buf.st_mode | S_IROTH;
                        if (operator == '-') stat_buf.st_mode = stat_buf.st_mode & ~S_IROTH;
                        break;
                    default: break;
                }
                break;
            case 'w':
                switch (user) {
                    case 'a':
                        if (operator == '+' || operator == '=') stat_buf.st_mode = stat_buf.st_mode | S_IWUSR | S_IWGRP | S_IWOTH;
                        if (operator == '-') stat_buf.st_mode = stat_buf.st_mode & ~S_IWUSR & ~S_IWGRP & ~S_IWOTH;
                        break;
                    case 'u':
                        if (operator == '+' || operator == '=') stat_buf.st_mode = stat_buf.st_mode | S_IWUSR;
                        if (operator == '-') stat_buf.st_mode = stat_buf.st_mode & ~S_IWUSR;
                        break;
                    case 'g':
                        if (operator == '+' || operator == '=') stat_buf.st_mode = stat_buf.st_mode | S_IWGRP;
                        if (operator == '-') stat_buf.st_mode = stat_buf.st_mode & ~S_IWGRP;
                        break;
                    case 'o':
                        if (operator == '+' || operator == '=') stat_buf.st_mode = stat_buf.st_mode | S_IWOTH;
                        if (operator == '-') stat_buf.st_mode = stat_buf.st_mode & ~S_IWOTH;
                        break;
                    default: break;
                }
                break;
            case 'x':
                switch (user) {
                    case 'a':
                        if (operator == '+' || operator == '=') stat_buf.st_mode = stat_buf.st_mode | S_IXUSR | S_IXGRP | S_IXOTH;
                        if (operator == '-') stat_buf.st_mode = stat_buf.st_mode & ~S_IXUSR & ~S_IXGRP & ~S_IXOTH;
                        break;
                    case 'u':
                        if (operator == '+' || operator == '=') stat_buf.st_mode = stat_buf.st_mode | S_IXUSR;
                        if (operator == '-') stat_buf.st_mode = stat_buf.st_mode & ~S_IXUSR;
                        break;
                    case 'g':
                        if (operator == '+' || operator == '=') stat_buf.st_mode = stat_buf.st_mode | S_IXGRP;
                        if (operator == '-') stat_buf.st_mode = stat_buf.st_mode & ~S_IXGRP;
                        break;
                    case 'o':
                        if (operator == '+' || operator == '=') stat_buf.st_mode = stat_buf.st_mode | S_IXOTH;
                        if (operator == '-') stat_buf.st_mode = stat_buf.st_mode & ~S_IXOTH;
                        break;
                    default: 
                    break;
                }
                break;
            default: break;
        }


    return stat_buf;
}

struct stat processOCTALMODE(int argc, char* argv[]) { //U G O     //r w x

    struct stat stat_buf;
    stat(argv[argc - 1], &stat_buf);

    stat_buf.st_mode = 0;

    for (int i = 1; i < 4; i++)
        switch(argv[argc - 2][i]) {
            case '1': //001
                switch(i) {
                    case 1:
                        stat_buf.st_mode = stat_buf.st_mode | S_IXUSR;
                        break;
                    case 2:
                        stat_buf.st_mode = stat_buf.st_mode | S_IXGRP;
                        break;
                    case 3:
                        stat_buf.st_mode = stat_buf.st_mode | S_IXOTH;
                        break;
                }
                break;
            case '2': //010
                switch(i) {
                    case 1:
                        stat_buf.st_mode = stat_buf.st_mode | S_IWUSR;
                        break;
                    case 2:
                        stat_buf.st_mode = stat_buf.st_mode | S_IWGRP;
                        break;
                    case 3:
                        stat_buf.st_mode = stat_buf.st_mode | S_IWOTH;
                        break;
                }
                break;
            case '3': //011
                switch(i) {
                    case 1:
                        stat_buf.st_mode = stat_buf.st_mode | S_IXUSR | S_IWUSR;
                        break;
                    case 2:
                        stat_buf.st_mode = stat_buf.st_mode | S_IXGRP | S_IWGRP;
                        break;
                    case 3:
                        stat_buf.st_mode = stat_buf.st_mode | S_IXOTH | S_IWOTH;
                        break;
                }
                break;
            case '4': //100
                switch(i) {
                    case 1:
                        stat_buf.st_mode = stat_buf.st_mode | S_IRUSR;
                        break;
                    case 2:
                        stat_buf.st_mode = stat_buf.st_mode | S_IRGRP;
                        break;
                    case 3:
                        stat_buf.st_mode = stat_buf.st_mode | S_IROTH;
                        break;
                }
                break;
            case '5': //101
                switch(i) {
                    case 1:
                        stat_buf.st_mode = stat_buf.st_mode | S_IRUSR | S_IXUSR;;
                        break;
                    case 2:
                        stat_buf.st_mode = stat_buf.st_mode | S_IRGRP | S_IXGRP;;
                        break;
                    case 3:
                        stat_buf.st_mode = stat_buf.st_mode | S_IROTH | S_IXOTH;;
                        break;
                }
                break;
            case '6': //110
                switch(i) {
                    case 1:
                        stat_buf.st_mode = stat_buf.st_mode | S_IRUSR | S_IWUSR;
                        break;
                    case 2:
                        stat_buf.st_mode = stat_buf.st_mode | S_IRGRP | S_IWGRP;
                        break;
                    case 3:
                        stat_buf.st_mode = stat_buf.st_mode | S_IROTH | S_IWOTH;
                        break;
                }
                break;
            case '7': //111
                switch(i) {
                    case 1:
                        stat_buf.st_mode = stat_buf.st_mode | S_IRUSR | S_IXUSR | S_IWUSR;
                        break;
                    case 2:
                        stat_buf.st_mode = stat_buf.st_mode | S_IRGRP | S_IXGRP | S_IWGRP;
                        break;
                    case 3:
                        stat_buf.st_mode = stat_buf.st_mode | S_IROTH | S_IXOTH | S_IWOTH;
                        break;
                }
                break;
            default: 
                stat_buf.st_mode = -1;
                return stat_buf;
        }
    return stat_buf;
}

bool changePermissions(char *dir, struct stat stat_buf) {
    return !(chmod(dir, stat_buf.st_mode) < 0);
}