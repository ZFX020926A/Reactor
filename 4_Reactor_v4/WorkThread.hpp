#ifndef __WORKTHREAD_H__
#define __WORKTHREAD_H__

#include "Thread.hpp"
#include "ThreadPool.hpp"

class WorkThread
:public Thread
{
public:
    WorkThread(ThreadPool &tp)
    :_threadpool(tp)
    {

    }
private:

    void run() override
    {
        // 调用Threadpool中的dotask任务
        _threadpool.dotask();
    }
public:
    ThreadPool &_threadpool;
    



};

#endif // !__WORKTHREAD_H__

