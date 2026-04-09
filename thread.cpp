#include <chrono>
#include <iostream>
#include <thread>

static bool is_finished = false;

void do_work() {
    using namespace std::chrono_literals;
    while (!is_finished) {
        std::cout << "Working\n";
        std::this_thread::sleep_for(1s);
    }
}

int main() {
    std::thread worker(do_work);

    std::cin.get();
    is_finished = true;

    worker.join();
}