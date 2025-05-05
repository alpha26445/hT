#include <iostream>
#include <fstream>
#include <cstring>  // For strcpy
using namespace std;

class Student {
    struct Stud {
        int roll;
        char name[20];  // Increased size for name
        char div;
        char add[50];  // Increased size for address
    };
    Stud rec;

public:
    void create();
    void display();
    int search();
    void deleteRecord();
};

void Student::create() {
    char ans;
    ofstream fout;
    fout.open("stud.dat", ios::out | ios::binary);

    do {
        cout << "\n\tEnter Roll No of Student: ";
        cin >> rec.roll;

        cout << "\n\tEnter Name of Student: ";
        cin.ignore();  // To ignore the newline character left by previous input
        cin.getline(rec.name, 20);

        cout << "\n\tEnter Division of Student: ";
        cin >> rec.div;

        cout << "\n\tEnter Address of Student: ";
        cin.ignore();  // To ignore the newline character left by previous input
        cin.getline(rec.add, 50);

        fout.write(reinterpret_cast<char*>(&rec), sizeof(Stud));
        cout << "\n\tDo you want to add more records (Y/N)? ";
        cin >> ans;

    } while (ans == 'y' || ans == 'Y');

    fout.close();
}

void Student::display() {
    ifstream fin;
    fin.open("stud.dat", ios::in | ios::binary);

    cout << "\n\tThe Content of the File are:\n";
    cout << "\n\tRoll\tName\tDiv\tAddress\n";

    while (fin.read(reinterpret_cast<char*>(&rec), sizeof(Stud))) {
        if (rec.roll != -1) {
            cout << "\n\t" << rec.roll << "\t" << rec.name << "\t" << rec.div << "\t" << rec.add;
        }
    }

    fin.close();
}

int Student::search() {
    int r;
    ifstream fin;
    fin.open("stud.dat", ios::in | ios::binary);

    cout << "\n\tEnter a Roll No to Search: ";
    cin >> r;

    while (fin.read(reinterpret_cast<char*>(&rec), sizeof(Stud))) {
        if (rec.roll == r) {
            cout << "\n\tRecord Found...\n";
            cout << "\n\tRoll\tName\tDiv\tAddress";
            cout << "\n\t" << rec.roll << "\t" << rec.name << "\t" << rec.div << "\t" << rec.add;
            fin.close();
            return 1;
        }
    }

    fin.close();
    return 0;
}

void Student::deleteRecord() {
    int pos = search();
    if (pos == 0) {
        cout << "\n\tRecord Not Found.\n";
        return;
    }

    fstream f;
    f.open("stud.dat", ios::in | ios::out | ios::binary);
    f.seekg(0, ios::beg);

    int offset = (pos - 1) * sizeof(Stud);  // Position calculation fixed
    f.seekp(offset);

    // Mark record as deleted
    rec.roll = -1;
    strcpy(rec.name, "NULL");
    rec.div = 'N';
    strcpy(rec.add, "NULL");

    f.write(reinterpret_cast<char*>(&rec), sizeof(Stud));
    f.close();

    cout << "\n\tRecord Deleted\n";
}

int main() {
    Student obj;
    int choice;
    char ans;

    do {
        cout << "\n\t***** Student Information *****";
        cout << "\n\t1. Create";
        cout << "\n\t2. Display";
        cout << "\n\t3. Delete";
        cout << "\n\t4. Search";
        cout << "\n\t5. Exit";
        cout << "\n\tEnter Your Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: 
                obj.create();
                break;

            case 2: 
                obj.display();
                break;

            case 3: 
                obj.deleteRecord();
                break;

            case 4: 
                if (obj.search() == 0) {
                    cout << "\n\tRecord Not Found...\n";
                }
                break;

            case 5:
                cout << "\n\tExiting Program...\n";
                break;

            default:
                cout << "\n\tInvalid choice. Please try again.\n";
        }

        cout << "\n\tDo you want to continue in the main menu (Y/N)? ";
        cin >> ans;

    } while (ans == 'y' || ans == 'Y');

    return 0;
}
