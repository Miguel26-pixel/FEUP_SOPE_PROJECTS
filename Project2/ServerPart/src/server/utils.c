#include "utils.h"

extern clock_t start, end;
extern struct tms t;

void init_clock(){
    start = times(&t);
    srand(time(0));
}

bool check_time(int argc, char* argv[]) {
    int index = (argc == 4) ? 2 : 4;
    char* ptr;
    int long ticks = sysconf(_SC_CLK_TCK);
    end = times(&t);
    if (strtod(argv[argc - index], &ptr) <= (double)(end - start) / ticks) return false;
    return true;
}

time_t get_remaining_time_secs(char * argv[]) {
    time_t remaining;
    char* ptr;
    int long ticks = sysconf(_SC_CLK_TCK);
    end = times(&t);
    remaining = strtod(argv[2], &ptr) - (double)(end - start) / ticks;
    return remaining;
}

suseconds_t get_remaining_time_micro(char * argv[]) {
    suseconds_t remaining;
    char* ptr;
    int long ticks = sysconf(_SC_CLK_TCK);
    end = times(&t);
    remaining = (strtod(argv[2], &ptr) - (double)(end - start) / ticks)*10e5;
    return remaining;
}