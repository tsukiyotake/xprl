#include <iostream>
#include <array>

#include <xprl/enumerate.hpp>
#include <xprl/zip.hpp>

int main() {

    std::cout << "zip test" << std::endl;
    std::array values = {1, 3, 4, 5, 6};
    for (auto const& [x, y]: xprl::zip(values, values)) {
        std::cout << x << ", " << y << std::endl;
    }
    std::cout << std::endl;

    std::cout << "enumerate test" << std::endl;
    for (auto const& [i, x]: xprl::enumerate(values)) {
        std::cout << i << ", " << x << std::endl;
    }
    std::cout << std::endl;

    auto copy = values;
    for (auto& [x, y]: xprl::zip(copy, values)) {
        x += y;
    }

    for (auto const& [x, y]: xprl::zip(copy, values)) {
        std::cout << x << ", " << y << std::endl;
    }
    std::cout << std::endl;

    return 0;
}
