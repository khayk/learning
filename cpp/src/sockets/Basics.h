#ifndef SOCKETS_BASICS_H
#define SOCKETS_BASICS_H

#include <string>
#include "Platform.h"

namespace network {

std::string getIp(const struct in_addr& addr)
{
  char ip4[INET_ADDRSTRLEN];
  inet_ntop(AF_INET, (void*)&addr, ip4, INET_ADDRSTRLEN);
  return std::string(ip4);
}

std::string getIp(const struct in6_addr& addr)
{
  char ip6[INET6_ADDRSTRLEN];
  inet_ntop(AF_INET6, (void*)&addr, ip6, INET6_ADDRSTRLEN);
  return std::string(ip6);
}

std::string getIp4ByHost(const std::string&)
{
  return std::string();
}

std::string getIp6ByHost(const std::string&)
{
  return std::string();
}

std::string ipByHost(const std::string& host)
{
  struct addrinfo hints, *res, *p;
  char ipstr[INET6_ADDRSTRLEN];
  int status;

  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC;      // AF_INET or AF_INET6 to force version
  hints.ai_socktype = SOCK_STREAM;

  if ((status = getaddrinfo(host.c_str(), NULL, &hints, &res)) != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
    return std::string();
  }

  printf("%s: ", host.c_str());

  for (p = res; p != NULL; p = p->ai_next) {
    void *addr;
    const char *ipver;

    // get the pointer to the address itself,
    // different fields in IPv4 and IPv6:
    if (p->ai_family == AF_INET) { // IPv4
      struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
      addr = &(ipv4->sin_addr);
      ipver = "v4";
    } else { // IPv6
      struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
      addr = &(ipv6->sin6_addr);
      ipver = "v6";
    }

    // convert the IP to a string and print it:
    inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
    printf("%s (%s)\n", ipstr, ipver);
  }

  freeaddrinfo(res); // free the linked list
  return std::string(ipstr);
}

}

#endif // SOCKETS_BASICS_H



