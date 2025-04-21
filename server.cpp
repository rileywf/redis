#include <sys/socket.h>
#include <cstdint>
#include <arpa/inet.h>
#include <string>
#include <errno.h>
#include <iostream>

/*IPv4*/
struct sockaddr_in {
    uint16_t sin_family; // AF_INET
    uint16_t sin_port; //port in bi-endian
    struct in_addr sin_addr;    //IPv4
};

struct in_addr {
    uint32_t s_addr;    // IPv4 in big-endian
};

/*IPv6
    TODO: implement this later when IPv4 is done.
*/
struct sockaddr_in6 {
    uint16_t sin6_family; //AF_INET6
    uint16_t   sin6_port; // port in big-endian
    uint32_t sin6_flowinfo; //ignore
    struct in6_addr sin6_addr; //IPv6
    uint32_t sin6_scope_id; //ignore
};

struct in6_addr {
    uint8_t s6_adder[16]; //ipv6
};


void die(const std::string errmsg) {
    int err = errno;
    std::cout << errmsg << ": " << errno << std::endl;
}


int main() {
    int fd = socket(AF_INET, SOCK_STREAM, 0);

    int val = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));

    struct sockaddr_in addr = {};
    addr.sin_family =  AF_INET;
    addr.sin_port = htons(1234);    //port
    addr.sin_addr.s_addr = htonl(0);    //wildcard IP 0.0.0.0
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
        
    }

}