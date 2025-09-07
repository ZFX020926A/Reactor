#include "ThreadPool.hpp"
#include "TaskQueue.hpp"
#include "WorkThread.hpp"

ThreadPool::ThreadPool(size_t poolnums, size_t tasknums)
:_vecpthreads()
,_sizepool(poolnums)
,_taskq(tasknums)
,_isexit(false)
{
    _vecpthreads.reserve(_sizepool);
}

void ThreadPool::Strart()
{
    // 线程池启动函数 创建线程
    for(size_t i = 0; i < _sizepool; ++i)
    {
        // 创建任务线程
        unique_ptr<Thread> upT(new WorkThread(*this));
        _vecpthreads.push_back(std::move(upT));
    }

    for(auto & subThread : _vecpthreads)
    {
        // 调用Thread 中的Start函数 开始运行 线程
        subThread->Strart();
    }

}

void ThreadPool::Stop()
{
    while(!_taskq.empty())
    {
        // 走到这里标识 线程吃中还有任务需要执行
    }

    // 修改线程池退出的标志位
    _isexit = true;
    for(auto & _subthread : _vecpthreads)
    {
        // 调用Thread中的Stop函数停止运行
        _subthread->Stop(); 
    }
}

void ThreadPool::addtask(Task *tk)
{
    if(tk)
    {
        _taskq.push(tk);
    }
}

void ThreadPool::dotask()
{
    // isexit = true 表示已经没有需要执行的任务了
    while(!_isexit)
    {
        Task * ts = _taskq.pop();
        if(ts)
        {
            ts->process();
        }

    }
}



