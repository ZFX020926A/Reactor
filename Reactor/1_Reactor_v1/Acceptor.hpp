#ifndef __ACCEPTOR_H__
#define __ACCEPTOR_H__
#include "Socket.hpp"
#include "InetAddress.hpp"

class Acceptor
{
public:
    Acceptor(string ip, unsigned short port);
    ~Acceptor();
    void setready();
    int setaccept();
private:
    void setreuseraddr(bool boo);
    void setreuserport(bool boo);
    void setbind();
    void setlisten(int listennums = 20000);
private:
    Socket      _socket;
    InetAddress _inetaddress;
};

#endif // !__ACCEPTRO_H__
