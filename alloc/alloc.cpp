#include <cstdint>
#include <new>

struct data
{
    data(int a, int b, int c): mem_1(a), mem_2(b), mem_3(c) {}
    data(): mem_1(1), mem_2(1), mem_3(1) {}
    ~data() {}
    int mem_1;
    int mem_2;
    int mem_3;
};

std::uint16_t pool[2 * sizeof(data)];

template<typename type>
type* factory_simple(void* mem)
{
    type* p = new(mem) type;
    return p;
}

template<typename type, 
         typename ...parameters>
type* factory(void* mem, parameters... params)
{
    type* p = new(mem) type(params...);
    return p;
}

int main()
{
    constexpr std::uint8_t OFFSET {2}; 

    data *dat_1 = factory_simple<data>(pool + OFFSET);
    int res = dat_1->mem_1;
    dat_1->~data();

    data *dat_2 = factory<data>(pool + OFFSET, 2, 2, 2); 
    res += dat_2->mem_1;

    return res;
}

