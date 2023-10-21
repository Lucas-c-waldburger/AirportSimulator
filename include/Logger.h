#ifndef AIRPORTSIMULATOR_LOGGER_H
#define AIRPORTSIMULATOR_LOGGER_H

#include <mutex>
#include <iostream>

class Logger
{
public:

    static inline void Log()
    {
        std::lock_guard<std::recursive_mutex> lock(s_mutex);
        std::cout << std::endl;
    }

    template<typename First, typename ...Rest>
    static inline void Log(First&& first, Rest&& ...rest)
    {
        std::lock_guard<std::recursive_mutex> lock(s_mutex);
        std::cout << std::forward<First>(first);
        Log(std::forward<Rest>(rest)...);
    }

private:
    static std::recursive_mutex s_mutex;

};


#endif //AIRPORTSIMULATOR_LOGGER_H
