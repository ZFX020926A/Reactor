#ifndef __ECHOSERVER_H__
#define __ECHOSERVER_H__

#include "ThreadPool.hpp"
#include "TcpServer.hpp"
#include "TcpConnection.hpp"

class EchoServer
{
private:
    ThreadPool _threadpool;
    TcpServer _tcpserver;
public:
    EchoServer(int poolnums, int tasknums, const string ip, unsigned short port);
    ~EchoServer();
    void Strart();
    void onConnection(TcpConnectionfd);
    void onMessage(TcpConnectionfd);
    void onClose(TcpConnectionfd);
};


#endif // !__ECHOSERVER_H__
