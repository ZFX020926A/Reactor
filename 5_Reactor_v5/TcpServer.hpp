#ifndef __TCPSERVER_H__

#define __TCPSERVER_H__

#include "EventLoop.hpp"
#include "Acceptor.hpp"

#include <string>
using std::string;

class TcpServer
{
private:
    Acceptor _acc;
    EventLoop _eventloop;
public:
    TcpServer(string ip, unsigned short port)
    : _acc(ip, port)
    , _eventloop(_acc)
    {
        _acc.setready();
    }

    ~TcpServer()
    {

    }

    void Strart()
    {
        _eventloop.loop();
    }

    void Stop()
    {
        _eventloop.unloop();
    }

    void setCallback(TcpConnectionCallback cb1, 
                     TcpConnectionCallback cb2, 
                     TcpConnectionCallback cb3)
        {
            _eventloop.setcallback(cb1, cb2, cb3);
        } 

};

#endif // !__TCPSERVER_H__