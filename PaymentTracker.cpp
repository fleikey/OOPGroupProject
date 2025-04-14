#include "PaymentTracker.h"
using namespace std;

Payment::Payment(const std::string& studentID, double amountDue)
    : studentID(studentID), amountDue(amountDue), amountPaid(0.0) {}

void Payment::makePayment(double amount) {
    amountPaid += amount;
    if (amountPaid > amountDue) {
        amountPaid = amountDue; // prevent overpaying
    }
}

double Payment::getBalance() const {
    return amountDue - amountPaid;
}

string Payment::getStudentID() const {
    return studentID;
}
