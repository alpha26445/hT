#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <cstdlib>

using namespace std;

const char* fileName = "Employee.txt";

class Employee {
private:
    int empID;
    char empName[50], post[50], department[10];
    float salary;

public:
    void readData();
    void displayRecord() const;
    int getID() const;
    const char* getDepartment() const;
    void updateRecord();
};

void Employee::readData() {
    cout << "\nEmployee ID: ";
    cin >> empID;
    cout << "Employee Name: ";
    cin >> empName;
    cout << "Employee's Post: ";
    cin >> post;
    cout << "Employee's Department: ";
    cin >> department;
    cout << "Salary: ";
    cin >> salary;
}

void Employee::displayRecord() const {
    cout << endl << "_______________________________";
    cout << endl << setw(5) << empID << setw(15) << empName << setw(15) << post << setw(15) << department << setw(8) << salary;
}

int Employee::getID() const {
    return empID;
}

const char* Employee::getDepartment() const {
    return department;
}

void Employee::updateRecord() {
    cout << "\nEnter new record:" << endl;
    readData();
}

void displayAllEmployees(fstream& file) {
    Employee e;
    file.clear();
    file.seekg(0, ios::beg);
    int counter = 0;
    cout << endl << setw(5) << "ID" << setw(15) << "Name" << setw(15) << "Post" << setw(15) << "Department" << setw(8) << "Salary";
    
    while (file.read((char*)&e, sizeof(e))) {
        counter++;
        e.displayRecord();
    }
    cout << endl << counter << " records found." << endl;
}

void searchEmployeeByID(fstream& file, int ID) {
    Employee e;
    bool found = false;
    file.seekg(0, ios::beg);
    while (file.read((char*)&e, sizeof(e))) {
        if (e.getID() == ID) {
            e.displayRecord();
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "\nData not found for employee ID #" << ID << endl;
    }
}

void searchEmployeeByDept(fstream& file, const char* dept) {
    Employee e;
    bool found = false;
    file.seekg(0, ios::beg);
    cout << "\nEmployees in department " << dept << ":";
    while (file.read((char*)&e, sizeof(e))) {
        if (strcmp(e.getDepartment(), dept) == 0) {
            e.displayRecord();
            found = true;
        }
    }
    if (!found) {
        cout << "\nData not found for department " << dept << endl;
    }
}

void addEmployeeRecord(fstream& file, Employee& emp) {
    Employee e;
    file.seekg(0, ios::beg);
    while (file.read((char*)&e, sizeof(e))) {
        if (e.getID() == emp.getID()) {
            cout << "This ID already exists... Try another ID." << endl;
            return;
        }
    }
    file.clear();
    file.seekp(0, ios::end);
    file.write((char*)&emp, sizeof(emp));
    cout << "\nNew record has been added successfully." << endl;
}

void updateEmployeeRecord(fstream& file, int ID) {
    Employee e;
    bool found = false;
    int recordNo = 0;
    file.seekg(0, ios::beg);
    while (file.read((char*)&e, sizeof(e))) {
        recordNo++;
        if (e.getID() == ID) {
            cout << "Old record:" << endl;
            e.displayRecord();
            e.updateRecord();
            file.seekp((recordNo - 1) * sizeof(e), ios::beg);
            file.write((char*)&e, sizeof(e));
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "\nData not found for employee ID #" << ID << endl;
    }
}

void deleteEmployeeRecord(fstream& file, int ID) {
    Employee e;
    bool found = false;
    char tempFile[] = "temp.txt";
    fstream temp(tempFile, ios::out | ios::binary);

    file.seekg(0, ios::beg);
    while (file.read((char*)&e, sizeof(e))) {
        if (e.getID() != ID) {
            temp.write((char*)&e, sizeof(e));
        } else {
            found = true;
        }
    }

    if (!found) {
        cout << "\nData not found for employee ID #" << ID << endl;
    } else {
        file.close();
        temp.close();
        remove(fileName);
        rename(tempFile, fileName);
        cout << "\nRecord deleted successfully." << endl;
    }
}

int main() {
    Employee emp;
    char option, ch;
    int ID;

    fstream file(fileName, ios::ate | ios::in | ios::out | ios::binary);

    do {
        cout << "\n******* Menu ********";
        cout << "\n1 => Add a new record";
        cout << "\n2 => Search record from employee ID";
        cout << "\n3 => List employee of particular department";
        cout << "\n4 => Display all employees";
        cout << "\n5 => Update record of an employee";
        cout << "\n6 => Delete record of a particular employee";
        cout << "\n7 => Exit from the program";
        cout << "\n*****************************\n";
        cin >> option;

        switch (option) {
            case '1':
                emp.readData();
                addEmployeeRecord(file, emp);
                break;

            case '2':
                cout << "\nEnter employee ID to search: ";
                cin >> ID;
                searchEmployeeByID(file, ID);
                break;

            case '3':
                {
                    char dept[50];
                    cout << "Enter department name to list employees: ";
                    cin >> dept;
                    searchEmployeeByDept(file, dept);
                }
                break;

            case '4':
                displayAllEmployees(file);
                break;

            case '5':
                cout << "\nEnter employee ID to be updated: ";
                cin >> ID;
                updateEmployeeRecord(file, ID);
                break;

            case '6':
                cout << "\nEnter employee ID to be deleted: ";
                cin >> ID;
                deleteEmployeeRecord(file, ID);
                break;

            case '7':
                cout << "Exiting program..." << endl;
                exit(0);

            default:
                cout << "Invalid option!" << endl;
        }

        cout << "\nDo you want to continue? (y/n): ";
        cin >> ch;

    } while (ch != 'n');

    file.close();
    return 0;
}
