#include "TcpConnection.hpp"

#include <iostream>

using std::cout;
using std::endl;

TcpConnection::TcpConnection(int fd)
: _sockfd(fd)
, _socketio(fd)
, _localaddr(getlocaladdr())
, _peeraddr(getpeeraddr())
{
}

TcpConnection::~TcpConnection()
{
}

void TcpConnection::sendmsg(const string &msg)
{
    int ret = _socketio.writen(msg.data(), msg.size()); // ret为发送成功得字节数
    cout << "发送 " << ret << "个数据" << endl;
}

string TcpConnection::recvmsg()
{
    char buff[65535] = {0};
    int ret = _socketio.readline(buff, sizeof(buff));

    return string(buff, ret);
}

bool TcpConnection::isclose()
{
    char buff[20] = {0};
    int ret = _socketio.recvpeek(buff, sizeof(buff));

    return 0 == ret;
}

InetAddress TcpConnection::getlocaladdr()
{
    struct sockaddr_in sockaddrin;
    memset(&sockaddrin, 0, sizeof(sockaddrin));
    socklen_t len = sizeof(sockaddrin);
    int ret = getsockname(_sockfd.getsockfd(), (struct sockaddr *)&sockaddrin, &len);
    if(ret < 0)
    {
        perror("getsockname");
    }
    return InetAddress(sockaddrin);
}

InetAddress TcpConnection::getpeeraddr()
{
    struct sockaddr_in sockaddrin;
    memset(&sockaddrin, 0, sizeof(sockaddrin));
    socklen_t len = sizeof(sockaddrin);
    int ret = getpeername(_sockfd.getsockfd(), (struct sockaddr *)&sockaddrin, &len);
    if(ret < 0)
    {
        perror("getpeername");
    }
    return InetAddress(sockaddrin);
}

void TcpConnection::setcallback(TcpConnectionCallback cb1,
                                TcpConnectionCallback cb2,
                                TcpConnectionCallback cb3)
    {
        _onconnection = cb1;
        _onmessage = cb2;
        _onclose = cb3;
    }

void TcpConnection::handlenewconnectionCallback()
{
    if(_onconnection)
    {
        _onconnection(shared_from_this());
    }

}

void TcpConnection::handlemessageCallback()
{
    if(_onmessage)
    {
        _onmessage(shared_from_this());
    }

}

void TcpConnection::handlecloseCallback()
{
    if(_onclose)
    {
        _onclose(shared_from_this());
    }

}