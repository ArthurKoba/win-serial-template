#include <iostream>
#include "serial.h"

using namespace std;

HardwareSerial Serial;

void testDestructor() {
    cout << "Start testDestructor" << endl;
    HardwareSerial serial;
    cout << "End testDestructor" << endl;
}


int main() {
//    testDestructor();
    uint32_t baudRate = 500000;
    char port[] = R"(\\.\COM30)";
    Serial.begin(port, baudRate);
    return 0;
}
