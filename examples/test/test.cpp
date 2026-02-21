#include <jet.h>

#include <iostream>

int main() {
    if (!jet::initialize()) {
        std::cout << "Failed to initialize Jet!\n";
        return -1;
    }

    jet::Window* window = jet::initWindow({});

    jet::deinitWindow(window);
    jet::shutdown();
}
