# Road Pothole Tracker

A simple C++ program for Linux that simulates detecting potholes on a road,
tracks which ones are fixed, and shows statistics.

## Problem
Potholes on Indian roads cause accidents and vehicle damage, and it is hard
to know how many exist and how many have been repaired. This project is a
small prototype of a system that detects potholes and tracks their repair.

## Architecture
```
Sensor (/dev/urandom) -> Detection logic -> Storage (arrays) -> Menu
```
- **Sensor:** a Linux device file that gives a number from 0 to 99. It stands in
  for a vehicle accelerometer, since no real hardware is used.
- **Detection logic:** a reading of 80 or more is a big jolt, which means a pothole.
  Severity: 80-89 = low (1), 90-95 = medium (2), 96-99 = high (3).
- **Storage:** two arrays, `severity[]` and `repaired[]`, hold the data for each pothole.
- **Menu:** the user scans the road, lists potholes, marks them fixed, and views stats.

## Linux concept used
On Linux, devices are accessed as files under `/dev`. The program reads the
sensor value from a device file using the Linux system calls `open()`, `read()`
and `close()`. In a real deployment, a hardware sensor driver would take the
place of this simulated device file.

## Requirements
- Linux (tested on Ubuntu in VirtualBox)
- g++ compiler

## Build and run
```
g++ pothole.cpp -o pothole
./pothole
```

## Menu
```
1. Scan road            - checks 20 road spots and detects potholes
2. Show potholes        - lists all potholes with severity and status
3. Mark pothole fixed   - marks a pothole as repaired by its number
4. Stats                - shows total, fixed and not fixed
0. Exit
```

## Sample output
```
Enter choice: 1
Pothole #1 found, severity 1
Pothole #2 found, severity 3
Enter choice: 3
Enter pothole number: 1
Marked as fixed.
Enter choice: 4
Total: 2
Fixed: 1
Not fixed: 1
```
(Output varies because the sensor values are random.)

## Limitations
- The sensor is simulated, not real hardware.
- Data is not saved after the program exits.
- Stores at most 100 potholes.
- Location is not tracked.

## Future work
- Create a real Linux kernel module (character device) for the sensor
- Add GPS location for every pothole
- Save data to a file or database
- Detect potholes from camera images
- Send reports to the authorities
