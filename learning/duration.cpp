#include <algorithm>
#include <chrono>
#include <functional>
#include <future>
#include <iomanip>
#include <iostream>
#include <memory>
#include <mutex>
#include <random>
#include <string>
#include <thread>
#include <tuple>
#include <type_traits>
#include <utility>
#include <variant>

class Random {
public:
    Random() : _generator(std::random_device{}()), _distribution(500, 5000) {}

    int get() {
        return _distribution(_generator);
    }

    std::chrono::milliseconds next() {
        return std::chrono::milliseconds{get()};
    }

private:
    std::mt19937 _generator;
    std::uniform_int_distribution<> _distribution;
};

static Random random;

template <class _Rep, class _Period>
std::future<void> timer_async(std::chrono::duration<_Rep, _Period> duration, std::function<void()> callback) {
    return std::async(std::launch::async, [duration, callback]() {
        std::this_thread::sleep_for(duration);
        callback();
    });
}

class Future {
public:
    template <typename T>
    struct ExtractFutureType;

    template <typename T>
    struct ExtractFutureType<std::future<T>> {
        using type = T;
    };

    template <typename T>
    using ExtractFutureTypeT = typename ExtractFutureType<std::decay_t<T>>::type;

public:
    template <typename Rep, typename Period, typename Callable, typename... Args,
        typename = std::enable_if_t<std::is_invocable_v<Callable, Args...>>>
    static auto Delayed(std::chrono::duration<Rep, Period> duration, Callable&& callback, Args&&... args)
        -> std::future<std::invoke_result_t<Callable, Args...>> {
        using ReturnType = std::invoke_result_t<Callable, Args...>;
        return std::async(std::launch::async,
            [duration, cb = std::forward<Callable>(callback),
                tupArgs = std::make_tuple(std::forward<Args>(args)...)]() mutable -> ReturnType {
                std::this_thread::sleep_for(duration);
                return std::apply(
                    [&cb](auto&&... unpackedArgs) {
                        return std::invoke(std::move(cb), std::forward<decltype(unpackedArgs)>(unpackedArgs)...);
                    },
                    std::move(tupArgs));
            });
    }

    template <typename... Futures>
    static auto Wait(Futures&&... futures) -> std::future<std::tuple<ExtractFutureTypeT<Futures>...>> {
        auto futureTuple = std::make_tuple(std::forward<Futures>(futures)...);
        return std::async(std::launch::async, [futs = std::move(futureTuple)]() mutable {
            return std::apply([](auto&... f) { return std::make_tuple(f.get()...); }, futs);
        });
    }

    template <typename... Futures>
    static auto Any(Futures&&... futures) {
        using ReturnVariant = std::variant<ExtractFutureTypeT<Futures>...>;

        auto promise  = std::make_shared<std::promise<ReturnVariant>>();
        auto doneFlag = std::make_shared<std::once_flag>();

        auto startRace = [promise, doneFlag](auto&& fut) {
            std::thread([f = std::move(fut), promise, doneFlag]() mutable {
                auto result = f.get(); // Blocks until this task completes

                std::call_once(*doneFlag, [&]() { promise->set_value(ReturnVariant(std::move(result))); });
            }).detach();
        };

        (startRace(std::forward<Futures>(futures)), ...);
        return promise->get_future();
    }
};

int add(int a, int b) {
    return a + b;
}

struct Multiplier {
    int operator()(int a, int b) const {
        return a * b;
    }
};

struct Timer {
    Timer() {
        _start = std::chrono::steady_clock::now();
    }

    ~Timer() {
        auto _end = std::chrono::steady_clock::now();
        std::cout << "Duration in milliseconds = "
                  << std::chrono::duration_cast<std::chrono::milliseconds>(_end - _start).count() << '\n';
    }

private:
    std::chrono::time_point<std::chrono::steady_clock> _start;
};

void wait() {
    Timer t{};
    auto fut1 = Future::Delayed(random.next(), []() { return 100; });
    auto fut2 = Future::Delayed(random.next(), []() { return std::to_string(1231); });
    auto fut3 = Future::Delayed(random.next(), [](){std::cout << "Done!!\n";});

    auto futures       = Future::Wait(std::move(fut1), std::move(fut2));
    auto [number, str] = futures.get();
    std::cout << "Int: " << number << ", String: " << std::quoted(str) << '\n';
}

int main() {
    using namespace std::chrono_literals;
    auto future = timer_async(13s, []() { std::cout << "Timer finished!\n"; });
    for (int i = 10; i >= 0; i--) {
        std::cout << "Processing in " << i << " seconds....\n";
        std::this_thread::sleep_for(1s);
    }

    std::string s = "Hello";
    auto concat   = [&s](const std::string& str) { return s + str; };

    std::function<void()> func = []() { std::cout << "Noice!!!\n"; };

    auto fut1 = Future::Delayed(random.next(), add, 1, 2);
    auto fut2 = Future::Delayed(random.next(), Multiplier{}, 5, 4);
    auto fut3 = Future::Delayed(random.next(), concat, " World!!");
    auto fut4 = Future::Delayed(random.next(), func);

    std::cout << fut1.get() << '\n';
    std::cout << fut2.get() << '\n';
    std::cout << fut3.get() << '\n';
    fut4.get();

    wait();
}
