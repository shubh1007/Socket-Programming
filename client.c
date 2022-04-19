#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main(void){
    int sock_desc;
    struct sockaddr_in server_address;
    char server_message[1024], client_message[1024];
    int server_struct_length = sizeof(server_address);

    // Clean the buffer
    memset(server_message, '\0', sizeof(server_message));
    memset(client_message, '\0', sizeof(client_message));
    // Create Client Socket
    sock_desc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (sock_desc < 0){
        printf("\nError in creating socket...");
        return -1;
    }
    printf("\nScoket created successfully...");
    // Set the Port and IP of the socket
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(2000);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    // Get the message input from user
    printf("\nEnter the message: ");
    gets(client_message);
    // send message to the server
    if (sendto(sock_desc, client_message, strlen(client_message), 0, (struct sockaddr*)&server_address, server_struct_length)<0)
    {
        printf("\nError in sending message to the server...");
        return -1;
    }
    // Receiver the server's response
    if (recvfrom(sock_desc, server_message, sizeof(server_message), 0, (struct sockaddr*)&server_address, &server_struct_length)<0)
    {
        printf("\nError in receiving response from server...");
        return -1;
    }
    printf("\nServer's Response: %s", server_message);
    // Close the socket
    close(sock_desc);
    

    return 0;
}