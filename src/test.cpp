#include <iostream>
#include <vector>
#include <array>
#include "vector.hpp"

int main() {
    ASC::Vector<int, 5> vec1 = {1,2,3,4,5};
    ASC::Vector<int, 5> vec2 = {2,3,4,5,6};
    ASC::Vector<int, 5> vec3 = vec1 + vec2;

    std::cout << vec1 << std::endl;
    std::cout << vec2 << std::endl;
    std::cout << vec3 << std::endl;
    std::cout << vec1.size() << std::endl;
    std::cout << vec2.size() << std::endl;
    std::cout << vec3.size() << std::endl;
    return 0;
}