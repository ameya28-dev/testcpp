#include <chrono>
struct Timer {
    using Clock = std::chrono::high_resolution_clock;
    using TimePoint = std::chrono::time_point<Clock>;

    void start() { m_start = Clock::now(); }
    void stop() { m_stop = Clock::now(); }

    double get_seconds() const {
        using namespace std::chrono;
        return duration_cast<seconds>(m_stop - m_start).count() * 1.0f;
    }

    double get_milliseconds() const {
        using namespace std::chrono;
        return duration_cast<milliseconds>(m_stop - m_start).count() * 1.0f;
    }

    operator double() const { return get_seconds(); }

   private:
    TimePoint m_start, m_stop;
};

int main() {
    Timer timer;
    timer.start();
    timer.stop();

    Timer timer2;
    timer2.start();
    timer2.stop();

    double time = timer2 + timer;
}