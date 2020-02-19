#include <time.h>
#include <errno.h>
#include <unistd.h>

/**
* Helper function to sleep for a given microsecond time
*/
int msleep(long msec)
{
    struct timespec ts;
    int res;

    // if time is negative, dont do anything
    if (msec < 0)
    {
        errno = EINVAL;
        return -1;
    }

    ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec % 1000) * 1000000;

    do {
        res = nanosleep(&ts, &ts);
    } while (res && errno == EINTR);

    return res;
}