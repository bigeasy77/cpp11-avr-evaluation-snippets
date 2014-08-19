#include <cstdint>

using namespace std;

namespace mcal
{
    namespace regs
    {
        //compile-time constexpr superior to define
        //pin0 to pin7 of the port
        constexpr uint8_t pinb0 = 0x1U;
        constexpr uint8_t pinb1 = 0x1U << 1U;
        constexpr uint8_t pinb2 = 0x1U << 2U;
        constexpr uint8_t pinb3 = 0x1U << 3U;
        constexpr uint8_t pinb4 = 0x1U << 4U;
        constexpr uint8_t pinb5 = 0x1U << 5U;
        constexpr uint8_t pinb6 = 0x1U << 6U;
        constexpr uint8_t pinb7 = 0x1U << 7U;

        //port b data register address
        constexpr uint8_t portb_addr = 0x25U;
    }
}

class led
{
public:
    typedef uint8_t port_t;
    typedef uint8_t pinb_t;

    led(const port_t p,
        const pinb_t b) : port(p),
                          pinb(b)
    {
        //clear only pinb bit of the value within the port address
        *reinterpret_cast<volatile port_t *>(port) &= ~pinb; 
        //set pin direction to out
        *reinterpret_cast<volatile port_t *>(port - 1U) |= pinb;        
    }

    void set_on() const
    {
        //direct memory access
        *reinterpret_cast<volatile port_t *>(port) |= pinb; 
    }

    void toggle() const
    {
        //direct memory access
        *reinterpret_cast<volatile port_t *>(port) ^= pinb; 
    }

private:
    const port_t port;
    const pinb_t pinb; 

};

template<typename port_t,
         typename pinb_t,
         port_t port,
         pinb_t pinb>
class led_opt
{
public:
    led_opt()
    {
        *reinterpret_cast<volatile port_t *>(port) &= ~pinb; 
        *reinterpret_cast<volatile port_t *>(pdir) |= pinb;        
    }

    void set_on() const
    {
        *reinterpret_cast<volatile port_t *>(port) |= pinb; 
    }

    void toggle() const
    {
        *reinterpret_cast<volatile port_t *>(port) ^= pinb; 
    }

private:
    static constexpr port_t pdir = port -1U;
};

//limit to file level (superior to static)
namespace
{
    //uniform initialization (c++11) of the constant object
    const led led_pin5
    {
        //constant folding
        mcal::regs::portb_addr, 
        mcal::regs::pinb5
    };

    //replace member variables with template parameters - known at compile time
    //max optimization
    const led_opt <uint8_t,
                   uint8_t,
                   mcal::regs::portb_addr,
                   mcal::regs::pinb5> led_opt_pin5;
}

int main()
{
    for(;;)
    {
        //led_pin5.toggle();
        //led_pin5.set_on();
        //led_opt_pin5.set_on();
        //led_opt_pin5.set_on();

        led_opt_pin5.toggle();
    }
}

