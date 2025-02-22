#include <iostream>
#include <future>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>

class Device {
public:
    void Run() {
        running = true;
        while (running) {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            std::lock_guard<std::mutex> lock(mutex);
            current += 0.3f;

            try {
                if (current > 30) {
                    promise.set_exception(
                        std::make_exception_ptr(std::runtime_error("Temperature too high: " + std::to_string(current) + " *C")));
                } else {
                    promise.set_value(current);
                }
                promise = std::promise<float>(); // Reset promise for the next value
            } catch (...) {
                // Catch unexpected exceptions (e.g., future already retrieved)
            }
        }
    }

    void Stop() {
        std::lock_guard<std::mutex> lock(mutex);
        running = false;
    }

    std::promise<float> promise;

private:
    bool running{false};
    float current{25.0f};
    std::mutex mutex;
};

class Monitor {
public:
    void Run(Device* device) {
        running = true;
        while (running) {
            try {
                std::shared_future<float> future = device->promise.get_future().share();
                float value = future.get();
                std::cout << "[Monitor] Device sensor is " << value << " *C" << std::endl;
            } catch (const std::runtime_error& e) {
                std::cerr << "[Monitor] Emergency shutdown: " << e.what() << std::endl;
                device->Stop();
                Stop();
            } catch (const std::future_error& e) {
                std::cerr << "[Monitor] Future error: " << e.what() << std::endl;
                device->Stop();
                Stop();
            }
        }
    }

    void Stop() { running = false; }

private:
    bool running{false};
};

int main() {
    Device device;
    Monitor monitor;

    std::thread deviceThread(&Device::Run, &device);
    std::thread monitorThread(&Monitor::Run, &monitor, &device);

    // Let the system run for 5 seconds and then stop
    std::this_thread::sleep_for(std::chrono::seconds(5));
    device.Stop();
    monitor.Stop();

    deviceThread.join();
    monitorThread.join();

    return 0;
}
