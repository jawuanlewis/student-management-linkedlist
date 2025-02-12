# Student Management System (Linked List Implementation)

A C++ command-line application for managing student records in educational institutions. The system uses a Linked List data structure to store and organize student information including names, IDs, and GPAs.

*Note: This project was developed as a school assignment to demonstrate Linked List implementation in C++.*

## Features

- Add new students with automatic sorting by last name
- Find students by ID
- Remove students by ID or full name
- Update student names and GPAs
- Display all students or filter by last name
- Handles duplicate names with ID-based sorting

## Setup Instructions

1. Ensure you have a C++ compiler installed (e.g., g++, Visual C++)
2. Clone this repository
3. Compile the program in a terminal:

```
g++ main.cpp -o student_manager
```

4. Run the application:

```
./student_manager
```

## Usage

After launching the application, use these commands:

- A: Add a new student
- C: Change a student's name
- D: Display all students
- E: Display students by last name
- F: Find a student by ID
- G: Update a student's GPA
- R: Remove a student by ID
- S: Remove a student by name
- ?: Display help menu
- Q: Quit the program