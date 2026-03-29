# ParkOS – Smart Parking Management System

## 1. Overview

ParkOS is a simulation-based smart parking management system developed in C for Linux environments. The project demonstrates the practical application of Linux system programming concepts including process management, inter-process communication (IPC), multithreading, synchronization, signal handling, and low-level file operations.

The system simulates real-world parking operations such as vehicle entry, exit, slot allocation, monitoring, and logging without relying on any physical hardware.

---

## 2. Objectives

* Design a multi-process system using `fork()` and `waitpid()`
* Implement IPC using pipe and FIFO (named pipes)
* Use POSIX threads for concurrent monitoring
* Apply synchronization using mutex mechanisms
* Perform low-level file handling using system calls
* Handle signals for controlled execution and shutdown
* Maintain modular and scalable code structure

---

## 3. System Architecture

### 3.1 Parent Process (Controller)

The main process acts as the system controller. It is responsible for:

* User authentication and interface management
* Creating and supervising child processes
* Coordinating IPC and core parking logic

### 3.2 Entry Process

* Created using `fork()`
* Accepts vehicle input from user
* Sends data to parent via pipe

### 3.3 Exit Process

* Created using `fork()`
* Sends vehicle exit information using FIFO

### 3.4 Parking Manager Module

* Core logic for slot allocation and removal
* Maintains parking state
* Interacts with database and logging system

### 3.5 Monitoring Thread

* Continuously observes parking occupancy
* Runs concurrently using POSIX threads
* Uses mutex to ensure safe shared data access

---

## 4. Inter-Process Communication

| Mechanism | Purpose                               |
| --------- | ------------------------------------- |
| Pipe      | Entry process to parent communication |
| FIFO      | Exit process to parent communication  |

The selection of IPC mechanisms is based on communication direction and persistence requirements.

---

## 5. Threading and Synchronization

* A dedicated monitoring thread runs in parallel with the main process
* Shared resources:

  * Parking slots array
  * Parked vehicle records
* Protected using:

  * `pthread_mutex_lock()`
  * `pthread_mutex_unlock()`

This ensures data consistency and prevents race conditions.

---

## 6. File I/O and Data Management

### 6.1 Vehicle Database

* File: `data/vehicle_db.txt`
* Stores vehicle number and type mappings
* Accessed using:

  * `open()`
  * `read()`
  * `close()`

### 6.2 Logging System

* File: `data/parking_log.txt`
* Records entry and exit events
* Uses:

  * `open()`
  * `write()`
  * `lseek()`

---

## 7. System Calls and APIs Used

### File Operations

* `open()`, `read()`, `write()`, `lseek()`, `close()`

### Process Management

* `fork()`, `waitpid()`

### IPC

* `pipe()`, `mkfifo()`, `read()`, `write()`

### Threading

* `pthread_create()`, `pthread_mutex_lock()`, `pthread_mutex_unlock()`

### Signal Handling

* `signal()`
* `SIGINT` for graceful shutdown
* `SIGUSR1` for runtime status trigger

---

## 8. Authentication System

| Role     | Permissions                         |
| -------- | ----------------------------------- |
| Employee | Park and remove vehicles            |
| Manager  | Full access including system status |

### Credentials

Employee

* Username: employee
* Password: 123

Manager

* Username: manager
* Password: admin

---

## 9. Program Flow

1. System startup and initialization
2. User authentication
3. Menu-driven operation
4. Vehicle entry or exit selection
5. IPC communication with child processes
6. Parking allocation or removal
7. Logging of operations
8. Continuous monitoring via thread
9. Signal-based shutdown handling

---

## 10. Simulation Features

* Time delays using `sleep()` to simulate real parking behavior
* File-based vehicle classification
* Controlled user input
* Background monitoring thread

---

## 11. Project Structure

```
parkos-smart-parking-simulator/
│
├── src/
├── include/
├── data/
│
├── docs/               (architecture diagrams)
├── Makefile
├── README.md
└── .gitignore
```

---

## 12. Build Instructions

```
make
```

---

## 13. Execution

```
make run
```

---

## 14. Setup Requirement

Create FIFO before execution:

```
mkfifo exit_pipe
```

---

## 15. Sample Execution

```
System initialized
Login successful
Menu displayed
Vehicle parked and logged
```

---

## 16. Key Features

* Multi-process architecture
* Dual IPC implementation
* Thread-based monitoring
* Synchronization using mutex
* Signal-based lifecycle control
* Structured logging system
* Modular code design

---

## 17. Limitations

* Terminal-based interface only
* Fixed parking capacity
* No persistent database updates
* Limited error recovery scenarios

---

## 18. Learning Outcomes

* Practical understanding of Linux system programming
* Process creation and management
* IPC design and implementation
* Thread synchronization
* Low-level file handling
* System architecture design

---

## 19. Conclusion

ParkOS is a complete simulation of a smart parking system integrating multiple core Linux programming concepts. The project demonstrates a well-structured and scalable approach to system-level software design and satisfies all requirements of the mini project guidelines.

---

## 20. Author

Yash Bhosale
Embedded Linux Mini Project – ParkOS
