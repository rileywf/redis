#include <sys/socket.h>
#include <cstdint>
#include <arpa/inet.h>
#include <string>
#include <errno.h>
#include <cstring>
#include <unistd.h>
#include <iostream>

void die(const std::string errmsg) {
    int err = errno;
    std::cout << errmsg << ": " << errno << std::endl;
}


int main() {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) { die("socket()");}

    struct sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_port = ntohs(1234);
    addr.sin_addr.s_addr = ntohl(INADDR_LOOPBACK); // 127.0.0.1
    int rv = connect(fd, (const struct sockaddr *)&addr, sizeof(addr));
    if (rv) { die("Connect");}

    char msg[]  = "hello";
    write(fd, msg, strlen(msg));

    char rbuf[64] = {};
    ssize_t n = read(fd, rbuf, sizeof(rbuf) - 1);
    if(n<0) {die("read");}

    std::cout << "server says: " << rbuf << std::endl;
    close(fd);
}