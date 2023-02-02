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
//    cout << "Start program" << endl;
    return 0;
}
