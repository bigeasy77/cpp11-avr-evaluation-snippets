#include <cstdint>
#include <array>
#include <limits>
#include <algorithm>
#include <atomic>

constexpr uint32_t ver = 3.0F;
static_assert(ver >= 3U, "Version is too low");

namespace
{
    //avr stdlibc++ lacks __atomic_load_4
    //volatile std::atomic<std::uint32_t> system_tick;
    volatile std::atomic<std::uint8_t> system_tick;

    typedef std::uint32_t cnt_t;
    std::array<cnt_t, 4U> counters;
    
    std::array<int, 3U> u
    {
        {1, 2, 3}
    };
    std::array<int, 3U> v
    {
        {2, 3, 4}
    };
}

std::uint32_t get_system_time()
{
    return std::atomic_load(&system_tick);
}

void fill_counters()
{
    std::fill(counters.begin(),
              counters.end(),
              std::numeric_limits<cnt_t>::max());
}

void alter_counters()
{
    std::for_each(counters.begin(), 
                  counters.end(), 
                  [](cnt_t& c){ c+=0x30; });
}

int get_inner_product()
{
    return
    std::inner_product(u.begin(), 
                       u.end(),
                       v.begin(),
                       0); //accumulator init
}

int main()
{
    get_system_time(); 
    fill_counters();
    //if (is_clean_counter_set())
    //{
    //    return get_inner_product();
    //}
}

