#ifndef SERVER_H
#define SERVER_H

#include <sys/socket.h>
#include <netdb.h>

typedef struct
{
  int socketFd;
  struct sockaddr_in addr;
  socklen_t addr_len;
} SocketDescriptor, *lpSocketDescriptor;

typedef enum {
  SERVER_STARTUP_SUCCESS = 0,
  SERVER_STARTUP_ERROR_SOCKET_INIT,
  SERVER_STARTUP_ERROR_ADDRESS_SETUP,
  SERVER_STARTUP_ERROR_SOCKET_BINDING,
  SERVER_STARTUP_ERROR_LISTENING,
  SERVER_STARTUP_UNKNOWN_ERROR,
} ServerStartupError;

static ServerStartupError serverStart(lpSocketDescriptor server);

#endif