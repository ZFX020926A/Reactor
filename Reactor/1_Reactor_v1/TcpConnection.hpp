#ifndef __TCPCONNECTION_H__
#define __TCPCONNECTION_H__

#include "Socket.hpp"
#include "SockIO.hpp"
#include "InetAddress.hpp"


class TcpConnection
{

public:
    TcpConnection(int fd);
    ~TcpConnection();
    void sendmsg(const string &msg);
    string recvmsg();
    bool isclose();
private:
    InetAddress getlocaladdr();
    InetAddress getpeeraddr();
private:
    Socket _sockfd;
    SockIO _socketio;
    InetAddress _localaddr;
    InetAddress _peeraddr;
};


#endif // !__TCPCONNECTION_H__