#ifndef __SOCKET_PLATFORM_H__
#define __SOCKET_PLATFORM_H__


#ifdef _WIN32
  #include <Ws2tcpip.h>
  #include <winsock.h>
#else
  #include <netinet/in.h>
  #include <arpa/inet.h>
  #include <sys/types.h>
  #include <sys/socket.h>
  #include <netdb.h>
#endif

#include <iostream>
#include <cstring>

#ifdef _WIN32
class WinsockInitializer {
public:
  WinsockInitializer() {
    WSAData wsaData;
    if (0 != WSAStartup(MAKEWORD(1, 1), &wsaData)) {
      std::cerr << "WSAStartup failed.\n";
    }
  }

  ~WinsockInitializer() {
    WSACleanup();
  }
};
#endif


#endif // __SOCKET_PLATFORM_H__
