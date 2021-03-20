#include <stdint.h>
#include <array>

namespace ASC {
    template<std::size_t... sizes>
    struct ndsize {
        constexpr static std::size_t size = 1;
    };
    
    template<std::size_t current_size, std::size_t... sizes>
    struct ndsize<current_size, sizes...> {
        constexpr static std::size_t size = current_size * ndsize<sizes...>::size;
    };

    template<class T, std::size_t... sizes>
    using ndarray_t = typename std::array<T, ndsize<sizes...>::size>;

    template<class T, uint8_t rank, std::size_t... dimensions>
    class NDArray {
        private:
        ndarray_t<T, dimensions...> buffer{};
        
        public:
        NDArray() : buffer() {}
    };
};