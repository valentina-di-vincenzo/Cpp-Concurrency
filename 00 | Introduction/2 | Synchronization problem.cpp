/* SYNCHRONIZATION PROBLEM
* After thread A evaluates "value" as true, thread B changes it. Now we are inside an if-block, even if the constraint has been violated. 
* If two threads access the same data, one writing and one reading, there is no guarantee on which operation is executed first. 
* Accesses must be synchronized.
*/

#include <thread>
#include <iostream>
#include <string>

void runA(bool& value, int i) {
  if(value) {
      //value should always be 1
      std::string out = "[ " + std::to_string(i) + " ] value " + std::to_string(value)  + "\n";
      std::cout << out;
  }
}

void runB(bool& value) {
    value = false;
}

int main() {
    for(int i = 0; i < 20; i++) {
        bool value = true; //1
        std::thread tA(runA, std::ref(value), i);
        std::thread tB(runB, std::ref(value));
        tA.join();
        tB.join();
    }
}
