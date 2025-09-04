#include "examplelib/core.h"

#include <print>

int main() {
    const char* message = examplelib::core::getinfo();
    std::println("{}", message);
    return 0;
}
