#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h> // для структуры sockaddr_in
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int s = socket(AF_INET, SOCK_STREAM, 0);
    if(s == -1) {
        perror("client: an error occurred while creating socket.");
        return -1;
    }
    struct sockaddr_in server_address = {0};
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(55555);
    inet_aton("127.0.0.1", &server_address.sin_addr);
    int con = connect(s, (struct sockaddr*)&server_address, sizeof server_address);
    if(con == -1) {
        perror("client: cannot connect to the server.");
        return -1;
    }
    char buf[256];
    read(s, &buf, sizeof buf);
    printf("%s", buf);
    close(s);
}