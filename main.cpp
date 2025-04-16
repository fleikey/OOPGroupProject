#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>
#include "Admin.h"
#include "Student.h"
#include "Room.h"
#include "Dormitory.h"
#include "PaymentTracker.h"

using namespace std;

int main() {
    Admin admin("John Doe", "Dormitory Manager");
    Dormitory mainDormitory("Main Building");
    PaymentTracker paymentTracker;
    vector<Student> students;
    
    for (int i = 101; i <= 110; i++) {
        mainDormitory.addRoom(i);
    }
    
    int choice;
    bool running = true;
    
    cout << "Welcome to the Dormitory Management System\n";
    
    while (running) {
        displayMenu();
        cin >> choice;
        
        switch (choice) {
            case 1: {
                string name;
                int id;
                
                cout << "Enter student name: ";
                cin.ignore();
                getline(cin, name);
                
                cout << "Enter student ID: ";
                cin >> id;
                
                students.emplace_back(name, id);
                paymentTracker.trackPayment(students.back());
                
                cout << "Student added successfully!\n";
                break;
            }
            
            case 2: {
                int roomNumber;
                cout << "Enter room number: ";
                cin >> roomNumber;
                
                mainDormitory.addRoom(roomNumber);
                break;
            }
            
            case 3: {
                int studentId;
                cout << "Enter student ID: ";
                cin >> studentId;
                
                Student* selectedStudent = nullptr;
                for (auto& student : students) {
                    if (student.getID() == studentId) {
                        selectedStudent = &student;
                        break;
                    }
                }
                
                if (selectedStudent) {
                    Room* availableRoom = mainDormitory.findAvailableRoom();
                    if (availableRoom) {
                        admin.assignRoom(*selectedStudent, *availableRoom);
                    } else {
                        cout << "No available rooms in " << mainDormitory.getName() << " dormitory.\n";
                    }
                } else {
                    cout << "Student with ID " << studentId << " not found.\n";
                }
                break;
            }
            
            case 4: {
                int studentId;
                double amount;
                
                cout << "Enter student ID: ";
                cin >> studentId;
                
                cout << "Enter payment amount: $";
                cin >> amount;
                
                paymentTracker.makePaymentForStudent(to_string(studentId), amount);
                
                for (auto& student : students) {
                    if (student.getID() == studentId) {
                        Payment* payment = paymentTracker.getPaymentForStudent(to_string(studentId));
                        if (payment && payment->getBalance() == 0) {
                            student.setPaymentStatus(true);
                        }
                        break;
                    }
                }
                break;
            }
            
            case 5: {
                int studentId;
                cout << "Enter student ID: ";
                cin >> studentId;
                
                bool found = false;
                for (auto& student : students) {
                    if (student.getID() == studentId) {
                        found = true;
                        Payment* payment = paymentTracker.getPaymentForStudent(to_string(studentId));
                        if (payment) {
                            admin.checkPayments(*payment);
                        } else {
                            cout << "No payment record found for this student.\n";
                        }
                        break;
                    }
                }
                
                if (!found) {
                    cout << "Student with ID " << studentId << " not found.\n";
                }
                break;
            }
            
            case 6: {
                cout << "Sending payment reminders to students with outstanding balances...\n";
                
                for (auto& student : students) {
                    Payment* payment = paymentTracker.getPaymentForStudent(to_string(student.getID()));
                    if (payment && payment->getBalance() > 0) {
                        admin.sendPaymentReminder(student);
                    }
                }
                break;
            }
            
            case 7: {
                mainDormitory.show();
                break;
            }
            
            case 8: {  
                cout << "\n===== STUDENT DIRECTORY =====\n";
                if (students.empty()) {
                    cout << "No students registered yet.\n";
                } else {
                    for (auto& student : students) {
                        student.show();
                        cout << "----------------------------\n";
                    }
                }
                break;
            }
            
            case 9: {
                paymentTracker.displayAllPayments();
                break;
            }
            
            case 0: 
                cout << "Thank you for using the Dormitory Management System!\n";
                running = false;
                break;
                
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }
    
    return 0;
}
