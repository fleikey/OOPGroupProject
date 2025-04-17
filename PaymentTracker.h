#ifndef PAYMENT_H
#define PAYMENT_H

#include <string>
using namespace std;

class Payment {

    string studentID;
    double amountDue;
    double amountPaid;

public:
    Payment(const string& studentID, double amountDue);

    void makePayment(double amount);
    double getBalance() const;
    string getStudentID() const;
};

#endif
