
/*

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

void numbersToInet() {
  struct sockaddr_in sa; // IPv4
  struct sockaddr_in6 sa6; // IPv6

  inet_pton(AF_INET, "10.12.110.57", &(sa.sin_addr)); // IPv4
  inet_pton(AF_INET6, "2001:db8:63b3:1::3490", &(sa6.sin6_addr)); // IPv6

  std::cout << network::getIp(sa.sin_addr)   << std::endl;
  std::cout << network::getIp(sa6.sin6_addr) << std::endl;
}

*/
