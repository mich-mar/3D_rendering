#include "render.h"
#include <iostream>
#include <chrono>
#include <thread>

int main() {
    render render(1000,1000,"Seahawk.obj");
    // render render(1000,1000,"-");
    render.setOffsets(1.0f,1.0f,200.0f);
    render.setParam(0.1f,1000.0f,90.0f);
    render.setScale(0.9f);

    while (true) {
        // std::this_thread::sleep_for(std::chrono::milliseconds(10));
        render.render2Dview();
    }

    return 0;
}
