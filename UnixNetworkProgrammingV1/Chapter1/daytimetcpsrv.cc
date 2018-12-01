/******************************************
* File  : daytimetcpsrv.cc
* Date  : 2018-10-24
* Author: Zhang Tianjiu
* Email : zhangtianjiu@vip.qq.com
*******************************************/

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#include <iostream>

int main(int argc, char** argv) {
    int listenfd = 0;
    int connfd = 0;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0) {
        std::cout << "socket error, errno=" << errno << std::endl;
        return -1;
    }

    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(13);
    if (bind(listenfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        std::cout << "bind error, errno=" << errno << std::endl;
        return -1;
    }

    if (listen(listenfd, 10) < 0) {
        std::cout << "listen error, errno=" << errno << std::endl;
        return -1;
    }

    for (;;) {
        connfd = accept(listenfd, nullptr, nullptr);
        if (connfd < 0) {
            std::cout << "accept error, errno=" << errno << std::endl;
            return -1;
        }

        char buff[1024] = {0};
        time_t ticks = time(nullptr);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));

        if (write(connfd, buff, strlen(buff)) < 0) {
            std::cout << "write error, errno=" << errno << std::endl;
            return -1;
        }

        close(connfd);
    }

    return 0;
}
