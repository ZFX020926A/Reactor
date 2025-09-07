#include "Thread.hpp"

#include <iostream>

using std::cout;
using std::endl;



Thread::Thread()
:_pthreadid(0)
, _isRuning(false)
{

}

Thread::~Thread()
{

}

void Thread::Strart()
{
    if(!_isRuning)
    {
        int ret = pthread_create(&_pthreadid, NULL, doTask, this);
        if(ret != 0)
        {
            cout << "创建错误" << endl;
        }

        _isRuning = true;
    }
}

void *Thread::doTask(void *arg)
{
    Thread *pthid = static_cast<Thread *>(arg);
    if(pthid)
    {
        pthid->run();
    }
    return NULL;
}

void Thread::Stop()
{
    if(_isRuning)
    {
        pthread_join(_pthreadid, NULL);
        _isRuning = false;
    }
}

