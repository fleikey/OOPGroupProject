#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "Person.h"
#include "Student.h"
#include "Room.h"
#include "Admin.h"
#include "Dormitory.h"
#include "PaymentTracker.h"

using namespace std;

void displayMenu() {
    cout << "\n===== DORMITORY MANAGEMENT SYSTEM ====="<<endl;
    cout << "1. Add Student"<<endl;
    cout << "2. Add Room"<<endl;
    cout << "3. Assign Student to Room"<<endl;
    cout << "4. Make Payment"<<endl;
    cout << "5. Check Payment Status"<<endl;
    cout << "6. Send Payment Reminders"<<endl;
    cout << "7. Display Dormitory Status"<<endl;
    cout << "8. Display All Students"<<endl;
    cout << "9. Display Payment Records"<<endl;
    cout << "0. Exit"<<endl;
    cout << "Choice: ";
}

void displayDormitoryStatus(const vector<Room>& rooms, const string& dormName) {
    cout << "\n===== " << dormName << " DORMITORY STATUS ====="<<endl;
    cout << "Total Rooms: " << rooms.size() << endl;
    
    int availableRooms = 0;
    for (const auto& room : rooms) {
        if (room.isAvailable()) availableRooms++;
    }
    
    cout << "Available Rooms: " << availableRooms << endl;
    cout << "Occupied Rooms: " << (rooms.size() - availableRooms) << endl;
    
    cout << "\nRoom Status:"<<endl;
    cout << left << setw(10) << "Room #" << setw(15) << "Status" << endl;
    cout << "-------------------------"<<endl;
    
    for (const auto& room : rooms) {

        cout << left << setw(10) << room.getNumber() 
             << setw(15) << (room.isAvailable() ? "Available" : "Occupied") << endl;
    }
    cout << "==============================="<<endl<<endl;
}

int main() {
    Admin admin("Fotima opa", "Komendant");
    Dormitory dorm("UWED dorm");
    vector<Payment> payments;
    vector<Student*> students; 

        for (int i = 101; i <= 110; i++) {
        dorm.addRoom(Room(i));
    }
    
    int choice;
    bool running = true;
    
    cout << "Welcome to the Dormitory Management System"<<endl;
    
    while (running) {
        displayMenu();
        cin >> choice;
        
        switch (choice) {
            case 1: {  //student
                string name;
                int id;
                
                cout << "Enter student name: ";
                cin.ignore();
                getline(cin, name);
                
                cout << "Enter student ID: ";
                cin >> id;
                
                bool exists = false;
                for (const auto& student : students) {
                    if (student->getName() == name) {
                        exists = true;
                        break;
                    }
                }
                
                if (!exists) {
                    Student* newStudent = new Student(name, id);
                    students.push_back(newStudent);
                    
                    Payment newPayment(to_string(id), 640000);
                    payments.push_back(newPayment);
                    
                    cout << "Student added successfully!"<<endl;
                } else {
                    cout << "A student with this name already exists."<<endl;
                }
                break;
            }
            
            case 2: {  //room
                int roomNumber;
                cout << "Enter room number: ";
                cin >> roomNumber;
                
                dorm.addRoom(Room(roomNumber));
                cout << "Room added successfully!"<<endl;
                break;
            }
            
            case 3: {  //assigns a student to room
                string name;
                int roomNum;
                
                cout << "Enter student name: ";
                cin.ignore();
                getline(cin, name);
                
                cout << "Enter room number: ";
                cin >> roomNum;
                
                Student* foundStudent = nullptr;
                for (auto& student : students) {
                    if (student->getName() == name) {
                        foundStudent = student;
                        break;
                    }
                }
                
                Room* foundRoom = nullptr;
                vector<Room>& rooms = dorm.getRooms();
                for (auto& room : rooms) {
                    if (room.getNumber() == roomNum) {
                        foundRoom = &room;
                        break;
                    }
                }
                
                if (foundStudent && foundRoom) {
                    admin.assignRoom(*foundStudent, *foundRoom);
                } else {
                    if (!foundStudent) cout << "Student not found."<<endl;
                    if (!foundRoom) cout << "Room not found."<<endl;
                }
                
                break;
            }
            
            case 4: {  //makes payment
                string name;
                double amount;
                
                cout << "Enter student name: ";
                cin.ignore();
                getline(cin, name);
                
                cout << "Enter payment amount is UZS: ";
                cin >> amount;
                int studentId = -1;
                for (auto& student : students) {
                    if (student->getName() == name) {
                        studentId = student->getID();
                        break;
                    }
                }
                
                if (studentId != -1) {
                    for (auto& payment : payments) {
                        if (payment.getStudentID() == to_string(studentId)) {
                            payment.makePayment(amount);
                            cout << "Payment of " << amount << "UZS recorded.\n";
                            cout << "Remaining debt: " << payment.getBalance() << " UZS\n";
                            
                            if (payment.getBalance() == 0) {
                                for (auto& student : students) {
                                    if (student->getName() == name) {
                                        student->payFees();
                                        break;
                                    }
                                }
                            }
                            break;
                        }
                    }
                } else {
                    cout << "Student not found."<<endl;
                }
                break;
            }
            
            case 5: {  //payment status
                string name;
                cout << "Enter student name: ";
                cin.ignore();
                getline(cin, name);
                int studentId = -1;
                for (auto& student : students) {
                    if (student->getName() == name) {
                        studentId = student->getID();
                        break;
                    }
                }
                
                if (studentId != -1) {
                    for (auto& payment : payments) {
                        if (payment.getStudentID() == to_string(studentId)) {
                            admin.checkPayments(payment);
                            break;
                        }
                    }
                } else {
                    cout << "Student not found."<<endl;
                }
                break;
            }
            
            case 6: {  //sends reminders to students
                cout << "Sending payment reminders to students with deby"<<endl;
                
                for (auto& student : students) {
                    int studentId = student->getID();
                    for (auto& payment : payments) {
                        if (payment.getStudentID() == to_string(studentId) && payment.getBalance() > 0) {
                            admin.sendPaymentReminder(*student);
                            break;
                        }
                    }
                }
                break;
            }
            
            case 7: {  //displays rooms
                vector<Room>& rooms = dorm.getRooms();
                displayDormitoryStatus(rooms, "UWED dorm");
                break;
            }
            
            case 8: {  //displays all the students
                cout << "\n===== STUDENT DIRECTORY ====="<<endl;
                if (students.empty()) {
                    cout << "No students registered yet."<<endl;
                } else {
                    for (auto& student : students) {
                        student->show();
                    }
                }
                cout << "==========================="<<endl<<endl;
                break;
            }
            
            case 9: { //displays payment records
                cout << "\n===== PAYMENT RECORDS ====="<<endl;
                cout << left << setw(15) << "Student ID" << setw(15) << "Debt" << endl;
                cout << "------------------------------"<<endl;
                
                for (const auto& payment : payments) {
                    cout << left << setw(15) << payment.getStudentID()
                         << setw(15) << "UZS" << fixed << setprecision(2) << payment.getBalance() << endl;
                }
                cout << "=============================="<<endl;
                break;
            }
            
            case 0:
                cout << "Thank you for using our Dormitory Management System!"<<endl;
                running = false;
                break;
                
            default:
                cout << "Invalid choice. Please try again."<<endl;
                break;
        }
    }
    
    for (auto& student : students) {
        delete student;
    }
    
    return 0;
}
