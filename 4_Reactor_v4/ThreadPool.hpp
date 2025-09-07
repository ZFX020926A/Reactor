#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include "Thread.hpp"
#include "TaskQueue.hpp"
#include "Task.hpp"

#include <vector>
#include <memory>

using std::vector;
using std::unique_ptr;

class ThreadPool
{
    friend class WorkThread;
public:
    ThreadPool(size_t, size_t);
    void Strart();
    void Stop();
    void addtask(Task *);
    void dotask();

private:
    vector<unique_ptr<Thread>> _vecpthreads;
    size_t                     _sizepool;
    TaskQueue                  _taskq;
    bool                       _isexit;
};




#endif // !__THREADPOOL_H__

