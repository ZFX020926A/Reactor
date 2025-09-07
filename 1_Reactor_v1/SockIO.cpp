#include "SockIO.hpp"

#include <tcpHeader.h>

SockIO::SockIO(int fd)
: _fd(fd)
{
}

SockIO::~SockIO()
{
}

// 检查缓冲区是否有内容
int SockIO::recvpeek(char *buff, int len)
{
    int ret = -1;
    do{
        ret = recv(_fd, buff, len, MSG_PEEK);
    }while(ret == -1 && errno == EINTR);

    return ret;
}

// 读n和数据 返回读到的数据
int SockIO::readn(char *buff, int len)
{   
    // 要读的总长度
    int flage = len;
    char *pbuff = buff;
    while(flage > 0)
    {
        int ret = recv(_fd, pbuff, flage, 0);
        if(ret == -1 && errno == EINTR)
        {
            continue;
        }
        else if(ret == -1)
        {
            perror("recv");
            return len - flage;
        }
        else if(ret == 0)
        {
            // 断开了连接
            return len - flage;
        }
        else {
            flage -= ret;
            pbuff += ret;
        }
    }
    return len - flage;
}

// 写n个数据
int SockIO::writen(const char *buff, int len)
{
    int flage = len;
    const char *pbuff = buff;
    while(flage > 0)
    {
        int ret = send(_fd, pbuff, flage, 0);
        if(ret == -1 && errno == EINTR)
        {
            continue;
        }
        else if(ret == -1)
        {
            perror("send");
            return len - flage;
        }
        else {
            flage -= ret;
            pbuff += ret;
        }
    }
    return len - flage;
}

// 读一行数据 一行多少数据是不知道的 需要找到\n
int SockIO::readline(char *buff, int len)
{
    char *pbuff = buff;
    int flage = len - 1; // 为\0留下一个位置 
    int total = 0; // 总共读了多少

    while(flage > 0)
    {
        int ret = recvpeek(pbuff, flage); // peek 不将缓冲区的内容删除掉

        for(int i = 0; i < ret; ++i)
        {
            if(pbuff[i] == '\n')
            {
                int nlocal = i + 1;
                ret = readn(pbuff, nlocal);
                total += ret;
                pbuff[i] = '\0';
                return total;
            }
        }

        // 没有找到\n则将找过的这部分拷贝出来
        ret = readn(pbuff, ret);
        flage -= ret;
        pbuff += ret;
        total += ret;
    }
    // 走到这里表示 没有多余的空间存储数据了，但是仍然没有找到\n
    buff[len - 1] = '\0';
    return len - 1;
}