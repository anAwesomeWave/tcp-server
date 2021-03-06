#include <stdio.h> // perror
#include <sys/types.h> // для сокета | man socket
#include <sys/socket.h> // для сокета
#include <netinet/in.h> // для структуры sockaddr_in
#include <arpa/inet.h> // для перевода в другой байтовый порядок | man htonl
#include <unistd.h> // для системных вызовов write read

int main(){
    int s = socket(AF_INET, SOCK_STREAM, 0);
    if(s == -1) {
        perror("an error occurred while creating socket.");
        return -1;
    }

    struct sockaddr_in server_addr = {0};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(55555);
    server_addr.sin_addr.s_addr = INADDR_ANY; // 0.0.0.0

    int opt = 1;
    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)); // чтобы порт не "залипал".
    int e = bind(s, (struct sockaddr*)&server_addr, sizeof server_addr);

    if(e == -1) {
        perror("error with setting up an address.");
        return -2;
    }

    listen(s, 5);

    struct sockaddr_in client_addr = {0};
    socklen_t len = sizeof(client_addr);
    int clsock = accept(s, (struct sockaddr*)&client_addr, &len);

    if(clsock == -1) {
        perror("error while establishing connection with client.");
        return -3;
    }else {
        printf("connection established.\n");
    }
    char buf[]= "You have reached the server.\n";
    write(clsock, buf, sizeof buf);
    close(clsock);
}