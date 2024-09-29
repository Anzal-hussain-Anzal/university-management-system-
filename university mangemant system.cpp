#include <iostream>
#include <fstream>
#include <string>
#include <windows.h> // For Sleep function
using namespace std;

class University {
private:
    string RollNo, Name, Subject, Address;

public:
    University() : RollNo(""), Name(""), Subject(""), Address("") {}

    void setRollNo(const string& rollNo) {
        RollNo = rollNo;
    }

    void setName(const string& name) {
        Name = name;
    }

    void setSubject(const string& subject) {
        Subject = subject;
    }

    void setAddress(const string& address) {
        Address = address;
    }

    string getRollNo() const {
        return RollNo;
    }

    string getName() const {
        return Name;
    }

    string getSubject() const {
        return Subject;
    }

    string getAddress() const {
        return Address;
    }
};

void add(University& student) {
    string rollNo, name, subject, address;

    cout << "\tEnter RollNo Of Student: ";
    cin >> rollNo;
    student.setRollNo(rollNo);

    cout << "\tEnter Name Of Student: ";
    cin.ignore(); // To ignore the leftover newline from the previous input
    getline(cin, name);
    student.setName(name);

    cout << "\tEnter Subject Of Student: ";
    getline(cin, subject);
    student.setSubject(subject);

    cout << "\tEnter Address Of Student: ";
    getline(cin, address);
    student.setAddress(address);

    ofstream out("university.txt", ios::app);
    if (!out) {
        cerr << "\tError: File Can't Open!" << endl;
    } else {
        out << student.getRollNo() << " : " << student.getName() << " : " 
            << student.getSubject() << " : " << student.getAddress() << endl;
        cout << "\tStudent Added Successfully!" << endl;
    }
}

void search() {
    string rollNo;
    cout << "\tEnter RollNo Of Student: ";
    cin >> rollNo;

    ifstream in("university.txt");
    if (!in) {
        cerr << "\tError: File Can't Open!" << endl;
        return;
    }

    string line;
    bool found = false;
    while (getline(in, line)) {
        if (line.find(rollNo) != string::npos) {
            cout << "\t" << line << endl;
            found = true;
            break;  // Stop searching after finding the student
        }
    }

    if (!found) {
        cout << "\tStudent Not Found!" << endl;
    }
}

void update(University& student) {
    string rollNo;
    cout << "\tEnter RollNo Of Student: ";
    cin >> rollNo;

    ifstream infile("university.txt");
    ofstream outfile("university_temp.txt");
    if (!infile || !outfile) {
        cerr << "\tError: File Can't Open!" << endl;
        return;
    }

    string line;
    bool found = false;
    while (getline(infile, line)) {
        if (line.find(rollNo) != string::npos) {
            string address;
            cout << "\tEnter New Address: ";
            cin.ignore();
            getline(cin, address);
            student.setAddress(address);

            size_t lastColon = line.find_last_of(':');
            if (lastColon != string::npos) {
                line.replace(lastColon + 2, string::npos, student.getAddress());
            }
            found = true;
        }
        outfile << line << endl;
    }

    if (!found) {
        cout << "\tStudent Not Found!" << endl;
    } else {
        cout << "\tData Updated!" << endl;
    }

    infile.close();
    outfile.close();
    remove("university.txt");
    rename("university_temp.txt", "university.txt");
}

void displayAll() {
    ifstream in("university.txt");
    if (!in) {
        cerr << "\tError: File Can't Open!" << endl;
        return;
    }

    string line;
    while (getline(in, line)) {
        cout << "\t" << line << endl;
    }
}

int main() {
    University student;

    bool exit = false;
    while (!exit) {
        system("cls");
        int val;
        cout << "\tWelcome To University Management System" << endl;
        cout << "\t***************************************" << endl;
        cout << "\t1. Add Student." << endl;
        cout << "\t2. Search Student." << endl;
        cout << "\t3. Update Data Of Student." << endl;
        cout << "\t4. Show All Records." << endl;
        cout << "\t5. Exit." << endl;
        cout << "\tEnter Your Choice: ";
        cin >> val;

        switch (val) {
            case 1:
                system("cls");
                add(student);
                Sleep(6000);
                break;
            case 2:
                system("cls");
                search();
                Sleep(6000);
                break;
            case 3:
                system("cls");
                update(student);
                Sleep(6000);
                break;
            case 4:
                system("cls");
                displayAll();
                Sleep(6000);
                break;
            case 5:
                system("cls");
                exit = true;
                cout << "\tGood Luck!" << endl;
                Sleep(3000);
                break;
            default:
                cout << "\tInvalid Choice! Please Try Again." << endl;
                Sleep(3000);
        }
    }
    return 0;
}

