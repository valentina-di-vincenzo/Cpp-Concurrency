#include <mutex>
#include <queue>

/* The simplest thread-safe queue, using lock_guard
 * To implement: isEmpty(), getSize()
 * How to use it: #include "3 | Thread Safe Queue.h" and then use an instance of threadSafe_queue as a normal queue
*/

class threadSafe_queue {

    std::queue<int> rawQueue; // shared structure between all threads
    std::mutex m; // rawQueue's red door

public:

    int& retrieve_and_delete() {
        int front_value = 0; // if empty return 0
        std::lock_guard<std::mutex> lg(m);
        // From now on, the current thread is the only one that can access rawQueue
        if( !rawQueue.empty() ) {
            front_value = rawQueue.front();
            rawQueue.pop();
        }
        return front_value;
    };  // other threads can lock the mutex now

    void push(int val) {
        std::lock_guard<std::mutex> lg(m);
        // from now on, the current thread is the only one that can access rawQueue
        rawQueue.push(val);
    }; // other threads can lock the mutex now
};
