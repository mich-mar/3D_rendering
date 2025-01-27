#include "render.h"
#include <iostream>
#include <chrono>
#include <thread>

int main() {
    render render(2000,2000,"teapot.obj");
    // render render(1000,1000,"-");

    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
        render.render2Dview();
    }

    return 0;
}
