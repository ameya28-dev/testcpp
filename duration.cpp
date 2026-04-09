#include <chrono>
#include <functional>
#include <future>
#include <iostream>
#include <thread>

using namespace std::chrono_literals;

template <class _Rep, class _Period>
std::future<void> timer_async(std::chrono::duration<_Rep, _Period> duration, std::function<void()> callback) {
    return std::async(std::launch::async, [duration, callback]() {
        std::this_thread::sleep_for(duration);
        callback();
    });
}

int main() {
    auto future = timer_async(13s, []() { std::cout << "Timer finished!\n"; });
    for (int i = 10; i >= 0; i--) {
        std::cout << "Processing in " << i << " seconds....\n";
        std::this_thread::sleep_for(1s);
    }
}