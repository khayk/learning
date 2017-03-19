#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <mutex>
#include <array>
#include <semaphore.h>

const int Slots             = 12;
volatile bool stopRequested = false;

typedef sem_t                       SemaphoreType;
typedef std::mutex                  MutexType;
typedef std::unique_lock<MutexType> LockType;

MutexType     mutex;
SemaphoreType empty;     // count empty buffer slots, initially N
SemaphoreType full;      // count full buffer slots,  initially 0

void initSemaphore(SemaphoreType* sem, int initialValue)
{
  if (-1 == sem_init(sem, 0, initialValue)) {
    throw std::runtime_error("Failed to initialize semaphore, errno: " + std::to_string(errno));
  }
}

void destroySemaphore(SemaphoreType* sem)
{
  sem_destroy(sem);
}

void handleError(const std::exception& e)
{
  std::cerr << "ERROR: " << e.what() << std::endl;
}

class Reporter {
public:
  Reporter(const std::string& name, const std::string& action)
    : name_(name)
    , action_(action)
    , reported_(0) {
  }

  ~Reporter() {
    LockType guard(mutex);
    std::cout << name_ << " " << action_ << " " << reported_ << " recoreds\n";
  }

  void report() {
    ++reported_;
  }

private:
  std::string name_;
  std::string action_;
  int         reported_;
};

void down(SemaphoreType* sem)
{
  if (0 != sem_wait(sem))
    throw std::runtime_error("Failed to decrement semaphore, errno: " + std::to_string(errno));
}

void up(SemaphoreType* sem)
{
  if (0 != sem_post(sem))
    throw std::runtime_error("Failed to increment semaphore, errno: " + std::to_string(errno));
}


template <class T, int N>
class CyclicBuffer {
public:
  CyclicBuffer()
    : nextFree_(0)
    , nextReady_(0) {
  }

  void insert(const T&) {
    // LockType guard(mutex);
    // buffer_[nextFree_++] = item;
    // if (nextFree_ == N)
    //   nextFree_ = 0;
  }

  void remove(T&) {
    // LockType guard(mutex);
    // item = buffer_[nextReady_++];
    // if (nextReady_ == N)
    //   nextReady_ = 0;
  }

  bool empty() const {
    LockType guard(mutex);
    return nextFree_ == nextReady_;
  }

private:
  size_t nextFree_;
  size_t nextReady_;
  std::array<T, N> buffer_;
};

CyclicBuffer<int, Slots> buffer;

template <class T>
T produceItem()
{
  return 0;
}

template <class T>
void consumeItem(T& item)
{
  ++item;
}


void producer(int number)
{
  try {
    Reporter report("Producer " + std::to_string(number), "produced");
    while (!stopRequested) {
      int item = produceItem<int>();
      report.report();

      down(&empty);
      buffer.insert(item);
      up(&full);
    }
  }
  catch (const std::exception& e) {
    handleError(e);
  }
}

void consumer(int number)
{
  try {
    Reporter report("Consumer " + std::to_string(number), "consumed");
    int item;
    while (!stopRequested) {
      down(&full);
      buffer.remove(item);
      up(&empty);

      consumeItem(item);
      report.report();
    }
  }
  catch (const std::exception& e) {
    handleError(e);
  }

  // while (!buffer.empty()) {
  //   buffer.remove(item);
  //   consumeItem(item);
  //   report.report();
  // }
}

int main(int, char const *[])
{
  using namespace std::chrono_literals;

  try {
    initSemaphore(&empty, Slots);
    initSemaphore(&full,  0);

    std::thread p1(producer, 1);
    std::thread c1(consumer, 1);
    std::thread c2(consumer, 2);
    std::thread c3(consumer, 3);
    // std::thread c4(consumer, 4);

    std::this_thread::sleep_for(1s);
    stopRequested = true;
    // c4.join();
    c3.join();
    c2.join();
    c1.join();
    p1.join();

    destroySemaphore(&full);
    destroySemaphore(&empty);
  }
  catch (const std::exception& e) {
    handleError(e);
  }


  return 0;
}
