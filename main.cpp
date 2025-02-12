// This program displays a menu of choices to a user
// and performs the chosen task. It will keep asking a user to
// enter the next choice until the choice of 'Q' (Quit) is entered.

#include <iostream>
#include <string>
#include "LinkedList.h"

using namespace std;

void printMenu();

int main() {
    char input1 = 'Z';
    string firstName, lastName, newFullName;
    int id;
    double gpa;
    bool success = false;

    LinkedList* list1 = new LinkedList();

    printMenu();

    do {
        cout << "\nWhat action would you like to perform?\n";
        cin.get(input1);
        input1 = toupper(input1);
        cin.ignore(20, '\n');   // Flush the buffer

        switch (input1) {
            case 'A':   // Add student
                cout << "Please enter the student's information:\n";
                cout << "First name: ";
                getline(cin, firstName);
                cout << "Last name: ";
                getline(cin, lastName);
                cout << "Student ID: ";
                cin >> id;
                cout << "GPA: ";
                cin >> gpa;
                cin.ignore(20, '\n');   // Flush buffer

                success = list1->addStudent(firstName, lastName, id, gpa);

                if (success) {
                    cout << "Student \"" << firstName << " " << lastName << "\" is added.\n";
                } else {
                    cout << "Student \"" << firstName << " " << lastName << "\" is NOT added.\n";
                }
                break;

            case 'C':   // Change student name
                cout << "Please enter the student ID whose name you want to change:\n";
                cin >> id;
                cin.ignore(20, '\n');   // Flush buffer
                cout << "\nPlease enter the student's new full name: ";
                getline(cin, newFullName);

                success = list1->changeStudentName(id, newFullName);

                if (success) {
                    cout << "\nStudent ID #: " << id << " name was changed.\n";
                } else {
                    cout << "\nStudent ID #: " << id << " does not exist.\n";
                }
                break;

            case 'D':   // Display all students
                list1->printStudentList();
                break;

            case 'E':   // Display students by last name
                cout << "\nPlease enter the student last name which you want to display:\n";
                getline(cin, lastName);
                list1->printStudentListByLastName(lastName);
                break;

            case 'F':   // Find a student
                cout << "\nPlease enter the student ID you want to search:\n";
                cin >> id;
                cin.ignore(20, '\n');   // Flush buffer
            
                success = list1->findStudent(id);

                if (success) {
                    cout << "Student with ID #: " << id << " was found.\n";
                } else {
                    cout << "Student with ID #: " << id << " was NOT found.\n";
                }
                break;

            case 'G':   // Update a student's GPA
                cout << "\nPlease enter the student ID whose GPA you want to update:\n";
                cin >> id;
                cin.ignore(20, '\n');   // Flush buffer
            
                success = list1->findStudent(id);

                if (success) {
                    cout << "\nPlease enter the new GPA:\n";
                    cin >> gpa;
                    cin.ignore(20, '\n');
                    
                    success = list1->updateStudentGpa(id, gpa);

                    if (success) {
                        cout << "Student with ID #: " << id << " GPA was updated.\n";
                    }
                } else {
                    cin.ignore(20, '\n');
                    cout << "Student with ID #: " << id << " does NOT exist.\n";
                }
                break;

            case 'R':   // Remove a student from the list by ID
                cout << "\nPlease enter the student ID to remove:\n";
                cin >> id;
                cin.ignore(20, '\n');   // Flush buffer

                success = list1->removeById(id);

                if (success) {
                    cout << "\nStudent with ID #: " << id << " was removed.\n";
                } else {
                    cout << "\nStudent with ID #: " << id << " does NOT exist.\n";
                }
                break;

            case 'S':   // Remove a student from the list by name
                cout << "Please enter the student first name you want to remove:\n";
                getline(cin, firstName);
                cout << "Please enter the student last name you want to remove:\n";
                getline(cin, lastName);

                success = list1->removeByName(firstName, lastName);

                if (success) {
                    cout << "\nStudent with name: " << firstName << " " << lastName << " was removed.\n";
                } else {
                    cout << "\nStudent with name: " << firstName << " " << lastName << " does NOT exist.\n";
                }
                break;

            case 'Q':   // Quit
                delete list1;
                break;

            case '?':   // Display Menu
                printMenu();
                break;

            default:
                cout << "Unknown action\n";
                break;
        }
    } while (input1 != 'Q');
    return 0;
}

// Display menu to the user
void printMenu() {
    cout << "Choice\t\tAction\n";
    cout << "------\t\t------\n";
    cout << "A\t\tAdd a Student\n";
    cout << "C\t\tChange a Student's Name\n";
    cout << "D\t\tDisplay All Students\n";
    cout << "E\t\tDisplay Students by Last Name\n";
    cout << "F\t\tFind a Student\n";
    cout << "G\t\tUpdate Student's GPA\n";
    cout << "R\t\tRemove Student by ID\n";
    cout << "S\t\tRemove Student by Name\n";
    cout << "Q\t\tQuit\n";
    cout << "?\t\tDisplay Help\n\n";
}
