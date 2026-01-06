# Employee Management System (C++)

A small **object-oriented employee management system** written in C++, designed to practice
inheritance, polymorphism, and dynamic memory management.

The system models different employee roles, computes salaries based on role-specific rules,
and maintains a priority queue ordered by salary.

## Features
- Abstract base class for employees
- Role-specific derived classes with overridden salary calculations
- Use of enums to model employee categories and qualifications
- Salary-based priority queue implemented using a heap
- Basic validation and error handling
- Simple test driver demonstrating functionality

## Structure
- `employee_management.h / .cpp` — core class hierarchy and logic
- `main.cpp` — example usage and tests

## Build & Run

```bash
g++ -std=c++17 -O2 -Wall -Wextra -pedantic main.cpp employee_management.cpp -o employee_system
./employee_system
```
Note: This project was done as part of a university course. Because these are very common assignments, I had to prioritize writing an original solution that wouldn’t trigger plagiarism checks, rather than fully optimizing style or structure.