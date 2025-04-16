#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>
#include "Person.h"
#include "Student.h"
#include "Room.h"
#include "Admin.h"
#include "Dormitory.h"
#include "PaymentTracker.h"

using namespace std;

// Date utility for payment deadline tracking
class DateUtility {
public:
    static string getCurrentDate() {
        auto now = chrono::system_clock::now();
        time_t tt = chrono::system_clock::to_time_t(now);
        tm local_tm = *localtime(&tt);
        
        stringstream ss;
        ss << put_time(&local_tm, "%Y-%m-%d");
        return ss.str();
    }
    
    static bool isPaymentOverdue(const string& deadline) {
        return !deadline.empty();
    }
};

// Function to display the main menu
void displayMenu() {
    cout << "\n===== DORMITORY MANAGEMENT SYSTEM =====\n";
    cout << "1. Add Student\n";
    cout << "2. Add Room\n";
    cout << "3. Assign Student to Room\n";
    cout << "4. Make Payment\n";
    cout << "5. Check Payment Status\n";
    cout << "6. Send Payment Reminders\n";
    cout << "7. Display Dormitory Status\n";
    cout << "8. Display All Students\n";
    cout << "9. Display Payment Records\n";
    cout << "0. Exit\n";
    cout << "Choice: ";
}

// Function to display dormitory status
void displayDormitoryStatus(const vector<Room>& rooms, const string& dormName) {
    cout << "\n===== " << dormName << " DORMITORY STATUS =====\n";
    cout << "Total Rooms: " << rooms.size() << "\n";
    
    int availableRooms = 0;
    for (const auto& room : rooms) {
        if (room.isAvailable()) availableRooms++;
    }
    
    cout << "Available Rooms: " << availableRooms << "\n";
    cout << "Occupied Rooms: " << (rooms.size() - availableRooms) << "\n";
    
    cout << "\nRoom Status:\n";
    cout << left << setw(10) << "Room #" << setw(15) << "Status" << "\n";
    cout << "-------------------------\n";
    
    for (const auto& room : rooms) {
        cout << left << setw(10) << room.getNumber() 
             << setw(15) << (room.isAvailable() ? "Available" : "Occupied") << "\n";
    }
    cout << "===============================\n\n";
}

