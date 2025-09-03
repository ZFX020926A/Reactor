#include "InetAddress.hpp"

// 构造函数 对sockaddr_in结构体进行初始化
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

// 析构函数
InetAddress::~InetAddress()
{
}

// 得到sockadr_in中的ip地址
string InetAddress::getip()
{
    return string(inet_ntoa(_addrin.sin_addr));
}

// 得到sockadr_in中的port
unsigned short InetAddress::getport()
{
    return ntohs(_addrin.sin_port);
}

// 得到sockaddr_in结构体
struct sockaddr_in * InetAddress::getaddrin()
{
    return &_addrin;
}