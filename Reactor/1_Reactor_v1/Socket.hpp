#ifndef __SOCKET_H__
#define __SOCKET_H__



class Socket{
public:
    Socket();
    
    Socket(int fd)
    : _sockfd(fd)
    {

    }
    
    ~Socket();

    int getsockfd() {
        return _sockfd;
    }

    void ShuntDownWrite();

private:
    int _sockfd;
};



#endif // !__SOCKET_H__