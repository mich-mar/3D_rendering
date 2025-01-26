#include "render.h"
#include <iostream>
#include <chrono>
#include <thread>

int main() {
    render render;


    std::cout << "Hello World!" << std::endl;

    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        render.render2Dview();
    }

    return 0;
}
