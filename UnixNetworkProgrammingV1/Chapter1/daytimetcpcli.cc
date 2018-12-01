/******************************************
* File  :
* Date  : 2018-10-24
* Author: Zhang Tianjiu
* Email : zhangtianjiu@vip.qq.com
*******************************************/

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <iostream>

#define MAXLINE 256

int main(int argc, char** argv) {
    int sockfd = 0;
    int n = 0;
    char recvline[MAXLINE + 1];

    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <IPaddress>" << std::endl;
        return -1;
    }

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cout << "socket error, errno=" << errno << std::endl;
        return -1;
    }

    struct sockaddr_in svr_addr = {0};
    svr_addr.sin_family = AF_INET;
    svr_addr.sin_port = htons(13);
    if (inet_pton(AF_INET, argv[1], &svr_addr.sin_addr) < 0) {
        std::cout << "inet_pton error, errno=" << errno << std::endl;
        return -1;
    }

    if (connect(sockfd, (struct sockaddr*)&svr_addr, sizeof(svr_addr)) < 0) {
        std::cout << "connect error, errno=" << errno << std::endl;
        return -1;
    }

    while ((n = read(sockfd, recvline, MAXLINE)) > 0) {
        recvline[n] = 0;
        std::cout << recvline << std::endl;
    }

    if (n < 0) {
        std::cout << "read error, errno=" << errno << std::endl;
        return -1;
    }

    return 0;
}
