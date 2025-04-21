#include <sys/socket.h>
#include <cstdint>
#include <arpa/inet.h>

struct sockaddr_in {
    uint16_t sin_family; // AF_INET
    uint16_t sin_port; //port in bi-endian
    struct in_addr sin_addr;    //IPv4
};

struct in_addr {
    uint32_t s_addr;    // IPv4 in big-endian
};


int main() {
    int fd = socket(AF_INET, SOCK_STREAM, 0);

    int val = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));

    struct sockaddr_in addr = {};
    addr.sin_family =  AF_INET;
    addr.sin_port = htons(1234);    //port
    addr.sin_addr.s_addr = htonl(0);    //wildcard IP 0.0.0.0

}