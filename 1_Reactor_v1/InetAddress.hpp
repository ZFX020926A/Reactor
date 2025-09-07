#ifndef __INETADDRESS_H__
#define __INETADDRESS_H__

#include <tcpHeader.h>
#include <string>

using std::string;

class InetAddress
{    
public:
    InetAddress(string ip, unsigned short);
    InetAddress(const struct sockaddr_in &addr);

    ~InetAddress();
    string getip();
    unsigned short getport();
    struct sockaddr_in * getaddrin();
private:
    struct sockaddr_in _addrin;
};



#endif //  __INETADDRESS_H__