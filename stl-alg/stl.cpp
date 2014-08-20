#include <cstdint>
#include <array>
#include <limits>
#include <algorithm>
#include <atomic>

namespace
{
    //undefined reference to __atomic_load_4
    //volatile std::atomic<std::uint32_t> system_tick;
    
    volatile std::atomic<std::uint8_t> system_tick;
}

std::uint32_t get_system_time()
{
    return std::atomic_load(&system_tick);
}

int main()
{
   get_system_time(); 
   return 0;
}

