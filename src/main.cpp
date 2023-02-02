#include <iostream>
#include "serial.h"

using namespace std;

void testDestructor() {
    cout << "Start testDestructor" << endl;
    Serial serial;
    cout << "End testDestructor" << endl;
}


int main() {
    testDestructor();
    return 0;
}
