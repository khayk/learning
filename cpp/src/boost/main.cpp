#include <iostream>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>

void fn()
{
  boost::shared_ptr<int> sp = boost::make_shared<int>(4);
  std::cout << "fn called\n" << *sp;
}

int main(int, char*[])
{
  fn();
  return 0;
}
