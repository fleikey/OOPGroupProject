#ifndef STUDENT_H
#define STUDENT_H

#include "Person.h"

class Student : public Person
{
private:
    int id;
    int roomNumber;
    bool paymentStatus;

public:
    Student(const string &name, int id);

    void setRoomNumber(int number);
    int getRoomNumber() const;

    void payFees();
    bool checkPaymentStatus() const;

    void show() const override;
};

#endif
