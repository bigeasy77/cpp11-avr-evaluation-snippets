#include <cstdint>
#include <tuple>


class Driver
{
    public:
    void init(){}
};

class Module
{
    public:
    void init(){}
};

class Device
{
    public:
    void init(){}
};


typedef std::tuple<Driver, Module, Device> tuple_t;
tuple_t things;

template <const unsigned N,
          const unsigned M = 0U>
struct tuple_init_each
{
    template<typename tuple_t>
    static void init(tuple_t &tpl) 
    {
        std::get<M>(tpl).init();
        tuple_init_each<N, M+1U>::init(tpl);
    }
};

template <const unsigned N>
struct tuple_init_each<N, N>
{
    template<typename tuple_t>
    static void init(tuple_t tpl) {}
};


int main()
{
    constexpr unsigned size =
        std::tuple_size<tuple_t>::value;
        
    tuple_init_each<size>::init(things);
}



