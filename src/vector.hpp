#include <iostream>
#include <vector>
#include <type_traits>
#include <initializer_list>

namespace ASC {
    // todo determine whether or not vectors and subsequently matrices should be fixed size using templates at compile time
    template<typename value_type, std::size_t number_of_elements>
    class Vector {
        private:
        std::vector<value_type> data;

        public:
        Vector(): data(std::vector<value_type>(number_of_elements)) {}

        Vector(std::initializer_list<value_type> _data): data(_data) {}

        ~Vector() {
            // todo better destructor
            data.clear();
        }

        template<typename value, std::size_t num>
        Vector<value, num>& operator=(const Vector<value, num>& copy) {
            this->data = copy->data;
        }

        // todo fix equals operators
        // template<typename value, std::size_t num>
        // Vector<value, num>& operator=(const std::vector<value>& copy) {
        //     this->data = copy;
        // }

        value_type& operator[](std::size_t index) {
            return data[index];
        }

        value_type& get(std::size_t index) {
            return this->operator[](index);
        }

        constexpr std::size_t size() {
            return number_of_elements;
        }

        template<typename value,
        std::enable_if_t<std::is_arithmetic_v<value_type>, bool> = true,
        std::enable_if_t<std::is_arithmetic_v<value>, bool> = true>
        // std::enable_if_t<number_of_elements == num, bool> = true>
        Vector<value_type, number_of_elements> operator+(Vector<value, number_of_elements>& other) {
            Vector<value_type, number_of_elements> ret;
            for (std::size_t i = 0; i < number_of_elements; i++) {
                ret[i] = this->operator[](i) + other[i];
            }
            return ret;
        }

        // todo figure out a way to get rid of C/C++ 349 error on << operator (even though it compiles successfully)
        friend std::ostream& operator<<(std::ostream& o, Vector<value_type, number_of_elements>& vec) {
            o << "<";
            for (std::size_t i = 0; i < vec.size(); i++) {
                o << vec[i] << (i != vec.size() - 1 ? ", " : "");
            }
            o << ">";
            return o;
        }
    };
};