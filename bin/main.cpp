#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

/* ===================== STRUCTS ===================== */

struct Student {
    string name, surname, studentNumber;
};

struct DanceClass {
    string classId, className, instructor;
    double monthlyFee;
};

struct Schedule {
    string scheduleId, classId, day, time;
};

struct Payment {
    string studentNumber;
    double amount;
    string date;   // YYYY-MM-DD
    string method;
};

struct Attendance {
    string studentNumber, classId, date;
};

/* ===================== GLOBAL DATA ===================== */

vector<Student> students;
vector<DanceClass> classes;
vector<Schedule> schedules;
vector<Payment> payments;
vector<Attendance> attendanceHistory;

/* ===================== FILE HANDLING ===================== */

void saveStudents() {
    ofstream file("students.csv");
    for (auto &s : students)
        file << s.name << "," << s.surname << "," << s.studentNumber << "\n";
    file.close();
}

void loadStudents() {
    ifstream file("students.csv");
    Student s;
    while (getline(file, s.name, ',') &&
           getline(file, s.surname, ',') &&
           getline(file, s.studentNumber))
        students.push_back(s);
    file.close();
}

void savePayments() {
    ofstream file("payments.csv");
    for (auto &p : payments)
        file << p.studentNumber << "," << p.amount << "," << p.method << "," << p.date << "\n";
    file.close();
}

void loadPayments() {
    ifstream file("payments.csv");
    Payment p;
    string amount;
    while (getline(file, p.studentNumber, ',') &&
           getline(file, amount, ',') &&
           getline(file, p.method, ',') &&
           getline(file, p.date)) {
        p.amount = stod(amount);
        payments.push_back(p);
    }
    file.close();
}

/* ===================== STUDENTS ===================== */

void createStudent() {
    Student s;
    cout << "Name: "; cin >> s.name;
    cout << "Surname: "; cin >> s.surname;
    cout << "Student Number: "; cin >> s.studentNumber;
    students.push_back(s);
    saveStudents();
    cout << "Student added.\n";
}

void viewStudents() {
    cout << "\nName\tSurname\tStudent Number\n";
    for (auto &s : students)
        cout << s.name << "\t" << s.surname << "\t" << s.studentNumber << "\n";
}

void removeStudent() {
    string num;
    cout << "Student Number to remove: ";
    cin >> num;
    for (int i = 0; i < students.size(); i++) {
        if (students[i].studentNumber == num) {
            students.erase(students.begin() + i);
            saveStudents();
            cout << "Student removed.\n";
            return;
        }
    }
    cout << "Student not found.\n";
}

/* ===================== CLASSES ===================== */

void createClass() {
    DanceClass c;
    cout << "Class ID: "; cin >> c.classId;
    cout << "Class Name: "; cin >> c.className;
    cout << "Instructor: "; cin >> c.instructor;
    cout << "Monthly Fee: "; cin >> c.monthlyFee;
    classes.push_back(c);
    cout << "Class added.\n";
}

void viewClasses() {
    cout << "\nID\tName\tInstructor\tFee\n";
    for (auto &c : classes)
        cout << c.classId << "\t" << c.className << "\t"
             << c.instructor << "\tR" << c.monthlyFee << "\n";
}

/* ===================== PAYMENTS ===================== */

void addPayment() {
    Payment p;
    cout << "Student Number: "; cin >> p.studentNumber;
    cout << "Amount: "; cin >> p.amount;
    cout << "Method (Cash/EFT/Card): "; cin >> p.method;
    cout << "Date (YYYY-MM-DD): "; cin >> p.date;
    payments.push_back(p);
    savePayments();
    cout << "Payment recorded.\n";
}

void viewPayments() {
    cout << "\nStudent\tAmount\tMethod\tDate\n";
    for (auto &p : payments)
        cout << p.studentNumber << "\tR" << p.amount << "\t"
             << p.method << "\t" << p.date << "\n";
}

/* ===================== ATTENDANCE ===================== */

void markAttendance() {
    Attendance a;
    cout << "Student Number: "; cin >> a.studentNumber;
    cout << "Class ID: "; cin >> a.classId;
    cout << "Date (YYYY-MM-DD): "; cin >> a.date;
    attendanceHistory.push_back(a);
    cout << "Attendance marked.\n";
}

/* ===================== MONTHLY REPORT ===================== */

void monthlyReport() {
    string month;
    double total = 0;

    cout << "Enter Month (YYYY-MM): ";
    cin >> month;

    for (auto &p : payments)
        if (p.date.substr(0, 7) == month)
            total += p.amount;

    cout << "\nTotal Revenue for " << month << ": R" << total << "\n";
}

/* ===================== MENU ===================== */

void menu() {
    int choice;
    do {
        cout << "\n--- DANCE STUDIO CMS ---\n";
        cout << "1. Add Student\n";
        cout << "2. View Students\n";
        cout << "3. Remove Student\n";
        cout << "4. Add Class\n";
        cout << "5. View Classes\n";
        cout << "6. Record Payment\n";
        cout << "7. View Payments\n";
        cout << "8. Mark Attendance\n";
        cout << "9. Monthly Revenue Report\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: createStudent(); break;
            case 2: viewStudents(); break;
            case 3: removeStudent(); break;
            case 4: createClass(); break;
            case 5: viewClasses(); break;
            case 6: addPayment(); break;
            case 7: viewPayments(); break;
            case 8: markAttendance(); break;
            case 9: monthlyReport(); break;
            case 0: cout << "Goodbye!\n"; break;
            default: cout << "Invalid option.\n";
        }
    } while (choice != 0);
}

/* ===================== MAIN ===================== */

int main() {
    loadStudents();
    loadPayments();
    menu();
    return 0;
}
