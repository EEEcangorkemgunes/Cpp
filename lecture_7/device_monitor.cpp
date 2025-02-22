#include <chrono>
#include <future>
#include <iostream>
#include <thread>

//
class System {
 public:
  void Run() {
    running = true;
    while (running) {
      std::cout << "System is running" << std::endl;
    }
  }
  void Stop() { running = false; }

 private:
  Device* device;
  Monitor* monitor;
  bool running{false};
};

class Device {
 public:
  void Run() {
    running = true;
    float current = 25.0f;
    while (running) {
    }
  }
  void Stop() { running = false; }

  void SetTemperature(float value) { temp.set_value(value); }
  void GetTemperature() { temp.get_future(); }
  std::promise<float> temp;

 private:
  bool running{false};
  float temperature{25.0f};
};

class Monitor {
 public:
  void Run(std::promise<float>* temp) {
    running = true;
    while (running) {
    }
  }
  void Stop() { running = false; }

  bool running{false};
  std::future<float> reading;
};

int main() {
  System s;
  Monitor m;
  Device d;

  return 0;
}