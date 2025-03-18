#include "render.h"
#include <iostream>
#include <chrono>
#include <fstream>
#include <thread>
#include "readUART.h"
#include <mutex>
#include <cmath>  // Do obliczeń matematycznych (np. M_PI)
#include <X11/Xlib.h>
#include "robot.h"

inputData input;
std::mutex inputMutex; // Mutex dla dostępu do zmiennej input

const float maxInputValue = 1000.0f;
const float twoPi = 2.0f * M_PI; // Pełny obrót w radianach
const float changeThreshold = 0.5f; // Próg tolerancji, poniżej którego ignorujemy zmiany

float convertToRadians(float value) {
    return (value / maxInputValue) * twoPi;
}

bool isChangeSignificant(float newVal, float oldVal) {
    return std::abs(newVal - oldVal) > changeThreshold;
}

// void renderLoop(int ID) {
//     inputData tempInput;9
//
//     render render(1500, 1500, files.at(0));
//     render.setOffsets(1.0f, 1.0f, 20.0f);
//     render.setParam(0.1f, 100.0f, 90.0f);
//     render.setScale(1.9f);
//     // render render(1000, 1000, "-");
//     int ctr = 0;
//
//     float lastX = M_PI / 4, lastY = M_PI / 4, lastZ = 0; // Przechowywanie poprzednich wartości
//
//     while (true) {
//         {
//             std::lock_guard<std::mutex> lock(inputMutex); // Blokuj dostęp do input
//             tempInput = input; // Skopiowanie danych wejściowych
//         }
//
//         // Ignorowanie małych zmian
//         if (isChangeSignificant(tempInput.x, lastX) ||
//             isChangeSignificant(tempInput.y, lastY) ||
//             isChangeSignificant(tempInput.z, lastZ) || ctr == 0) {
//             // Zamiana wartości na kąty w radianach
//             float radX = convertToRadians(tempInput.x);
//             float radY = convertToRadians(tempInput.y);
//             float radZ = convertToRadians(tempInput.z);
//
//             render.render2Dview(lastX, lastY, lastZ); // Przekazywanie kątów w radianach do rendera
//
//             // Aktualizacja poprzednich wartości
//             lastX = tempInput.x;
//             lastY = tempInput.y;
//             lastZ = tempInput.z;
//         }
//         ctr++;
//     }
// }

// void uartLoop(int ID) {
//     std::string data;
//
//     // Wyszukaj dostępne porty UART
//     std::vector<std::string> uartPorts = readUART::findUARTPorts();
//
//     // Nazwa portu
//     const char *portName = uartPorts.at(0).c_str();
//
//     // Konfiguracja UART
//     int uartFD = readUART::configureUART(portName);
//
//     while (true) {
//         try {
//             data = readUART::readFromUART(uartFD);
//         } catch (const std::exception &e) {
//             // Obsługuje wyjątki
//         }
//
//         if (!data.empty()) {
//             inputData newInput = readUART::getInputData(data); {
//                 std::lock_guard<std::mutex> lock(inputMutex); // Blokuj dostęp do input
//                 input = newInput; // Aktualizuj dane wejściowe
//             } // Mutex zostanie automatycznie odblokowany po zakończeniu tego zakresu
//             // std::cout << "Otrzymano: " << input.x << ", " << input.y << ", " << input.z << std::endl;
//         }
//     }
// }

int main() {
    robot robot;

    robot.run();

    // std::thread renderThread (renderLoop, 0);
    // std::thread uartThread(uartLoop, 1);

    // uartThread.join();
    // renderThread.join();

    return 0;
}
