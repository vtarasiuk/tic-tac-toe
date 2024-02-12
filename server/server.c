#include "server.h"
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "../game.h"

#define PORT 8888
#define CONNECTIONS_LIMIT 2

int main()
{
  SocketDescriptor server = {0};
  int error = serverStart(&server);
  if (error != SERVER_STARTUP_SUCCESS)
  {
    if (error != SERVER_STARTUP_ERROR_SOCKET_INIT)
    {
      printf("Close call for server fd\n");
      printf("Address: %s\n", inet_ntoa(server.addr.sin_addr));
      close(server.socketFd);
    }
    perror("Failed to start a server");
    return EXIT_FAILURE;
  }

  fprintf(stdout, "Waiting for connections on port %d...\n", PORT);

  SocketDescriptor clients[2] = {0};

  // establish connection with 2 clients
  for (size_t client = 0; client < 2; client++)
  {
    clients[client].addr_len = sizeof(clients[client].addr);
    int clientSockFd = accept(server.socketFd, (struct sockaddr *)&clients[client].addr, &clients[client].addr_len);
    if (clientSockFd == -1)
    {
      perror("Error during accept call");
      client -= 1;
      continue;
    }
    // also, what if during a connection a previous client was disconnected? 
    clients[client].socketFd = clientSockFd;

    fprintf(stdout, "Connection accepted from %s:%d\n", inet_ntoa(clients[client].addr.sin_addr), ntohs(clients[client].addr.sin_port));
  }

  char gameState[] = "---------";
  printf("sizeof gameState = %ld\n", sizeof gameState);

    const int BUF_SIZE = 512;
    char buffer1[BUF_SIZE];
    char buffer2[BUF_SIZE];
    // Read data from the client
  
  int turn = 1;
  int client1, client2;
  while (1)
  {
    // who is first turn player => sent, receive, sent to another player, receive, loop until game ends
    // error checking, send function optimization (flags)
    send(clients[0].socketFd, gameState, sizeof(gameState), 0);
    client1 = recv(clients[0].socketFd, buffer1, BUF_SIZE, 0);
    if (client1 == 0)
    {
      fprintf(stderr, "Client 1 disconnected from the server\n");
      break;
    }

    memcpy(gameState, buffer1, 9 + 1); // vulnerability\
    // do validating input
    // then copying into structure from game.h gamefield
    // then I need parsing function that will parse gamefield state into string
    // save this string, send to the next player
    // wait until answer

    send(clients[1].socketFd, gameState, sizeof(gameState), 0);
    client2 = recv(clients[1].socketFd, buffer2, BUF_SIZE, 0);

    memcpy(gameState, buffer2, 9 + 1); // vulnerability
  }

    // // Send a message back to the client
    // const char *message = "Hello from the server!";
    // send(clientSocketFd, message, strlen(message), 0);

  // Close sockets
  for (int i = 0; i < 2; ++i) {
    close(clients[i].socketFd);
  }
  close(server.socketFd);

  return EXIT_SUCCESS;
}

ServerStartupError serverStart(lpSocketDescriptor server)
{
  if (server == NULL)
  {
    return SERVER_STARTUP_UNKNOWN_ERROR;
  }

  server->socketFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (server->socketFd == -1)
  {
    return SERVER_STARTUP_ERROR_SOCKET_INIT;
  }

  server->addr.sin_family = AF_INET;
  server->addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
  server->addr.sin_port = htons(PORT);
  server->addr_len = sizeof(server->addr);

  if (bind(server->socketFd, (struct sockaddr *)&server->addr, server->addr_len) == -1)
  {
    return SERVER_STARTUP_ERROR_SOCKET_BINDING;
  }

  if (listen(server->socketFd, CONNECTIONS_LIMIT) == -1)
  {
    return SERVER_STARTUP_ERROR_LISTENING;
  }

  return SERVER_STARTUP_SUCCESS;
}