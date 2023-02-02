//
// Created by Koba on 02.02.2023.
//

#include "serial.h"

HardwareSerial Serial;

HardwareSerial::HardwareSerial() {
//    if (actualSerial != nullptr) return;
//    actualSerial = this;
    cout << "default handle: " << handle << endl;
    handle = new HANDLE;
    cout << "after constructor handle: " << handle << endl;
}

HardwareSerial::~HardwareSerial() {
    CloseHandle(handle);
    cout << "after destructor handle: " << handle << endl;

}

[[noreturn]] void HardwareSerial::reader() {
    while (true) {
//        cout << "New thread" << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
}

SerialBeginResult HardwareSerial::begin(char *port, uint32_t baudRate) {
    handle = CreateFile(port, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, 0);
    if (handle == INVALID_HANDLE_VALUE) {
        if (GetLastError() == ERROR_FILE_NOT_FOUND) {
            cout << "PORT" << port << " NOT FOUND\n";
            return NO_FIND;
        }
        cout << "UNKNOWN ERROR\n";
        return SOME_ERROR;
    }

    DCB serialParams = { 0 };
    serialParams.DCBlength = sizeof(serialParams);
    GetCommState(handle, &serialParams);
    serialParams.BaudRate = baudRate;
    serialParams.ByteSize = 8;
    serialParams.StopBits = ONESTOPBIT;
    serialParams.Parity = NOPARITY;
    SetCommState(handle, &serialParams);

    COMMTIMEOUTS timeout = { 0 };
    timeout.ReadIntervalTimeout = 0;
    timeout.ReadTotalTimeoutConstant = 0;
    timeout.ReadTotalTimeoutMultiplier = 0;
    timeout.WriteTotalTimeoutConstant = 50;
    timeout.WriteTotalTimeoutMultiplier = 10;
    SetCommTimeouts(handle, &timeout);
    cout << "OPEN PORT " << port << endl;
    thread tr(reader);
    tr.detach();
    return OK;
}





size_t HardwareSerial::write(const char *data, size_t size) {
    DWORD send = 0;
    OVERLAPPED osWrite = { 0 };
    osWrite.hEvent = CreateEvent(nullptr, TRUE, FALSE, nullptr);
    if (osWrite.hEvent == nullptr) {
        cout << "error creating overlapped event handle\n";
        return send;
    }
    if (WriteFile(handle, data, size, &send, &osWrite)) {
        cout << "WriteFile completed immediately.\n";
    } else if (GetLastError() == ERROR_IO_PENDING) {
        if (WaitForSingleObject(osWrite.hEvent, INFINITE) == WAIT_OBJECT_0) {
            if (!GetOverlappedResult(handle, &osWrite, &send, FALSE))
                cout << "Write operation completed not successfully...\n";
        } else {
            cout << "An error has occurred in WaitForSingleObject...\n";
            cout << "This usually indicates a problem with the OVERLAPPED structure's event handle\n";
        }
    } else {
        cout << "WriteFile failed, but isn't delayed. Report error and abort.\n";
    }
    return send;
}

char HardwareSerial::readByte() {
    DWORD dwRead = 0;
    char buffer[300];
    OVERLAPPED osReader = { 0 };
    osReader.hEvent = CreateEvent(nullptr, TRUE, FALSE, nullptr);
    // Create the overlapped event. Must be closed before exiting
    // to avoid a handle leak.

    //lpBuf[0] += 10;
    //dwRead == 1;
    ReadFile(handle, &buffer, 50, &dwRead, &osReader); // Read the Keyboard!
    if (dwRead == 1)         // In order to have an on the fly reading process
    {
        std::cout << buffer;
    }
    return buffer[0];
}

size_t HardwareSerial::print(const char *data) {
    return write(data, strlen(data));
}

size_t HardwareSerial::println(const char *data) {
    size_t sendBytes = write(data, strlen(data));
    sendBytes += write("\n", 1);
    return sendBytes;
}