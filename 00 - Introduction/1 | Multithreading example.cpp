/* SHOWING THE NON-DETERMINISTIC BEHAVIOUR OF MULTITHREADING
 * Differently from a single-threaded implementation, each execution produces a different
 * and not predictable output (the only certainty is that A lines are sorted in ascending
 * order, as well as B lines).
 */

#include <thread>
#include <iostream>
#include <string>

void run(std::string threadName) {
  for (int i = 0; i < 10; i++) {
    std::string out = threadName + std::to_string(i) + "\n";
    std::cout << out;
  }
}

int main() {
  std::thread tA(run, "A");
  std::thread tB(run, "\tB");
  tA.join();
  tB.join();
}