int main() {
    // Initialize system components
    Admin admin("John Doe", "Dormitory Manager");
    Dormitory mainDormitory("Main Building");
    vector<Payment> payments;
    vector<Student*> students; // Use pointers to avoid copy constructor issues
    
    // Add some initial rooms
    for (int i = 101; i <= 110; i++) {
        mainDormitory.addRoom(Room(i));
    }
    
    int choice;
    bool running = true;
    
    cout << "Welcome to the Dormitory Management System\n";
    
    while (running) {
        displayMenu();
        cin >> choice;
        
        switch (choice) {
            case 1: {  // Add Student
                string name;
                int id;
                
                cout << "Enter student name: ";
                cin.ignore();
                getline(cin, name);
                
                cout << "Enter student ID: ";
                cin >> id;
                
                // Check if student ID already exists
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
                    
                    // Create payment record
                    Payment newPayment(to_string(id), 500.0); // $500 as default fee
                    payments.push_back(newPayment);
                    
                    cout << "Student added successfully!\n";
                } else {
                    cout << "A student with this name already exists.\n";
                }
                break;
            }
            
            case 2: {  // Add Room
                int roomNumber;
                cout << "Enter room number: ";
                cin >> roomNumber;
                
                mainDormitory.addRoom(Room(roomNumber));
                cout << "Room added successfully!\n";
                break;
            }
            
            case 3: {  // Assign Student to Room
                string name;
                int roomNum;
                
                cout << "Enter student name: ";
                cin.ignore();
                getline(cin, name);
                
                cout << "Enter room number: ";
                cin >> roomNum;
                
                // Find student
                Student* foundStudent = nullptr;
                for (auto& student : students) {
                    if (student->getName() == name) {
                        foundStudent = student;
                        break;
                    }
                }
                
                // Find room
                Room* foundRoom = nullptr;
                vector<Room>& rooms = mainDormitory.getRooms(); // You'll need to add this accessor
                for (auto& room : rooms) {
                    if (room.getNumber() == roomNum) {
                        foundRoom = &room;
                        break;
                    }
                }
                
                if (foundStudent && foundRoom) {
                    admin.assignRoom(*foundStudent, *foundRoom);
                } else {
                    if (!foundStudent) cout << "Student not found.\n";
                    if (!foundRoom) cout << "Room not found.\n";
                }
                
                break;
            }
            
            case 4: {  // Make Payment
                string name;
                double amount;
                
                cout << "Enter student name: ";
                cin.ignore();
                getline(cin, name);
                
                cout << "Enter payment amount is UZS: ";
                cin >> amount;
                
                // Find student ID
                int studentId = -1;
                for (auto& student : students) {
                    if (student->getName() == name) {
                        studentId = student->getID(); // Using room number as ID for simplicity
                        break;
                    }
                }
                
                if (studentId != -1) {
                    // Find payment record
                    for (auto& payment : payments) {
                        if (payment.getStudentID() == to_string(studentId)) {
                            payment.makePayment(amount);
                            cout << "Payment of " << amount << "UZS recorded.\n";
                            cout << "Remaining balance: " << payment.getBalance() << " UZS\n";
                            
                            // Update student payment status if paid in full
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
                    cout << "Student not found.\n";
                }
                break;
            }
            
            case 5: {  // Check Payment Status
                string name;
                cout << "Enter student name: ";
                cin.ignore();
                getline(cin, name);
                
                // Find student ID
                int studentId = -1;
                for (auto& student : students) {
                    if (student->getName() == name) {
                        studentId = student->getID(); // Using room number as ID for simplicity
                        break;
                    }
                }
                
                if (studentId != -1) {
                    // Find payment record
                    for (auto& payment : payments) {
                        if (payment.getStudentID() == to_string(studentId)) {
                            admin.checkPayments(payment);
                            break;
                        }
                    }
                } else {
                    cout << "Student not found.\n";
                }
                break;
            }
            
            case 6: {  // Send Payment Reminders
                cout << "Sending payment reminders to students with outstanding balances...\n";
                
                for (auto& student : students) {
                    int studentId = student->getID();
                    
                    // Find payment record
                    for (auto& payment : payments) {
                        if (payment.getStudentID() == to_string(studentId) && payment.getBalance() > 0) {
                            admin.sendPaymentReminder(*student);
                            break;
                        }
                    }
                }
                break;
            }
            
            case 7: {  // Display Dormitory Status
                vector<Room>& rooms = mainDormitory.getRooms(); // You'll need to add this accessor
                displayDormitoryStatus(rooms, "Main Building");
                break;
            }
            
            case 8: {  // Display All Students
                cout << "\n===== STUDENT DIRECTORY =====\n";
                if (students.empty()) {
                    cout << "No students registered yet.\n";
                } else {
                    for (auto& student : students) {
                        student->show();
                    }
                }
                cout << "===========================\n\n";
                break;
            }
            
            case 9: {  // Display Payment Records
                cout << "\n===== PAYMENT RECORDS =====\n";
                cout << left << setw(15) << "Student ID" << setw(15) << "Balance" << "\n";
                cout << "------------------------------\n";
                
                for (const auto& payment : payments) {
                    cout << left << setw(15) << payment.getStudentID()
                         << setw(15) << "$" << fixed << setprecision(2) << payment.getBalance() << "\n";
                }
                cout << "==============================\n\n";
                break;
            }
            
            case 0:  // Exit
                cout << "Thank you for using the Dormitory Management System!\n";
                running = false;
                break;
                
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }
    
    // Clean up dynamically allocated memory
    for (auto& student : students) {
        delete student;
    }
    
    return 0;
}
