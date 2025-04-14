#ifndef ADMIN_H
#define ADMIN_H
#include "PaymentTracker.h"
#include "Student.h"
#include <string>
using namespace std;

class Admin {
private:
    string name;
    string duty;

public:
    Admin(const string& name, const string& duty);

    void assignRoom(Student& student, Room& room);
    void checkPayments(const Payment& payment);
    void sendPaymentReminder(const Student& student);
};

#endif
