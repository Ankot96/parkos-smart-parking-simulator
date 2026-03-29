# ParkOS – Smart Parking Management System

## Overview

**ParkOS** is a simulation-based smart parking management system developed in C for Linux.
The project demonstrates practical usage of **Linux system calls, POSIX APIs, IPC mechanisms, multithreading, synchronization, and signal handling**.

The system simulates real-world parking operations such as vehicle entry, exit, slot allocation, monitoring, and logging — all without using any hardware.

---

## Objectives

* Implement a **multi-process system** using `fork()` and `waitpid()`
* Demonstrate **Inter-Process Communication (IPC)** using:

  * Pipe
  * FIFO (Named Pipe)
* Use **POSIX Threads (pthreads)** for concurrent monitoring
* Ensure **thread synchronization** using mutex
* Perform **low-level file I/O operations**
* Implement **signal handling** for graceful shutdown
* Design a **modular multi-file system**

---

## System Architecture

### Main Controller (Parent Process)

* Handles UI, login, and system coordination
* Spawns child processes for entry and exit
* Receives data via IPC

---

### Entry Process (Child)

* Created using `fork()`
* Takes vehicle input from user
* Sends vehicle number to parent via **pipe**

---

### Exit Process (Child)

* Created using `fork()`
* Sends vehicle number via **FIFO (named pipe)**

---

### Monitor Thread

* Runs continuously in background
* Displays parking occupancy status
* Uses `pthread` and `mutex` for safe access

---

## Inter-Process Communication (IPC)

| Mechanism | Purpose                |
| --------- | ---------------------- |
| Pipe      | Entry process → Parent |
| FIFO      | Exit process → Parent  |

---

## Synchronization

* Shared resources:

  * Parking slots array
  * Parked cars list
* Protected using:

  ```c
  pthread_mutex_t lock;
  ```

---

## File Handling

### Vehicle Database

* File: `data/vehicle_db.txt`
* Stores vehicle types
* Accessed using:

  * `open()`
  * `read()`
  * `close()`

---

### Logging System

* File: `data/parking_log.txt`
* Logs all entry/exit events
* Uses:

  * `open()`
  * `write()`
  * `lseek()`

---

## System Calls Used

### File I/O

* `open()`, `read()`, `write()`, `lseek()`, `close()`

### Process Control

* `fork()`, `waitpid()`

### IPC

* `pipe()`, `mkfifo()`, `read()`, `write()`

### Threads

* `pthread_create()`, `pthread_mutex_lock()`, `pthread_mutex_unlock()`

### Signals

* `SIGINT` → graceful shutdown
* `SIGUSR1` → status trigger

---

## Authentication System

| Role     | Permissions                         |
| -------- | ----------------------------------- |
| Employee | Park / Remove vehicles              |
| Manager  | Full access (including status view) |

### Credentials

**Employee**

* Username: `employee`
* Password: `123`

**Manager**

* Username: `manager`
* Password: `admin`

---

## User Interface

* Terminal-based UI with ANSI colors
* Boot-style startup screen
* Menu-driven interaction
* Real-time updates

---

## Program Flow

```
Start Program
   ↓
Boot Screen (UI)
   ↓
Login (Auth Module)
   ↓
Main Menu
   ↓
User Selection:
   1 → Entry → Pipe → park_car()
   2 → Exit → FIFO → remove_car()
   3 → View Status (Manager only)
   ↓
Monitor Thread runs in background
   ↓
Logs written to file
   ↓
Signal handles shutdown
```

---

## Simulation Features

* Delays using `sleep()` to simulate real-world parking
* File-based vehicle classification
* Manual user input
* Continuous monitoring thread

---

## Project Structure

```
parkos-smart-parking-simulator/
│
├── src/
│   ├── main.c
│   ├── parking_manager.c
│   ├── database.c
│   ├── ui.c
│   ├── auth.c
│
├── include/
│   ├── parking_manager.h
│   ├── database.h
│   ├── ui.h
│   ├── auth.h
│
├── data/
│   ├── vehicle_db.txt
│   └── parking_log.txt
│
├── Makefile
└── README.md
```

---

## Build Instructions

```bash
make
```

---

## Run Instructions

```bash
make run
```

---

## Setup Requirement

Create FIFO before running:

```bash
mkfifo exit_pipe
```

---

## Sample Run

```
[BOOT] Initializing system...
[SUCCESS] System Ready

Login:
Username: manager
Password: admin

1. Park Vehicle
2. Remove Vehicle
3. View Status

Enter choice: 1
Car parked successfully
```

---

## Clean Build

```bash
make clean
```

---

## Key Features

* Multi-process architecture
* Dual IPC mechanisms
* Thread-based monitoring
* Real-time logging
* Signal-based control
* Modular and scalable design

---

## Limitations

* No GUI (terminal-based only)
* Static parking capacity
* No persistent database updates

---

## Learning Outcomes

* Understanding of Linux system calls
* Process management and IPC
* Thread synchronization
* File handling at low level
* System-level program design

---

## 🏁 Conclusion

ParkOS successfully demonstrates a **complete system-level simulation** integrating processes, threads, IPC, signals, and file handling.
It reflects real-world system design principles and satisfies all requirements of the mini project guidelines.

---

## 👨‍💻 Author

Yash Bhosale
ParkOS – Smart Parking Simulation System
