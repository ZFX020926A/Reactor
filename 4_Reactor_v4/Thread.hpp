#ifndef __THREAD_H__
#define __THREAD_H__

#include "pthread.h"

class Thread {
public:
    Thread();
    ~Thread();
    void Strart();
    void Stop();

private:
    static void * doTask(void *);
    virtual void run() = 0;

private:
    pthread_t _pthreadid;
    bool      _isRuning;
};


#endif // !THREAD_H

