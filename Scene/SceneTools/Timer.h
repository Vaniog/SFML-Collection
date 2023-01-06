#pragma once
#include <iostream>
#include <chrono>

class Timer {
public:
    Timer();
    /// update delta_time and time
    void Update();
    /// \return time, passed between last two updates;
    [[nodiscard]] uint64_t GetDelta() const;
    /// \return time, passed from timer start
    [[nodiscard]] uint64_t GetTime() const;
private:
    std::chrono::time_point<std::chrono::steady_clock> start_time_;
    std::chrono::time_point<std::chrono::steady_clock> last_update_time_;
    std::chrono::microseconds delta_time_;
};