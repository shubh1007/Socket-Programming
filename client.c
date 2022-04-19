#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>

int main(){
    int sock, len, fromlen, n;
    struct sockaddr_in server, client;
    struct hostent *hp;
    char buff[1024];

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock<0){
        perror("Error in creating socket");
    }
    server.sin_family = AF_INET;
    hp = gethostbyname()
    server.sin_port = htons(9001);
    server.sin_addr.s_addr = "127.0.0.1";
    if (bind(sock, (struct sockaddr *)&server, len) < 0);{
        perror("Error in Binding Socket with IP and PORT");
    }
    fromlen = sizeof(struct sockaddr_in);
    while (1)
    {
        n = recvfrom(sock, buff, sizeof(buff), 0, (struct sockaddr *)&client, &fromlen);
        if (n<0){
            perror("Error in recieving data");
        }
        
    }
    return 0;
}