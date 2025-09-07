#ifndef __EVENTLOOP_H__

#include "Acceptor.hpp"
#include "TcpConnection.hpp"

#include <map>
#include <vector>

using std::map;
using std::vector;

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
public:
    EventLoop(Acceptor &acc);
    ~EventLoop();
    void loop();
    void unloop();
    void setcallback(TcpConnectionCallback cb1, 
                     TcpConnectionCallback cb2, 
                     TcpConnectionCallback cb3);
private:
    int createpollfd();
    void addepollevent(int);
    void delepollevent(int);
    void epollwaitevent();
    void handlenewconnection();
    void handlemessage(int fd);
};




#endif // !__EVENTLOOP_H__
