#include <chrono>
#include <future>
#include <iostream>
#include <thread>
#include <unordered_map>

class Monitor {
 public:
  static void PrintWarning(const std::string& device, const float& temperature) {
    std::cout << device << "is overheating. Temperature is: " << temperature << "C. Device will be turned off." << std::endl;
  }
  static void PrintStatus(const std::string& device, const float& temperature, const bool& isRunning) {
    std::cout << device << " is " << (isRunning ? "running" : "stopped") << "Temperature is" << temperature << "C." << std::endl;
  }
};

class Device {
 public:
  std::promise<float> temp;

  Device(std::string givenName) : isRunning(false), currentTemperature(25.0f), name(givenName) {}

  void Boot() {
    isAwake = true;
    while (isAwake) {
      if (isRunning) {
        currentTemperature += static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 0.3f));
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
        if (currentTemperature > 30) {
          temp.set_exception(
              std::make_exception_ptr(std::runtime_error{"Temperature too high: " + std::to_string(currentTemperature) + " C."}));
        } else
          temp.set_value(currentTemperature);
      } else {
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
        if (currentTemperature > 25.0f) {
          currentTemperature -= static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 0.3f));
        }
        if (currentTemperature > 30) {
          temp.set_exception(
              std::make_exception_ptr(std::runtime_error{"Temperature too high: " + std::to_string(currentTemperature) + " C."}));
        } else {
          temp.set_value(currentTemperature);
        }
      }
    }
  }
  void Start() { isRunning = true; }
  void Stop() { isRunning = false; }

 private:
  std::string name;
  bool isRunning;
  bool isAwake;
  float currentTemperature;
};

class System {
 public:
  System() : isRunning(false) { inputThread = std::thread{&System::handleInput, this}; }
  ~System() {
    if (inputThread.joinable()) {
      inputThread.join();
    }
  }
  void handleDevice(Device* device) {
    std::future<float> reading;
    std::thread deviceThread{&Device::Boot, device};
  }
  void run() {
    isRunning = true;
    while (isRunning) {
      for (auto it = devices.begin(); it != devices.end(); it++) {
        if (deviceThreads.find(it->first) == deviceThreads.end()) {
          deviceThreads[it->first] = std::thread{&System::handleDevice, this, it->second};
        }
      }
      for (auto it = devices.begin(); it != devices.end(); it++) {
        
      }
    }
  }
  bool addDevice(const std::string name) {
    if (devices.find(name) != devices.end()) {
      return false;
    }
    devices[name] = new Device(name);
    return true;
  }
  void handleInput() {
    std::string input;
    while (input != "exit") {
      std::getline(std::cin, input);
    }

    isRunning = false;
  }

 private:
  std::thread inputThread;
  bool isRunning;
  std::unordered_map<std::string, Device*> devices;
  std::unordered_map<std::string, std::future<float>> readings;
  std::unordered_map<std::string, std::thread> deviceThreads;
};

int main() {
  System system;
  system.addDevice("device1");
  system.addDevice("device2");
  system.run();

  return 0;
}