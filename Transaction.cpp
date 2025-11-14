#include "Transaction.h"
#include <fstream>
#include <ctime>

Transaction::Transaction(const std::string& type, double amount, const std::string& senderWalletID, const std::string& receiverWalletID) {
    this->type = type;
    this->amount = amount;
    this->senderWalletID = senderWalletID;
    this->receiverWalletID = receiverWalletID;

    time_t now = time(0);
    timestamp = ctime(&now);
    timestamp.pop_back();
}

std::string Transaction::getTransactionRecord() const {
    std::stringstream ss;
    ss << type << "," << amount << "," << senderWalletID << "," << receiverWalletID << "," << timestamp;
    return ss.str();
}
