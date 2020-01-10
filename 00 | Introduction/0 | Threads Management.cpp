/* BASIC THREAD MANAGEMENT
 * 1. Create threads with three different callable objects (a function newValue, a lambda expression and a class operator)
 * 2. Use of join and detach methods
 * 3. Pass a ref value as argument
 */

#include <iostream>
#include <thread>
#include <vector>
#include <string>


void newValue(int& value) {
    value = 2;
    std::string out = "[newValue] t0 new value: " + std::to_string(value) +" \n";
    std::cout << out;
}

class workClass {
public:
    void operator() (){
        std::string out = "[operator] t1 running\n";
        std::cout << out;
    };
};
int main() {
    std::cout << "Main thread running" << std::endl;
    std::vector<std::thread> detachPool;

    int value = 5;
    std::string value_out = "[main] \told value: " + std::to_string(value);
    std::thread t0(newValue, std::ref(value));
    //t0 must terminate before inspecting the new value
    t0.join();
    value_out += "\tnew value: " + std::to_string(value) + "\n";
    std::cout << value_out;

    std::thread t1{ workClass() };
    detachPool.push_back(std::move(t1));

    std::thread t2( []() {
             std::string out = "[lambda] t2 running\n";
            std::cout << out; });
    detachPool.push_back(std::move(t2));

    for( std::thread& t : detachPool ) {
        t.detach();
    }
    std::string out = "Main thread exits\n";
    std::cout << out;
    return 0;
}
