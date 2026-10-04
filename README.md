# Road Pothole Tracker

A small C++ program for Linux. It pretends to drive on a road, finds potholes,
and keeps track of which ones are fixed.

Design and diagrams: [docs/DESIGN.md](docs/DESIGN.md)

## Why I made it
Many roads in India have potholes and it is hard to know how many are fixed.
This is a small prototype that finds potholes and tracks repairs.

## How it works
1. There is no real sensor, so I read a number (0 to 99) from the Linux file `/dev/urandom`.
2. If the number is 80 or more, I count it as a pothole.
3. A bigger number means a worse pothole (severity 1, 2 or 3).
4. Potholes are kept in arrays. The user can mark them as fixed.

## Linux concept
In Linux, devices are treated like files in `/dev`. My program uses
`open()`, `read()` and `close()` on `/dev/urandom` to get the sensor value.
With a real sensor, a driver would give the value in the same way.

## How to run
```
g++ pothole.cpp -o pothole
./pothole
```
Needs Linux and g++. I tested it on Ubuntu.

## Menu
```
1. Scan road
2. Show potholes
3. Mark pothole fixed
4. Stats
0. Exit
```

## Limits
- The sensor is fake.
- Data is lost when the program closes.
- It stores only 100 potholes.

## Future work
- A real Linux driver for the sensor
- GPS location
- Saving data in a file
