# CampusResourceReservationSystem

A C++ console application for reserving campus resources such as study rooms, laptops, calculators, lab equipment, and tutoring services.

This project was created for **CSCE 2110 - Milestone 1**.

## Team

* **Samriddi Upreti** - Waiting List (Queue) + Cancellation History (Stack)
* **Frank Mucheke** - Reservation Management (Linked List)
* **Urisha Shrestha** - Resource Management

## Data Structures

This project uses the given data structures:

* **Linked List** - stores active reservations
* **Queue** - manages waiting lists (FIFO)
* **Stack** - manages cancellation history and undo (LIFO)
* **Vector** - stores resource inventory

## Project Structure

```text
include/    Header files (.h)
src/        Source files (.cpp), including main.cpp
data/       Input data files
```

## Build and Run

Compile the program with:

```bash
g++ -I include src/*.cpp -o reservation_system
```

Then run:

```bash
./reservation_system
```

## Features

* View available campus resources
* Search for resources
* Create reservations
* Cancel reservations
* Automatically add users to a waiting list when a resource is unavailable
* Undo the most recent cancellation
* Track cancellation history
