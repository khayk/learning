#include <Ws2tcpip.h>
#include <winsock.h>
#include <iostream>

using namespace std;

class WinsockInitializer {
public:
  WinsockInitializer() {
    WSAData wsaData;
    if (0 != WSAStartup(MAKEWORD(1, 1), &wsaData)) {
      cerr << "WSAStartup failed.\n";
    }
  }

  ~WinsockInitializer() {
    WSACleanup();
  }
};

void numbersToInet() {
  struct sockaddr_in sa; // IPv4
  struct sockaddr_in6 sa6; // IPv6

  inet_pton(AF_INET, "10.12.110.57", &(sa.sin_addr)); // IPv4
  inet_pton(AF_INET6, "2001:db8:63b3:1::3490", &(sa6.sin6_addr)); // IPv6


                                                                  // IPv4:
  char ip4[INET_ADDRSTRLEN];  // space to hold the IPv4 string
  // struct sockaddr_in sa;      // pretend this is loaded with something
  inet_ntop(AF_INET, &(sa.sin_addr), ip4, INET_ADDRSTRLEN);
  printf("The IPv4 address is: %s\n", ip4);

  // IPv6:
  char ip6[INET6_ADDRSTRLEN]; // space to hold the IPv6 string
  // struct sockaddr_in6 sa6;    // pretend this is loaded with something
  inet_ntop(AF_INET6, &(sa6.sin6_addr), ip6, INET6_ADDRSTRLEN);
  printf("The address is: %s\n", ip6);
}

int main(int, char const *[])
{
  WinsockInitializer wsi;
  numbersToInet();
  return 0;
}
