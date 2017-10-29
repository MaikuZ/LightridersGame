#include "Timer.h"

void Timer::startTimer()
{
    gettimeofday(&start, nullptr);
}
long long int Timer::endTimer()
{
    gettimeofday(&end, nullptr);
    return (long long int)(end.tv_sec-start.tv_sec)*1000 + (long long int)(end.tv_usec-start.tv_usec)/1000;
}
