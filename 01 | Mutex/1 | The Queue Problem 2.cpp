#include <queue>
#include <deque>
#include <thread>
#include <iostream>

/* THE QUEUE PROBLEM #2
 * Six threads ( A to F ) push values ( 1 to 6 ) in a queue.
 * [ QUESTION ] : Can you say why sometimes there is an element = 0 (value never pushed) ?
 */

void pushValue(std::queue<int>& rawQueue, int value) {
    std::string out = "Pushing " + std::to_string(value) + " | size before: " + std::to_string(rawQueue.size());
    rawQueue.push(value);
    out += "\tafter: " + std::to_string(rawQueue.size()) + "\n";
    std::cout << out;
}

int main() {
    std::queue<int> rawQueue;

    std::thread tA(pushValue, std::ref(rawQueue), 1);
    std::thread tB(pushValue, std::ref(rawQueue), 2);
    std::thread tC(pushValue, std::ref(rawQueue), 3);
    std::thread tD(pushValue, std::ref(rawQueue), 4);
    std::thread tE(pushValue, std::ref(rawQueue), 5);
    std::thread tF(pushValue, std::ref(rawQueue), 6);
    tA.join();
    tB.join();
    tC.join();
    tD.join();
    tE.join();
    tF.join();

    std::cout << std::endl << "Size of the queue: " + std::to_string(rawQueue.size()) << std::endl;
    std::cout << "Elements in the queue: " << std::endl;
    // in the queue there should be 1, 2, 3, 4, 5, 6 in any order
    for ( int i = 0; !rawQueue.empty() ; i++ ) {
        std::cout << std::to_string(rawQueue.front()) << std::endl;
        rawQueue.pop();
    }

}

/* [ ANSWER ] : Let's suppose thread A pushes 1 and at the same time thread E pushes 5 overwriting 1.
 *    Now there is just one element in the queue (5), even if two pushes actually occurred increasing the size
 *    by one each.
 *    The next pushed element is written in the size+1 position, leaving a free spot marked with 0, the default
 *    initialization value.
 *
 *    N.B: It can also happen a final size < 6 or some odd error. To explain this, remember that also the increasing
 *    operation is not atomic ( size++ "equals" to tmp = size + 1; size = tmp; ).
 */
