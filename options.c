#include "options.h"

/*
mode of 'fileForTests' retained as 0444 (r--r--r--)
mode of 'fileForTests' changed from 0444 (r--r--r--) to 0755 (rwxr-xr-x)
*/

extern unsigned nfmod, nftot;

void processOPTIONSvc(struct stat before, struct stat after, int argc, char *argv[])
{
    bool checkV = false, checkC = false;
    for (int i = 0; i < argc; i++)
    {
        if (!strcmp(argv[i], "-v"))
            checkV = true;
        if (!strcmp(argv[i], "-c"))
            checkC = true;
    }
    if (checkV)
    {
        if (after.st_mode == before.st_mode)
        {
            printf("mode of '%s' retained as %s (", argv[argc - 1], argv[argc - 2]);
            printPermissions(after);
            printf(")\n");
            nftot++;
        }
        else
        {
            printf("mode of '%s' changed from 0%d (", argv[argc - 1], convertDecimalToOctal(before.st_mode) % 1000);
            printPermissions(before);
            printf(") to %s (", argv[argc - 2]);
            printPermissions(after);
            printf(")\n");
            nfmod++;
            nftot++;
        }
        return;
    }
    if (checkC)
    {
        if (after.st_mode != before.st_mode)
        {
            printf("mode of '%s' changed from 0%d (", argv[argc - 1], convertDecimalToOctal(before.st_mode) % 1000);
            printPermissions(before);
            printf(") to %s (", argv[argc - 2]);
            printPermissions(after);
            printf(")\n");
            nfmod++;
            nftot++;
        }
    }
}

void printPermissions(struct stat fileStat)
{
    printf((S_ISDIR(fileStat.st_mode)) ? "d" : "-");
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

bool checkR(int argc, char *argv[])
{
    for (int i = 0; i < argc; i++)
        if (!strcmp(argv[i], "-R"))
            return true;
    return false;
}