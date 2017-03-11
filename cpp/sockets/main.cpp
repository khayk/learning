#include "Basics.h"

int main(int, char const *[])
{
#ifdef _WIN32
  WinsockInitializer wsi;
#endif

  network::ipByHost("localhost");
  network::ipByHost("epam.com");
  return 0;
}
