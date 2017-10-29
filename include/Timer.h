#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED
#include <sys/time.h>
class Timer
{
    struct timeval start, end;
public:
    void startTimer();
    long long int endTimer();
};


#endif // TIMER_H_INCLUDED
