#ifndef WALLET_H
#define WALLET_H

#include <string>
#include <vector>
#include "Transaction.h"

class Wallet {
private:
    void storeTransaction(const Transaction& tx);

public:
    std::string walletID;
    double balance;

    Wallet(const std::string& walletID);

    void addMoney(double amount);
    void withdrawMoney(double amount);
    void transferMoney(Wallet& receiver, double amount);

    std::vector<Transaction> getTransactionHistory() const;

    double getBalance() const { return balance; }
};

#endif
