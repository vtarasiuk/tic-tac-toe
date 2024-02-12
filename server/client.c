#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8888
#define MAX_BUFFER 512

int main() {
    int clientSocket;
    struct sockaddr_in serverAddr;
    // char buffer[MAX_BUFFER] = {0};

    // Create socket
    if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Initialize server address struct
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }

    // Connect to the server
    if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    printf("Connected to the server\n");

    // Send a message to the server
    // const char *message = "Hello from the client!";
    // send(clientSocket, message, strlen(message), 0);
    // printf("Message sent to server: %s\n", message);

    // // Read the server's response
    // read(clientSocket, buffer, MAX_BUFFER);
    // printf("Received from server: %s\n", buffer);

    char buffer[9 + 1] = {0};
    while(1)
    {
        ssize_t read;
        if ((read = recv(clientSocket, buffer, sizeof(buffer), 0)) != sizeof(buffer))
        {
            perror("Invalid data received");
        }
        printf("Received data: %ld size long\nData: %s\n", read, buffer);
        sleep(3);
    }
    // Close socket
    close(clientSocket);

    return 0;
}
