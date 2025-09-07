#include "InetAddress.hpp"

InetAddress::InetAddress(string ip, unsigned short port)
{
    memset(&_addrin, 0, sizeof(_addrin));
    _addrin.sin_family = AF_INET;
    _addrin.sin_addr.s_addr = inet_addr(ip.c_str());
    _addrin.sin_port = htons(port);
}

InetAddress::InetAddress(const struct sockaddr_in &addr)
: _addrin(addr)
{

}

InetAddress::~InetAddress()
{
}

string InetAddress::getip()
{
    return string(inet_ntoa(_addrin.sin_addr));
}

unsigned short InetAddress::getport()
{
    return ntohs(_addrin.sin_port);
}

struct sockaddr_in * InetAddress::getaddrin()
{
    return &_addrin;
}