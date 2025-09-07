#ifndef __EVENTLOOP_H__

#include "Acceptor.hpp"
#include "TcpConnection.hpp"
#include "MutexLock.hpp"

#include <map>
#include <vector>
#include <functional>

using std::map;
using std::vector;

using Functor = std::function<void()>;

class EventLoop
{
private:
    int _epollfd;
    Acceptor &_accfd;
    bool _islooping;
    map<int, TcpConnectionfd> _conns;

    vector<struct epoll_event> _veceventarr;

    TcpConnectionCallback _onconnection;
    TcpConnectionCallback _onmessage;
    TcpConnectionCallback _onclose;

    // v4
    int _eventfd; // 进程间通信的文件描述符
    vector<Functor> _pendingFunctors; // 用来存储待执行的回调函数 
    MutexLock _mutex; // 对_pendingFunctors的互斥锁
public:
    EventLoop(Acceptor &acc);
    ~EventLoop();
    void loop();
    void unloop();
    void setcallback(TcpConnectionCallback cb1, 
                     TcpConnectionCallback cb2, 
                     TcpConnectionCallback cb3);
    
    // v4
    void runinLoop(Functor &&); // 用来执行待执行的回调函数
private:
    int createpollfd();
    void addepollevent(int);
    void delepollevent(int);
    void epollwaitevent();
    void handlenewconnection();
    void handlemessage(int fd);
    
    // v4
    void handlereadevent(); // 处理事件fd上的可读事件
    void wakeup(); // 计算事件执行完毕 ，用来唤醒I/O事件
    void doPendingFunctors(); // 执行回调函数
    int createEventfd(); //创建eventfd
};


#endif // !__EVENTLOOP_H__
