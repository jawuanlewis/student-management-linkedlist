// This program creates a Linked List class for
// making a list of students, including each
// student's name, id, and gpa. Many methods for
// manipulating the student data are also defined.

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

struct Student {
    string firstName, lastName;
    int id;
    double gpa;
    struct Student* next;
};

class LinkedList {
    private:
        struct Student* head;

    public:
        LinkedList();
        ~LinkedList();
        bool findStudent(int studentId);
        bool addStudent(string firstName, string lastName, int studentId, double gpa);
        bool removeById(int studentId);
        bool removeByName(string firstName, string lastName);
        bool changeStudentName(int studentId, string newFullName);
        bool updateStudentGpa(int studentId, double newGpa);
        void printStudentListByLastName(string oneLastName);
        void printStudentList();
};


/* LinkedList function definitions */

LinkedList::LinkedList() {
    head = NULL;
}

LinkedList::~LinkedList() {
    int studentCount = 0;
    struct Student* temp;

    while (head != NULL) {
	    temp = head;
	    head = head->next;
	    free(temp);
	    studentCount++;
    }
    cout << "The number of deleted students is: " << studentCount << "\n";
}

// Find whether or not the specified student exists
bool LinkedList::findStudent(int studentId) {
    struct Student* temp = head;
    bool studentExists = false;

    while (temp != NULL) {
        if (studentId == temp->id) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

// Add a new student to the list (sorted by last name)
// NOTE: students should have unique IDs, but may have the same last or full name
bool LinkedList::addStudent(string firstName, string lastName, int studentId, double gpa) {
    if (findStudent(studentId)) {
	    cout << "Duplicate student. Not added.\n";
	    return false;
    }
    
    // Create new Student node with user input
    struct Student* newStudent = new Student();
    newStudent->firstName = firstName;
    newStudent->lastName = lastName;
    newStudent->id = studentId;
    newStudent->gpa = gpa;

    if (head == NULL) {
	    head = newStudent;
	    head->next = NULL;
	    return true;
    }

    struct Student* temp = head;
    int lastNameCount = 0;
    int firstAndLastCount = 0;

    // Handling cases where students have the same name
    while (temp != NULL) {
        if (temp->lastName == lastName && temp->firstName != firstName) {
            lastNameCount++;
        } else if (temp->lastName == lastName && temp->firstName == firstName) {
            firstAndLastCount++;
        }
        temp = temp->next;
    }

    temp = head;

    // If no student has same last name, sort by last name
    if (lastNameCount == 0 && firstAndLastCount == 0) {
        if (head->next == NULL) {
            if (lastName < head->lastName) {
                newStudent->next = head;
                head = newStudent;
            } else {
                head->next = newStudent;
            }
            return true;
        }
        if (lastName < head->lastName) {
            newStudent->next = head;
            head = newStudent;
            return true;
        } else {
            while (temp->next != NULL) {
                if (temp->next->lastName > lastName) {
                    newStudent->next = temp->next;
                    temp->next = newStudent;
                    return true;
                }
                temp = temp->next;
            }
        }
        if (temp->next == NULL) {
            temp->next = newStudent;
            return true;
        }
    } 
    // Sort by first name if 2+ students share same last name
    else if (lastNameCount > 0 && firstAndLastCount == 0) { 
        if (head->next == NULL) {
            if (firstName < head->firstName) {
                newStudent->next = head;
                head = newStudent;
            } else {
                head->next = newStudent;
            }
            return true;
        }
        if (lastName == head->lastName) {
            if (firstName < head->firstName) {
                newStudent->next = head;
                head = newStudent;
                return true;
            } else {
                while (temp->next != NULL && temp->next->firstName < firstName && temp->next->lastName == lastName) {
                    temp = temp->next;
                }
                if (temp->next == NULL) {
                    temp->next = newStudent;
                } else {
                    newStudent->next = temp->next;
                    temp->next = newStudent;
                }
                return true;
            }
        } else {
            while (temp->next->lastName != lastName) {
                temp = temp->next;
            }
            while (temp->next != NULL && temp->next->lastName == lastName) {
                if (temp->next->firstName > firstName) {
                    newStudent->next = temp->next;
                    temp->next = newStudent;
                    return true;
                }
                temp = temp->next;
            }
            if (temp->next == NULL) {
                temp->next = newStudent;
            } else {
                newStudent->next = temp->next;
                temp->next = newStudent;
            }
            return true;
        }
    }
    // Sort by ID if 2+ students share same full name
    else if (firstAndLastCount > 0) {
        if (head->next == NULL) {
            if (studentId < head->id) {
                newStudent->next = head;
                head = newStudent;
            } else {
                head->next = newStudent;
            }
            return true;
        }
        if (firstName == head->firstName && lastName == head->lastName) {
            if (studentId < head->id) {
                newStudent->next = head;
                head = newStudent;
            } else {
                while (temp->next != NULL && temp->next->id < studentId && temp->next->firstName == firstName && temp->next->lastName == lastName) {
                    temp = temp->next;
                }
                if (temp->next == NULL) {
                    temp->next = newStudent;
                } else {
                    newStudent->next = temp->next;
                    temp->next = newStudent;
                }
            }
            return true;
        } else {
            while (temp->next->firstName != firstName || temp->next->lastName != lastName) {
                temp = temp->next;
            }
            while (temp->next != NULL && temp->next->firstName == firstName && temp->next->lastName == lastName) {
                if (temp->next->id > studentId) {
                    newStudent->next = temp->next;
                    temp->next = newStudent;
                    return true;
                }
                temp = temp->next;
            }
            if (temp->next == NULL) {
                temp->next = newStudent;
            } else {
                newStudent->next = temp->next;
                temp->next = newStudent;
            }
            return true;
        }
    }
    return false;
}

// Remove the specified student from the list
bool LinkedList::removeById(int studentId) {
    if (head == NULL || !findStudent(studentId)) {
	    return false;
    }

    struct Student* temp = head;
    struct Student* prev = NULL;

    if (studentId == temp->id) {
        head = temp->next;
        delete temp;
        return true;
    }

    while (temp->id != studentId) {
	    prev = temp;
	    temp = temp->next;
    }

    prev->next = temp->next;
    delete temp;
    return true;
}

// Remove any students with the specified first and last name
bool LinkedList::removeByName(string firstName, string lastName) {
    if (head == NULL) {
	    cout << "No such student name found.\n";
	    return false;
    }

    bool studentsRemoved = false;

    if (head->next == NULL && head->firstName == firstName && head->lastName == lastName) {
        struct Student* temp = head;
        head = temp->next;
        delete temp;
        return true;
    }

    while (head->firstName == firstName && head->lastName == lastName) {
        struct Student* temp = head;
        head = head->next;
        free(temp);
        studentsRemoved = true;
    }

    // traverse entire list
    for (struct Student* temp = head; temp != NULL; temp = temp->next) {
        while (temp->next != NULL && temp->next->firstName == firstName && temp->next->lastName == lastName) {
            struct Student* tmp = temp->next;
            temp->next = tmp->next;
            free(tmp);
            studentsRemoved = true;
        }
    }

    if (!studentsRemoved) {
        cout << "No such student name found.\n"; 
    }
    return studentsRemoved;
}

// Modify the name of the specified student
bool LinkedList::changeStudentName(int studentId, string newFullName) {
    if (head == NULL || !findStudent(studentId)) {
	    cout << "\nStudent is NOT inside the list, cannot change student name.\n";
	    return false;
    }

    struct Student* temp = head;

    while (temp->id != studentId) {
	    temp = temp->next;
    }

    string newFirstName = newFullName.substr(0, newFullName.find(" ")); 
    string newLastName = newFullName.substr(newFullName.find(" ") + 1);
    int sameId = temp->id;
    double sameGpa = temp->gpa;

    // Use remove and add functions to maintain alphabetical order
    if (removeById(sameId)) {
        return addStudent(newFirstName, newLastName, sameId, sameGpa);
    }
    return false;   // if above operations fail
}

// Update GPA of the specified student
bool LinkedList::updateStudentGpa(int studentId, double newGpa) {
    if (head == NULL || !findStudent(studentId)) {
	    cout << "Student is NOT inside the list, cannot change the gpa.\n";
	    return false;
    }
    
    struct Student* temp = head;

    while (temp->id != studentId) {
	    temp = temp->next;
    }
    temp->gpa = newGpa;
    return true;
}

// Print all students in the list with the specified last name.
void LinkedList::printStudentListByLastName(string oneLastName) {
    if (head == NULL) {
	    cout << "The list is empty.\n";
	    return;
    }

    struct Student* temp = head;
    int count = 0;

    // Find students with the given last name
    while (temp != NULL) {
        if (temp->lastName == oneLastName) {
            count++;

            cout << left << setw(12) << temp->firstName
                 << left << setw(12) << temp->lastName
                 << right << setw(8) << temp->id
                 << setw(10) << fixed << setprecision(2) << temp->gpa << "\n";
        }
        temp = temp->next;
    }

    if (count == 0) {
	    cout << "No students with the specified last name found.\n";
    }
}

// Print all students in the list
void LinkedList::printStudentList() {
    if (head == NULL) {
	    cout << "The list is empty.\n";
	    return;
    }

    struct Student* temp = head;
    
    while (temp != NULL) {

        cout << left << setw(12) << temp->firstName
             << left << setw(12) << temp->lastName
             << right << setw(8) << temp->id
             << setw(10) << fixed << setprecision(2) << temp->gpa << "\n";

        temp = temp->next;
    }
}
