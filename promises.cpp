#include <iostream>
#include <future>
#include <thread>
#include <chrono>
#include <condition_variable>
#include <atomic>

std::mutex reading_mutex;
std::condition_variable reading_ready_condition;

class Device {
public:
    Device() : power_on{true}, running{false}, current_reading{25.0f} {
        std::cout << "[Device] Powered up..." << std::endl;
        sensor_thread = std::thread{&Device::UpdateTemp, this};
    }
    ~Device() {
        power_on = false;
        std::cout << "[Device] Powered down..." << std::endl;
        if (sensor_thread.joinable())
            sensor_thread.join();
    }

    // Method to start the device's operation
    void Run() {
        running = true;
        std::cout << "[Device] Is started..." << std::endl;
        running_time = 0;
        while (running) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            ++running_time;
        }
    }

    // Method to stop the device
    void Stop() {
        std::cout << "[Device] Is stopped... "
                  << "run-time: " << running_time << " ms" << std::endl;
        running = false;
    }

    bool IsRunning() const { return running; }

    // Method to get the latest temperature future
    std::shared_ptr<std::future<float>> GetTemperatureFuture() {
        std::lock_guard<std::mutex> lock(reading_mutex);
        return std::make_shared<std::future<float>>(temp_sensor.get_future());
    }

private:
    std::atomic_bool power_on;
    std::atomic_bool running;
    unsigned int running_time;
    float current_reading;
    std::thread sensor_thread;
    std::promise<float> temp_sensor;

    // Method to update the temperature
    void UpdateTemp() {
        while (power_on) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            if (running) current_reading += 0.3f;
            else if (current_reading > 25.0f) current_reading -= 0.1f;

            std::lock_guard<std::mutex> lock(reading_mutex);
            
            if (current_reading > 30) {
                temp_sensor.set_exception(
                    std::make_exception_ptr(
                        std::runtime_error{"Temperature too high: " + std::to_string(current_reading) + " *C"}
                    )
                );
            } else {
                temp_sensor.set_value(current_reading);
            }

            reading_ready_condition.notify_one();
        }
    }
};

class System {
public:
    System() : running{false}, emergency_counter{0} {
        std::cout << "[System] Powered up..." << std::endl;
    }
    ~System() {
        std::cout << "[System] Powered down..." << std::endl;
    }

    void Run() {
        running = true;
        std::cout << "[System] Turning on..." << std::endl;

        while (running) {
            std::unique_lock<std::mutex> ul{reading_mutex};
            reading_ready_condition.wait(ul);

            // Get the latest temperature reading
            std::shared_ptr<std::future<float>> future = connected_device->GetTemperatureFuture();
            
            try {
                float value = future->get();
                std::cout << "[System] device sensor is " << value << " *C" << std::endl;
                if (value <= 28 && !connected_device->IsRunning()) {
                    device_thread = std::thread{&Device::Run, connected_device};
                }
            }
            catch (const std::runtime_error& e) {
                std::cerr << "[System] Emergency shutdown: " << e.what() << std::endl;
                ++emergency_counter;
                connected_device->Stop();
                
                if (device_thread.joinable())
                    device_thread.join();
                
                if (emergency_counter >= 3)
                    Stop();
            }
            catch (const std::future_error& e) {
                std::cerr << "[System] future error: " << e.what() << std::endl;
                break;
            }
        }
    }

    void Stop() {
        std::cout << "[System] Turning off..." << std::endl;
        running = false;
    }

    void ConnectDevice(Device* device) { 
        connected_device = device; 
    }

private:
    bool running;
    Device* connected_device;
    std::thread device_thread;
    int emergency_counter;
};

int main() {
    System system;
    Device device;

    system.ConnectDevice(&device);
    system.Run();

    return 0;
}
