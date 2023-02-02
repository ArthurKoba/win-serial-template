//
// Created by Koba on 02.02.2023.
//

#ifndef WIN_SERIAL_TEMPLATE_SERIAL_H
#define WIN_SERIAL_TEMPLATE_SERIAL_H

#include <windows.h>
#include <iostream>
#include <cstdint>
#include <chrono>
#include <thread>

#ifndef SERIAL_PORT
    #define SERIAL_PORT "\\\\.\\COM1"
#endif

using namespace std;

enum SerialBeginResult : uint8_t {
    OK, NO_FIND, SOME_ERROR
};

class HardwareSerial {
public:
    HardwareSerial();
    ~HardwareSerial();
    SerialBeginResult begin(char *port, uint32_t baudRate);
    size_t write(const char *data, size_t size);
    size_t print(const char *data);
    size_t println(const char *data);
    char readByte();
private:
    [[noreturn]] void static reader();
    HANDLE handle = nullptr;
    thread *readerThread = nullptr;
};

#endif //WIN_SERIAL_TEMPLATE_SERIAL_H
