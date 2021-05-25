#include "options.h"

/*
mode of 'fileForTests' retained as 0444 (r--r--r--)
mode of 'fileForTests' changed from 0444 (r--r--r--) to 0755 (rwxr-xr-x)
*/

extern unsigned nfmod, nftot;

void processOPTIONSvc(struct stat before, struct stat after, int argc, char *argv[]) {
    if (checkV(argc,argv))
    {
        if (after.st_mode == before.st_mode)
        {
            printf("mode of '%s' retained as 0%d (", argv[argc - 1], convertDecimalToOctal(after.st_mode) % 1000);
            printPermissions(after);
            printf(")\n");
        }
        else
        {
            printf("mode of '%s' changed from 0%d (", argv[argc - 1], convertDecimalToOctal(before.st_mode) % 1000);
            printPermissions(before);
            printf(") to 0%d (", convertDecimalToOctal(after.st_mode) % 1000);
            printPermissions(after);
            printf(")\n");
        }
        return;
    }
    if (checkC(argc,argv))
    {
        if (after.st_mode != before.st_mode)
        {
            printf("mode of '%s' changed from 0%d (", argv[argc - 1], convertDecimalToOctal(before.st_mode) % 1000);
            printPermissions(before);
            printf(") to 0%d (", convertDecimalToOctal(after.st_mode) % 1000);
            printPermissions(after);
            printf(")\n");
        }
    }
}

void printPermissions(struct stat fileStat) {
    printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
    printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
    printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
    printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
    printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
    printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
    printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
    printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
    printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");
}

bool checkR(int argc, char *argv[]) {
    for (int i = 0; i < argc; i++) {
        if (argv[i][0] == '-')
            for (int j = 0; j < strlen(argv[i]); j++)
                if (argv[i][j] == 'R')
                    return true;
    }
    return false;
}

bool checkV(int argc, char *argv[]) {
    for (int i = 0; i < argc; i++) {
        if (argv[i][0] == '-')
            for (int j = 0; j < strlen(argv[i]); j++)
                if (argv[i][j] == 'v')
                    return true;
    }
    return false;
}

bool checkC(int argc, char *argv[]) {
    for (int i = 0; i < argc; i++) {
        if (argv[i][0] == '-')
            for (int j = 0; j < strlen(argv[i]); j++)
                if (argv[i][j] == 'c')
                    return true;
    }
    return false;
}