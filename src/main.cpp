#include <iostream>
#include "serial.h"

using namespace std;

void testDestructor() {
    cout << "Start testDestructor" << endl;

    cout << "End testDestructor" << endl;
}


int main() {
    testDestructor();
    return 0;
}
