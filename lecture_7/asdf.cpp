#include <iostream>
#include <future>
#include <thread>
#include <chrono>

class Device{
    public:
    void Run(){
        running = true;
        while(running){
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            current += 0.3f;
            temp = std::promise<float>();   // need to be reinitialized to promise new value
            if(current > 30){
                temp.set_exception(std::make_exception_ptr(std::runtime_error("Temperature too high: " + std::to_string(current) + " *C")));
            }else
                temp.set_value(current);
        }
    }
    void Stop() { running = false; }
    // void Temprature(){
    //     if(running) 
    //     else current -= 0.3f;

    // }
    std::promise<float> temp;

    private:
    bool running{false}; 
    float current{25.0f};
};

class Monitor{
    public:
    void Run(std::promise<float>* temp){
        reading = temp->get_future();
        running = true;
        while(running){
            try {
                float value = 1.0;//reading.get(); // Get the value from the future
                std::cout << "[Monitor] device sensor is " << value << " *C" << std::endl;

            }catch (const std::runtime_error& e) {
                std::cerr << "[Monitor] Emergency shutdown: " << e.what() << std::endl;
                device_to_monitor->Stop();
            }catch (const std::future_error& e) {
                std::cerr << "[Monitor] future error: " << e.what() << std::endl;
                device_to_monitor->Stop();
                break;
            }
        }
    }
    void Stop() { running = false; }

    bool running{false};
    Device* device_to_monitor;
    std::future<float> reading;
};

int main(){
    Device d;
    Monitor m;
    m.device_to_monitor = &d;

    std::thread device_thread{&Device::Run, &d};
    std::thread monitor_thread{&Monitor::Run, &m, &(d.temp)};

    device_thread.join();
    monitor_thread.join();
    return 0;
}