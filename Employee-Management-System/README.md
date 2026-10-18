# In-Memory Employee Management System (C)

A console-based Employee Management System written in C. It stores 
employee records in memory and supports adding, viewing, searching, 
sorting, deleting, and reporting. I built it to revise everything I had 
learned in C in one project.

## Features
- **Add employees** with validation: unique positive ID, age 1-79, 
  positive salary
- **Duplicate ID rejection** before any record is saved
- **View all records** and **search by ID**
- **Sort** by ID, Name, or Salary using bubble sort (with an early exit 
  when the list is already sorted)
- **Summary report:** headcount, average salary, and the highest-paid 
  employee
- **Delete** a record by ID
- **Fixed capacity** of 100 employees, with a warning when the list is full
- **Safe menu input:** typing letters instead of numbers no longer 
  breaks the program

## Menu

    ------------------------------------------------------------
                    EMPLOYEE MANAGEMENT SYSTEM
    ------------------------------------------------------------
    1. Add New Employee
    2. View All Employee Records
    3. Search Employee by ID
    4. Sort Employees (by ID, Name, or Salary)
    5. View Analytics & Summary Report
    6. Delete/Remove Employee Record
    7. Exit Program
    ------------------------------------------------------------

## C concepts used
- `struct` and arrays of structs
- Functions and prototypes
- Nested `switch` menus
- Bubble sort with a swap flag
- String handling (`strcmp`) and input validation
- Global state tracking (record counters)

## How to run

    cd Employee-Management-System
    gcc InMemoryEmpMngSystem.c -o ems
    ./ems          (on Windows: ems.exe)

## What I learned
Getting the program to work was only half of it. Testing it with bad 
input (a letter at the menu, a full list, a very long name, only one 
employee in the report) showed bugs that normal use never triggered, 
and fixing them taught me more about arrays and input handling in C 
than writing the program did.

## Planned improvements
- File handling, so records are saved between runs (my next C project)
- Re-prompt on invalid input instead of returning to the menu
- Case-insensitive sorting by name
