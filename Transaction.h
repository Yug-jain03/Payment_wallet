#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <ctime>
#include <sstream>

class Transaction {
public:
    std::string type;
    double amount;
    std::string senderWalletID;
    std::string receiverWalletID;
    std::string timestamp;

    Transaction(const std::string& type, double amount, const std::string& senderWalletID, const std::string& receiverWalletID);

    std::string getTransactionRecord() const;
};

#endif
