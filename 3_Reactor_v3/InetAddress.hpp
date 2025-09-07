#ifndef __INETADDRESS_H__
#define __INETADDRESS_H__

#include <tcpHeader.h>
#include <string>

using std::string;

class InetAddress
{
private:
    struct sockaddr_in _addrin;
public:
    InetAddress(string ip, unsigned short port);
    InetAddress(const struct sockaddr_in &addr);
    ~InetAddress();
    string getip();
    unsigned short getport();
    struct sockaddr_in *getaddrin();
};




#endif // !__INETADDRESS_H__