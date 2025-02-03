

#ifndef READUART_H
#define READUART_H

#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <memory>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <cstring>
#include <sstream>

struct inputData {
    float x = 0;
    float y = 0;
    float z = 0;
};

namespace virables {
    inline int baudRate = 9600;
    inline const std::string &command = "ls /dev/ttyACM*";
}

namespace readUART {

    int configureUART(const char *portName);

    std::string readFromUART(int uartFD);

    std::vector<std::string> findUARTPorts();

    inputData getInputData(const std::string &input);
}

#endif //READUART_H