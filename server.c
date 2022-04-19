#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main(void){
    int sock_desc;
    struct sockaddr_in server_addr, client_addr;
    char server_message[1024], client_message[1024];
    int client_struct_length = sizeof(client_addr);

    // Clean the buffer
    memset(server_message, '\0', sizeof(server_message));
    memset(client_message, '\0', sizeof(client_message));

    // Create UDP Socket
    sock_desc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (sock_desc<0){
        printf("\nError in creating the socket...");
        return -1;
    }
    printf("\nSocket Created Successfully");

    // Set the IP and PORT number for binding
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Bind the socket with IP and PORT
    if (bind(sock_desc, (struct sockaddr *)&server_addr, sizeof(server_addr))<0){
        printf("\nError in binding the port...");
        return -1;
    }
    printf("\nBinding done successfully");
    printf("\nListening for the incoming messages...");

    // Receive client's message
    if (recvfrom(sock_desc, client_message, sizeof(client_message), 0, (struct sockaddr *)&client_addr, &client_struct_length)<0)
    {
        printf("\nError in receiving data from client...");
        return -1;
    }
    printf("\nData Received from client: %s\n", client_message);
    if (sendto(sock_desc, server_message, strlen(server_message), 0, (struct sockaddr *)&client_addr, client_struct_length)<0)
    {
        printf("\nError in sending data to the client...");
        return -1;
    }
    // Close the socket
    return 0;
}








