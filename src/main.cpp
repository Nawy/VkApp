#include <iostream>
#include <stdexcept>
#include "CVulkanBase.hpp"

int main() {

    CVulkanBase app(800, 600);

    try {
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}