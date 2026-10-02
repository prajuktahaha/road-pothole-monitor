// pothole.cpp - simple pothole tracker (C++ on Linux)
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
using namespace std;

int severity[100];   // 1 = low, 2 = medium, 3 = high
int repaired[100];   // 0 = not fixed, 1 = fixed
int total = 0;       // number of potholes found so far

// Reads one number (0 to 99) from the Linux device file /dev/urandom.
// This is our "sensor", because we have no real hardware.
int readSensor() {
    unsigned char value = 0;
    int fd = open("/dev/urandom", O_RDONLY);   // open the device
    read(fd, &value, 1);                       // read 1 byte from it
    close(fd);                                 // close it
    return value % 100;
}

int main() {
    int choice = -1;

    while (choice != 0) {
        cout << endl;
        cout << "1. Scan road" << endl;
        cout << "2. Show potholes" << endl;
        cout << "3. Mark pothole fixed" << endl;
        cout << "4. Stats" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            for (int i = 0; i < 20; i++) {
                int jolt = readSensor();
                if (jolt >= 80 && total < 100) {      // big jolt = pothole
                    if (jolt < 90) severity[total] = 1;
                    else if (jolt < 96) severity[total] = 2;
                    else severity[total] = 3;
                    repaired[total] = 0;
                    total++;
                    cout << "Pothole #" << total << " found, severity "
                         << severity[total - 1] << endl;
                }
            }
        }
        else if (choice == 2) {
            for (int i = 0; i < total; i++) {
                cout << "#" << i + 1 << " severity " << severity[i];
                if (repaired[i] == 1) cout << " - FIXED" << endl;
                else cout << " - NOT FIXED" << endl;
            }
        }
        else if (choice == 3) {
            int id;
            cout << "Enter pothole number: ";
            cin >> id;
            if (id >= 1 && id <= total) {
                repaired[id - 1] = 1;
                cout << "Marked as fixed." << endl;
            } else {
                cout << "Wrong number." << endl;
            }
        }
        else if (choice == 4) {
            int done = 0;
            for (int i = 0; i < total; i++) {
                if (repaired[i] == 1) done++;
            }
            cout << "Total: " << total << endl;
            cout << "Fixed: " << done << endl;
            cout << "Not fixed: " << total - done << endl;
        }
    }
    return 0;
}