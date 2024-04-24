//
// Created by Gusta on 24-04-2024.
//

#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 12345
#define BUFFER_SIZE 1024

int clientInit() {
    WSADATA wsa;
    SOCKET client_socket;
    struct sockaddr_in server_address;
    char message[BUFFER_SIZE];
    char buffer[BUFFER_SIZE];

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("WSAStartup failed\n");
        return 1;
    }

    // Create socket
    if ((client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {
        printf("Socket creation failed\n");
        return 1;
    }

    // Initialize server address
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(SERVER_IP);
    server_address.sin_port = htons(SERVER_PORT);

    // Connect to server
    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == SOCKET_ERROR) {
        printf("Connection failed\n");
        return 1;
    }

    // Continuously send and receive data
    while (1) {
        // Send data to server
        strcpy(message, "Hello from C client!");
        send(client_socket, message, strlen(message), 0);
        printf("Sent to server: %s\n", message);

        // Receive response from server
        int bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
        if (bytes_received <= 0) {
            printf("Server disconnected\n");
            break;
        }
        buffer[bytes_received] = '\0';
        printf("Received from server: %s\n", buffer);

        // Sleep for a while to simulate continuous operation
        Sleep(1000);
    }

    // Cleanup
    closesocket(client_socket);
    WSACleanup();
    return 0;
}
