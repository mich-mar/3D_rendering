#include "render.h"
#include <iostream>
#include <chrono>
#include <fstream>
#include <thread>
#include "readUART.h"
#include <mutex>
#include <cmath>  // Do obliczeń matematycznych (np. M_PI)
#include <cmath>  // Do obliczeń matematycznych

inputData input;
std::mutex inputMutex;  // Mutex dla dostępu do zmiennej input

const float maxInputValue = 1000.0f;
const float twoPi = 2.0f * M_PI;  // Pełny obrót w radianach
const float changeThreshold = 0.5f;  // Próg tolerancji, poniżej którego ignorujemy zmiany

float convertToRadians(float value) {
    return (value / maxInputValue) * twoPi;
}

bool isChangeSignificant(float newVal, float oldVal) {
    return std::abs(newVal - oldVal) > changeThreshold;
}

void renderLoop(int renderThread) {
    inputData tempInput;

    render render(1000, 1000, "Seahawk.obj");
    render.setOffsets(1.0f, 1.0f, 200.0f);
    render.setParam(0.1f, 1000.0f, 90.0f);
    render.setScale(0.9f);
    // render render(1000, 1000, "-");

    float lastX = 0.0f, lastY = 0.0f, lastZ = 0.0f;  // Przechowywanie poprzednich wartości

    while (true) {
        {
            std::lock_guard<std::mutex> lock(inputMutex);  // Blokuj dostęp do input
            tempInput = input;  // Skopiowanie danych wejściowych
        }

        // Ignorowanie małych zmian
        if (isChangeSignificant(tempInput.x, lastX) ||
            isChangeSignificant(tempInput.y, lastY) ||
            isChangeSignificant(tempInput.z, lastZ)) {

            // Zamiana wartości na kąty w radianach
            float radX = convertToRadians(tempInput.x);
            float radY = convertToRadians(tempInput.y);
            float radZ = convertToRadians(tempInput.z);

            render.render2Dview(radX, radY, radZ);  // Przekazywanie kątów w radianach do rendera

            // Aktualizacja poprzednich wartości
            lastX = tempInput.x;
            lastY = tempInput.y;
            lastZ = tempInput.z;
        }
    }
}

void uartLoop(int uartFD) {
    std::string data;
    while (true) {
        try {
            data = readUART::readFromUART(uartFD);
        } catch (const std::exception &e) {
            // Obsługuje wyjątki
        }

        if (!data.empty()) {
            inputData newInput = readUART::getInputData(data);
            {
                std::lock_guard<std::mutex> lock(inputMutex);  // Blokuj dostęp do input
                input = newInput;  // Aktualizuj dane wejściowe
            }  // Mutex zostanie automatycznie odblokowany po zakończeniu tego zakresu
            // std::cout << "Otrzymano: " << input.x << ", " << input.y << ", " << input.z << std::endl;
        }
    }
}

int main() {

    // ================ UART ===================================
    // Wyszukaj dostępne porty UART
    std::vector<std::string> uartPorts = readUART::findUARTPorts();

    // Nazwa portu
    const char *portName = uartPorts.at(0).c_str();

    // Konfiguracja UART
    int uartFD = readUART::configureUART(portName);

    // Utwórz wątki dla renderowania i UART
    std::thread renderThread(renderLoop, 0);
    std::thread uartThread(uartLoop, uartFD);

    // Poczekaj na zakończenie wątków (choć w tym przypadku to nigdy nie nastąpi, ponieważ while(true))
    renderThread.join();
    uartThread.join();

    return 0;
}
