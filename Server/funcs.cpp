#include "funcs.h"
#include <string>
#include <thread>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>

using namespace std;

struct client{
    struct sockaddr_in ClientInfo;
    string Username;
    unsigned int ClientInfo_size = sizeof(ClientInfo);
};


int Socket(int domain, int type, int protocol){
    int res = socket(domain, type, protocol);
    if (res == -1){
        perror("socket error");
        exit(EXIT_FAILURE);
    }
    return res;
}

void Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen){
    int res = bind(sockfd, addr, addrlen);
    if (res == -1){
        perror("bind error");
        exit(EXIT_FAILURE);
    }
}

void Listen(int sockfd, int backlog){
    int res = listen(sockfd, backlog);
    if(res == -1){
        perror("listen failed");
        exit(EXIT_FAILURE);
    }
}

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen){
    int res = accept(sockfd, addr, addrlen);
    if (res == -1){
        perror("accept failed");
        exit(EXIT_FAILURE);
    }
    return res;
}

void Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen){
    int res = connect(sockfd, addr, addrlen);
    if (res == -1){
        perror("connecting failed");
        exit(EXIT_FAILURE);
    }
}

void Inet_pton(int af, const char *src, void *dst){
    int res = inet_pton(af, src, dst);
    if (res == 0) {
        printf("src not valid\n");
        exit(EXIT_FAILURE);
    }
    if (res == -1) {
        perror("inet_pton failed");
        exit(EXIT_FAILURE);
    }
    
}

void Client(int port){
    int fd = Socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in adr = {0};
    adr.sin_family = AF_INET;
    adr.sin_port = htons(port); 
    Inet_pton(AF_INET, "127.0.0.1", &adr.sin_addr);
    Connect(fd, (struct sockaddr *)&adr, sizeof adr);
    thread th(Write, fd);
    thread th2(Read, fd);
    th.join();
    th2.join();
    close(fd);
}

void Server(int port){
    int fd[2];
    string buf;
    client clients[2];
    int server = Socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in adr = {0};
    adr.sin_family = AF_INET;
    adr.sin_port = htons(port);
    Bind(server, (struct sockaddr *)&adr, sizeof adr);
    Listen(server, 2);
    socklen_t adrlen = sizeof adr;
    for (int i = 0; i < 2; i++){
        fd[i] = Accept(server, (sockaddr*)&clients[i].ClientInfo, &clients[i].ClientInfo_size);
        cout << clients[i].ClientInfo.sin_port << endl;     
    }
    thread th1(Serve, fd[0], fd[1]);
    thread th2(Serve, fd[1], fd[0]);
    th1.join();
    th2.join();
    close(fd[0]);
    close(fd[1]);
    close(server);
}

void Serve(int fd1, int fd2){
    char msg[1024];
    while(true){
        read(fd1, msg, 1024);
        write(fd2, msg, 1024); 
        printf("%s\n", msg);
    }
}

void Write(int fd){
    char msg[1024];
    while(true){
        scanf("%s", msg);
        write(fd, msg, 1024);
    }
}

void Read(int fd){
    char msg[1024];
    while(true){
        read(fd, msg, 1024);
        printf("%s\n", msg);
    }
}
