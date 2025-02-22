// THIS TOPIC IS ALSO VALID AND THE SAME FOR PROCESS SYNCHRONIZATION

/*

Basically std::promise is sent to the called thread and
once the value is ready, we set that value in promise object,
now at calling thread side we can get that value using std::future object
which was created using std::promise object before sending it to the called thread.
And this is how we receive value from one thread to another in synchronisation.

instructions:
    1. create a promise object.
    2. create a future object using the promise object's get_future() method.
    3. move the promise object to the thread (we dont need it in the main).
    4. set the promise object value in the thread using its set_value() method.
    5. in the main, get the value from the future object using its get() method.
        NOTE: get() method of the future object is blocking call. It means that
              it will wait until the set_value() finished in the promise object.

CAUTION:
    Once you call set_value() on a promise, you cannot set another value without reinitializing the promise.
    Each time you reinitialize the promise, you must call get_future() on it before using get() on the future.
*/

#include <future>
#include <iostream>
#include <thread>
#include <vector>

typedef unsigned long long ull;

void sumOdds(std::promise<ull>* sum_promise, ull start, ull end) {
  int count = 10;

  while (--count) {
    ull sum = 0;

    std::cout << "calculating started..." << std::endl;
    for (ull i = start; i <= end; i++) {
      if (i & 1) sum += i;
    }
    std::cout << "calculating finished..." << std::endl;

    sum_promise->set_value(sum);
  }
}

int main() {
  ull start = 0;
  ull end = 1'900'000'000;

  std::promise<ull> sum;
  std::future<ull> sum_future = sum.get_future();

  std::cout << "Thread Created!" << std::endl;
  std::thread t(sumOdds, &sum, start, end);

  int count = 10;

  while (--count) {
    std::cout << "Waiting for the next result..." << std::endl;
    std::cout << "Sum: " << sum_future.get() << std::endl;
    std::vector<int> a;
    std::cout << &a << std::endl;
    a.push_back(1);
    std::cout << &a << std::endl;
    sum = std::promise<ull>{};
    sum_future = sum.get_future();
  }

  t.join();
  std::cout << "Completed!" << std::endl;

  return EXIT_SUCCESS;
}