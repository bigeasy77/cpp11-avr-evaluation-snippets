#include <cstdint>
#include <limits>

void __vector_1(void) __attribute__((interrupt)); 

class comm
{
    public:
        comm():rx_data(0U), 
               is_rx(false) {}
        ~comm() {}

        template<typename unsigned_t>
        bool send_data(const unsigned_t& data) const
        {
            static_assert(false == std::numeric_limits<unsigned_t>::is_signed, 
                            "type must be unsigned");

            const std::size_t count = std::numeric_limits<unsigned_t>::digits / 8;
            
            std::size_t it; 
            for(it = 0U; it < count; it++)
            {
                const std::uint8_t byte = data >> (it * 8U);
                if(!send_byte(byte))
                {
                    break;
                }
            }
            return (it == count);
        }

        bool receiver_ready() const { return is_rx; }

        std::uint8_t receive_byte()
        {
            if (is_rx)
            {
                is_rx = false;
                return rx_data;
            }
            return 0U;
        }

    private:
        static constexpr std::uint8_t tx_buf = 0xAAU;
        static constexpr std::uint8_t rx_buf = 0xABU;

        std::uint8_t rx_data;
        bool is_rx;

        comm(const comm&) = delete;
        const comm& operator=(const comm&) = delete;

        bool send_byte(const std::uint8_t byte) const
        {
            *reinterpret_cast<volatile std::uint8_t *>(tx_buf) =
                byte;
            return true;
        }

        friend
        void comm_rx_isr(); 
};

namespace
{
    comm com;
}

void comm_rx_isr() 
{
    com.rx_data = 
        *reinterpret_cast<volatile std::uint8_t*>(comm::rx_buf);
    com.is_rx = true;
}

void __vector_1(void)
{
    comm_rx_isr();
}

int main()
{
    constexpr std::uint16_t word = 0xFFFFU;
    //constexpr int word = 0xFFFFU; //error

    com.send_data(word);
}
