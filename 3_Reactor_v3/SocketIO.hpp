#ifndef __SOCKETIO_H__
#define __SOCKETIO_H__

class SocketIO
{
private:
    int _fd;
public:
    SocketIO(int fd);
    ~SocketIO();

    int readn(char *buff, int len);
    int writen(const char *buff, int len);
    int readline(char *buff, int len);
    int recvpeek(char *buff, int len);
};




#endif // !__SOCKETIO_H__#define __