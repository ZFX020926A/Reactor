#ifndef __CONDITION_H__
#define __CONDITION_H__

#include "MutexLock.hpp"
#include <pthread.h>


class Condition
{
public:
    Condition(MutexLock &);
    ~Condition();
    void wait();
    void notify_one();
    void notify_all();
private:
    pthread_cond_t _cond;
    MutexLock      &_mutex;
};




#endif // !CONDITION_H

