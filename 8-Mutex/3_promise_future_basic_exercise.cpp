#include <iostream>
#include <future>
#include <thread>
#include <chrono>

class Device{
    public:
    void Run(){
        running = true;
        while(running){
            temp = std::promise<float>();   // need to be reinitialized to promise new value
            current += 0.3f;
            //std::this_thread::sleep_for(std::chrono::milliseconds(400));
            if(current > 30){
                temp.set_exception(
                    std::make_exception_ptr(
                        std::runtime_error{"Temperature too high: " + std::to_string(current) + " *C"}
                    )
                );
            }else
                temp.set_value(current);
        }
    }
    void Stop() { 
        std::cout << "[Device] shutting down..." << std::endl;
        running = false;
    }
    
    std::promise<float> temp;

    private:
    bool running{false}; 
    float current{25.0f};
};

class System{
    public:
    void Run(std::promise<float>* temp){
        running = true;
        while(running){
            reading = temp->get_future();
            try {
                float value = reading.get(); // Get the value from the future
                std::cout << "[System] device sensor is " << value << " *C" << std::endl;
            }catch (const std::runtime_error& e) {
                std::cerr << "[System] Emergency shutdown: " << e.what() << std::endl;
                connected_device->Stop();
                Stop();
            }catch (const std::future_error& e) {
                std::cerr << "[System] future error: " << e.what() << std::endl;
                break;
            }
        }
    }
    void Stop() { running = false; }
    void ConnectDevice(Device* device){ connected_device = device; }

    private:
    bool running{false};
    Device* connected_device;
    std::future<float> reading;
};

int main(){
    Device d;
    System m;
    m.ConnectDevice(&d);

    std::thread device_thread{&Device::Run, &d};
    std::thread monitor_thread{&System::Run, &m, &(d.temp)};

    device_thread.join();
    monitor_thread.join();
    return 0;
}