#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>

int main(){
    int sock, len, fromlen, n;
    struct sockaddr_in server, client;
    char buff[1024], message[1024] = "Hello World This is the message send from server side";

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock<0){
        perror("Error in creating socket");
    }
    len = sizeof(server);
    bzero(&server, len);
    server.sin_family = AF_INET;
    server.sin_port = htons(9001);
    server.sin_addr.s_addr = INADDR_ANY;
    if (bind(sock, (struct sockaddr *)&server, len) < 0);{
        perror("Error in Binding Socket with IP and PORT");
    }   
    fromlen = sizeof(struct sockaddr_in);
    while (1)
    {
        n = recvfrom(sock, buff, sizeof(buff), 0, (struct sockaddr *)&client, &fromlen);
        if (n<0){
            perror("Error in recieving");
        }
        write(1, message, sizeof(message));
        write(1, buff, n);
        char msg[100] = "Got your message\n";
        n = sendto(sock, msg, sizeof(msg), 0, (struct sockaddr *)&client, fromlen);
        if (n<0)
        {
            perror("Error in sending message from server side");
        }
    }
    return 0;
}