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

using namespace std;

#ifdef _WIN32
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
#endif

std::string getIp(const struct in_addr& addr) {
  char ip4[INET_ADDRSTRLEN];
  inet_ntop(AF_INET, &addr, ip4, INET_ADDRSTRLEN);
  return std::string(ip4);
}

std::string getIp(const struct in6_addr& addr) {
  char ip6[INET6_ADDRSTRLEN];
  inet_ntop(AF_INET6, &addr, ip6, INET6_ADDRSTRLEN);
  return std::string(ip6);
}

std::string getIp4ByHost(const std::string& host) {

}

std::string getIp6ByHost(const std::string& host) {

}

void numbersToInet() {
  struct sockaddr_in sa; // IPv4
  struct sockaddr_in6 sa6; // IPv6

  inet_pton(AF_INET, "10.12.110.57", &(sa.sin_addr)); // IPv4
  inet_pton(AF_INET6, "2001:db8:63b3:1::3490", &(sa6.sin6_addr)); // IPv6

  std::cout << getIp(sa.sin_addr)   << std::endl;
  std::cout << getIp(sa6.sin6_addr) << std::endl;
}

void getaddrinfo1() {
  int status;
  struct addrinfo hints;
  struct addrinfo *servinfo;  // will point to the results

  memset(&hints, 0, sizeof hints); // make sure the struct is empty
  hints.ai_family = AF_UNSPEC;     // don't care IPv4 or IPv6
  hints.ai_socktype = SOCK_STREAM; // TCP stream sockets
  hints.ai_flags = AI_PASSIVE;     // fill in my IP for me

  if ((status = getaddrinfo(NULL, "3490", &hints, &servinfo)) != 0) {
    fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
    exit(1);
  }

  // servinfo now points to a linked list of 1 or more struct addrinfos

  // ... do everything until you don't need servinfo anymore ....
  freeaddrinfo(servinfo); // free the linked-list
}

void getaddrinfo2() {
  int status;
  struct addrinfo hints;
  struct addrinfo *servinfo;  // will point to the results

  memset(&hints, 0, sizeof hints); // make sure the struct is empty
  hints.ai_family = AF_UNSPEC;     // don't care IPv4 or IPv6
  hints.ai_socktype = SOCK_STREAM; // TCP stream sockets

  // get ready to connect
  status = getaddrinfo("www.example.net", "3490", &hints, &servinfo);

  // servinfo now points to a linked list of 1 or more struct addrinfos
  freeaddrinfo(servinfo); // free the linked-list
}

int main(int, char const *[])
{
#ifdef _WIN32
  WinsockInitializer wsi;
#endif
  numbersToInet();
//  getaddrinfo1();
//  getaddrinfo2();

  return 0;
}
