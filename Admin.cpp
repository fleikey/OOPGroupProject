

#include "Admin.h"
#include "PaymentTracker.h"
#include <iostream>
using namespace std;

Admin::Admin(const string& name, const string& duty)
    : name(name), duty(duty) {}

void Admin::assignRoom(Student& student, Room& room) {
    if (room.isAvailable()) {
        room.assignStudent(student);
        student.setRoomNumber(room.getNumber());
        cout << "Room " << room.getNumber() << " assigned to " << student.getName() << "\n";
    } else {
        cout << "Room " << room.getNumber() << " is not available.\n";
    }
}

void Admin::checkPayments(const Payment& payment) {
    cout << "Checking payments for student: " << payment.getStudentID() << "\n";
    cout << "Outstanding balance: $" << payment.getBalance() << "\n";
}

void Admin::sendPaymentReminder(const Student& student) {
    cout << "Reminder sent to student: " << student.getName() << "\n";
}

