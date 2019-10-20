#include <queue>
#include <thread>
#include <iostream>

/* THE QUEUE PROBLEM #1
 * Two threads (A and B) read the front value of a queue and pop it immediately after.
 * [ Q ] : Do the two threads cumulatively always retrieve all the elements of the queue?
 */

void retrieve_and_delete(std::queue<int>& rawQueue, std::string threadName) {
    if( !rawQueue.empty() ) {
        std::string out = "[ " + threadName + " ] front " + std::to_string(rawQueue.front());
        rawQueue.pop();
        out += " | new front " + std::to_string(rawQueue.front())  + "\n";
        std::cout << out;
    }
}

int main() {
    std::queue<int> rawQueue;

    // queue 0 to 19
    for ( int i = 0; i < 20; i++) {
        rawQueue.push(i);
    }

    // two threads reading the front value and popping it immediately after
    for ( int i = 0; i < 10; i++) {
        std::thread tA(retrieve_and_delete, std::ref(rawQueue), "A");
        std::thread tB(retrieve_and_delete, std::ref(rawQueue), "B");
        tA.join();
        tB.join();
    }

}

/* [ A ] : No, they don't.
 *
 * POSSIBLE OUTPUT:
 * [ A ] front 0 | new front 2
 * [ B ] front 0 | new front 1
 * [ .... ]
 *
 * As you can see thread B reads 0 and pops 0 (new front is 1), but thread A reads 0 and pops 1 (new front is 2).
 * 1 is deleted, but never retrieved.
*/
