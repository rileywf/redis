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

void msg(std::string msg) {
    std::cerr << msg << std::endl;
}



void get_conn(int connfd) {
    char rbuf[64] = {};

    ssize_t n = read(connfd, rbuf, sizeof(rbuf)-1);
    if(n < 0) {
        msg("read() error");
        return;
    }

    std::cout << "client says: " << rbuf << std::endl;

    char wbuf[] = "world";
    write(connfd, wbuf, strlen(wbuf));
}


int main() {
    int fd = socket(AF_INET, SOCK_STREAM, 0);

    int val = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));

    struct sockaddr_in addr = {};
    addr.sin_family =  AF_INET;
    addr.sin_port = htons(1234);    //port
    addr.sin_addr.s_addr = ntohl(0);    //wildcard IP 0.0.0.0
    int rv = bind(fd, (const struct sockaddr *)&addr, sizeof(addr));
    if (rv) { die("bind()"); }

    //listen
    rv = listen(fd, SOMAXCONN);
    if (rv) { die("listen()"); }

    //accept connections
    while(true) {
        //accept
        struct sockaddr_in client_addr = {};
        socklen_t addrlen = sizeof(client_addr);
        int connfd = accept(fd, (struct sockaddr *)&client_addr, &addrlen);
        if (connfd < 0) {
            continue; //error
        }

        get_conn(connfd);

        close(connfd); // close connection

    }

}