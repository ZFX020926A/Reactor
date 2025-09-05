#ifndef __ACCEPTOR_H__
#define __ACCEPTOR_H__

#include "Socket.hpp"
#include "InetAddress.hpp"

#include <tcpHeader.h>

class Acceptor
{
private:
    Socket _socket;
    InetAddress _inetaddress;
public:
    Acceptor(string ip, unsigned short port);
    ~Acceptor();
    void setready();
    int setaccept();
    int getacceptfd();
private:
    void setreuseraddr(bool boo);
    void setreuserport(bool boo);
    void setbind();
    void setlisten();
};







#endif // !__ACCEPTOR_H__