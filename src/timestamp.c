#include "../include/timestamp.h"
#include <time.h>

void getCurrentTimestamp(char *buffer, int bufferSize) {
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, bufferSize, "[%Y-%m-%d %H:%M:%S]", timeinfo);
}
