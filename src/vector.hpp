#include <iostream>
#include <vector>
#include <type_traits>
#include <initializer_list>

namespace ASC {
    template<class value_type, std::size_t number_of_elements>
    class Vector;

    template<class type, std::size_t size>
    std::ostream& operator<<(std::ostream&, ASC::Vector<type, size>&);

    template<class value1, class value2, std::size_t num1, std::size_t num2,
    std::enable_if_t<std::is_arithmetic_v<value1>, bool> = true,
    std::enable_if_t<std::is_arithmetic_v<value2>, bool> = true,
    std::enable_if_t<num1 == num2,                 bool> = true>
    Vector<value1, num1> operator+(Vector<value1, num1> lhs, Vector<value2, num2>& rhs);

    // todo determine whether or not vectors and subsequently matrices should be fixed size using templates at compile time
    template<class value_type, std::size_t number_of_elements>
    class Vector {
        private:
        std::vector<value_type> data;

        public:
        Vector(): data(std::vector<value_type>(number_of_elements)) {}

        Vector(Vector const &other) : data(other.data) {}

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

        template<class value, std::size_t num,
        std::enable_if_t<std::is_arithmetic_v<value_type>, bool> = true,
        std::enable_if_t<std::is_arithmetic_v<value>,      bool> = true,
        std::enable_if_t<number_of_elements == num,        bool> = true>
        Vector<value_type, number_of_elements>& operator+=(Vector<value, num>& other) {
            for (std::size_t i = 0; i < number_of_elements; i++) {
                (*this)[i] += other[i];
            }
            return *this;
        }

        friend Vector operator+ <> (Vector lhs, Vector& rhs);

        // template<typename value,
        // std::enable_if_t<std::is_arithmetic_v<value_type>, bool> = true,
        // std::enable_if_t<std::is_arithmetic_v<value>, bool> = true>
        // // std::enable_if_t<number_of_elements == num, bool> = true>
        // Vector<value_type, number_of_elements> operator+(Vector<value, number_of_elements>& other) {
        //     Vector<value_type, number_of_elements> ret;
        //     for (std::size_t i = 0; i < number_of_elements; i++) {
        //         ret[i] = this->operator[](i) + other[i];
        //     }
        //     return ret;
        // }

        friend std::ostream& operator<< <> (std::ostream&, Vector&);
    };
    
    template<class type, std::size_t size>
    std::ostream& operator<<(std::ostream& o, ASC::Vector<type, size>& vec) {
        o << "<";
        for (std::size_t i = 0; i < vec.size(); i++) {
            o << vec[i] << (i != vec.size() - 1 ? ", " : "");
        }
        o << ">";
        return o;
    }

    template<class value1, class value2, std::size_t num1, std::size_t num2,
    std::enable_if_t<std::is_arithmetic_v<value1>, bool>,
    std::enable_if_t<std::is_arithmetic_v<value2>, bool>,
    std::enable_if_t<num1 == num2,                 bool>>
    Vector<value1, num1> operator+(Vector<value1, num1> lhs, Vector<value2, num2>& rhs) {
        lhs += rhs;
        return lhs;
    }
};
