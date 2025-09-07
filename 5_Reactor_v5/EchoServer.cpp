#include "EchoServer.hpp"
#include "Mytask.hpp"
#include "ThreadPool.hpp"

#include <iostream>

using std::cout;
using std::endl;

EchoServer::EchoServer(int poolnums, int tasknums, const string ip, unsigned short port)
: _threadpool(poolnums, tasknums)
, _tcpserver(ip, port)
{
    _tcpserver.setCallback(
        std::bind(&EchoServer::onConnection, this, std::placeholders::_1),
        std::bind(&EchoServer::onMessage, this, std::placeholders::_1),
        std::bind(&EchoServer::onClose, this, std::placeholders::_1)
    );
}

EchoServer::~EchoServer()
{
}

void EchoServer::Strart()
{
    _threadpool.Strart();
    _tcpserver.Strart();
}

void EchoServer::onConnection(TcpConnectionfd conn)
{
    cout << "有新连接上来了" << conn << endl;
}

void EchoServer::onMessage(TcpConnectionfd conn)
{
    string msg = conn->recvmsg();
    cout << "有新消息到来了 : " << msg << endl;

    Mytask mytask(msg, conn);
    _threadpool.addtask(std::bind(&Mytask::process, mytask));
}

void EchoServer::onClose(TcpConnectionfd conn)
{
    cout << "连接断开了" << conn << endl;
}


