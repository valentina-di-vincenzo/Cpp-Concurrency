#include <mutex>
#include <queue>

/* The simplest thread-safe queue, using just raw mutex ( no lock_guard ); Check "3 | Thread Safe Queue.h" for a better version.
 * To implement: isEmpty(), getSize()
 * How to use it: #include "2 | Thread Safe Queue (dummy).h" and then use an instance of threadSafe_queue as a normal queue
*/

class threadSafe_queue {

    std::queue<int> rawQueue; // shared structure between all threads
    std::mutex m; // rawQueue's red door

public:

    int& retrieve_and_delete() {
        int front_value = 0; // if empty return 0
        m.lock();
        // From now on, the current thread is the only one that can access rawQueue
        if( !rawQueue.empty() ) {
            front_value = rawQueue.front();
            rawQueue.pop();
        }
        m.unlock();
        // other threads can lock the mutex now
        return front_value;
    };

    void push(int val) {
        m.lock();
        rawQueue.push(val);
        m.unlock();
    };

};
