#include <gtest/gtest.h>

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <mutex>
#include <array>
#include <string>

using namespace std::chrono_literals;

#ifdef _WIN32
  #include <windows.h>
  
  typedef HANDLE SemaphoreType;
#else
  #include <semaphore.h>

  typedef sem_t SemaphoreType;
#endif

const int Slots             = 4;
volatile bool stopProducers = false;
volatile bool stopConsumers = false;

typedef std::mutex                  MutexType;
typedef std::unique_lock<MutexType> LockType;

MutexType     mutex;
SemaphoreType empty;     // count empty buffer slots, initially N
SemaphoreType full;      // count full buffer slots,  initially 0

void initSemaphore(SemaphoreType* sem, int initialValue)
{
#ifdef _WIN32
  *sem = CreateSemaphore(NULL, initialValue, Slots, "");
  if (NULL == *sem) {
    throw std::runtime_error("CreateSemaphore error: " + std::to_string(GetLastError()));
  }
#else
  if (-1 == sem_init(sem, 0, initialValue)) {
    throw std::runtime_error("Failed to initialize semaphore, errno: " + std::to_string(errno));
  }
#endif
}

void destroySemaphore(SemaphoreType* sem)
{
#ifdef _WIN32
  CloseHandle(*sem);
#else
  sem_destroy(sem);
#endif
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
    std::cout << name_ << " " << action_ << " " << reported_ << " records\n";
  }

  void report() {
    ++reported_;
  }

  int numReports() const {
    return reported_;
  }

private:
  std::string name_;
  std::string action_;
  int         reported_;
};

bool down(SemaphoreType* sem)
{
#ifdef _WIN32
  if (WAIT_OBJECT_0 == WaitForSingleObject(*sem, 1000L))
    return true;

  LockType guard(mutex);
  std::cerr << "Thread " << std::this_thread::get_id() << ": wait timed out\n";

#else
  if (0 != sem_wait(sem))
    throw std::runtime_error("Failed to decrement semaphore, errno: " + std::to_string(errno));
#endif

  return false;
}

void up(SemaphoreType* sem)
{
#ifdef _WIN32
  LONG prevCount = 0;
  while (!ReleaseSemaphore(*sem, 1, &prevCount) ) {
    LockType guard(mutex);
    std::cerr << "ReleaseSemaphore error: " << GetLastError() << "\n";
  }
#else
  if (0 != sem_post(sem))
    throw std::runtime_error("Failed to increment semaphore, errno: " + std::to_string(errno));
#endif
}


template <class T, int N>
class CyclicBuffer {
public:
  CyclicBuffer()
    : nextFree_(0)
    , nextReady_(0) {
  }

  void insert(const T& item) {
    LockType guard(mutex);
    buffer_[nextFree_++] = item;
    if (nextFree_ == N)
      nextFree_ = 0;
  }

  bool remove(T& item) {
    LockType guard(mutex);
    if (nextFree_ == nextReady_)
      return false;
    item = buffer_[nextReady_++];
    if (nextReady_ == N)
      nextReady_ = 0;
    return true;
  }

private:
  size_t nextFree_;
  size_t nextReady_;
  std::array<T, N> buffer_;
};

CyclicBuffer<int, 2 * Slots> buffer;

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
  Reporter report("Producer " + std::to_string(number), "produced");
  while (!stopProducers) {
    int item = produceItem<int>();
    
    if (!down(&empty))
      continue;

    buffer.insert(item);
    up(&full);

    report.report();
  }
}

void consumer(int number)
{
  Reporter report("Consumer " + std::to_string(number), "consumed");
  int item;

  while (!stopConsumers) {
    if (!down(&full))
      continue;

    buffer.remove(item);
    up(&empty);

    consumeItem(item);
    report.report();
  }

  while (buffer.remove(item)) {
    consumeItem(item);
    report.report();
  }
}

TEST(ProducerConsumerTest, 1Producer1Consumer)
{
  initSemaphore(&empty, Slots);
  initSemaphore(&full,  0);

  stopProducers = false;
  stopConsumers = false;

  std::thread p1(producer, 1);
  std::thread c1(consumer, 1);

  std::this_thread::sleep_for(1s);

  stopProducers = true;
  p1.join();

  stopConsumers = true;
  c1.join();

  destroySemaphore(&full);
  destroySemaphore(&empty);
}

TEST(ProducerConsumerTest, 2Producer1Consumer)
{
  initSemaphore(&empty, Slots);
  initSemaphore(&full, 0);

  stopProducers = false;
  stopConsumers = false;

  std::thread p1(producer, 1);
  std::thread p2(producer, 2);
  std::thread c1(consumer, 1);

  std::this_thread::sleep_for(1s);

  stopProducers = true;
  p2.join();
  p1.join();
  
  stopConsumers = true;
  c1.join();

  destroySemaphore(&full);
  destroySemaphore(&empty);
}


TEST(ProducerConsumerTest, 1Producer4Consumer)
{
  initSemaphore(&empty, Slots);
  initSemaphore(&full, 0);

  stopProducers = false;
  stopConsumers = false;

  std::thread p1(producer, 1);
  std::thread c1(consumer, 1);
  std::thread c2(consumer, 2);
  std::thread c3(consumer, 3);
  std::thread c4(consumer, 4);

  std::this_thread::sleep_for(1s);

  stopProducers = true;
  p1.join();

  stopConsumers = true;
  c1.join();
  c2.join();
  c3.join();
  c4.join();

  destroySemaphore(&full);
  destroySemaphore(&empty);
}
