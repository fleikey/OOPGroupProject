#include "Student.h"
#include <iostream>

Student::Student(const string &name, int id)
    : Person(name), id(id), roomNumber(-1), paymentStatus(false) {}

void Student::setRoomNumber(int number)
{
    roomNumber = number;
}

int Student::getRoomNumber() const
{
    return roomNumber;
}

void Student::payFees()
{
    paymentStatus = true;
    cout << name << " has paid the fees.\n";
}

bool Student::checkPaymentStatus() const
{
    return paymentStatus;
}

void Student::show() const
{
    cout << "Student Name: " << name << ", ID: " << id << ", Room: " << roomNumber
         << ", Payment: " << (paymentStatus ? "Paid" : "Unpaid") << endl;
}
