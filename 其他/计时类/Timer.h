#include<bits/stdc++.h>

#ifndef TIMER_H
#define TIMER_H

template<typename TimeUnit = std::chrono::milliseconds>
class Timer {
public:
    Timer() : start(std::chrono::high_resolution_clock::now()) {}

    ~Timer() {
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << "耗时: "
            << std::chrono::duration_cast<TimeUnit>(end - start).count()
            << " " << getUnit() << std::endl;
    }

private:
    const char *getUnit() {
        if constexpr (std::is_same_v<TimeUnit, std::chrono::nanoseconds>) return "纳秒";
        else if constexpr (std::is_same_v<TimeUnit, std::chrono::microseconds>) return "微秒";
        else if constexpr (std::is_same_v<TimeUnit, std::chrono::milliseconds>) return "毫秒";
        else return "秒";
    }

    std::chrono::time_point<std::chrono::high_resolution_clock> start;
};

class MilliTimer {
public:
    MilliTimer() : start(std::chrono::high_resolution_clock::now()) {}

    void reset() {
        start = std::chrono::high_resolution_clock::now();
    }

    // 获取已过时间（不重置）
    long long elapsed() const {
        auto now = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count();
    }

    // 获取并打印时间
    void stop(const std::string &msg = "") {
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << msg << "耗时: " << duration.count() << " 毫秒" << std::endl;
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
};
#endif