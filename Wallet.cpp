#include "Wallet.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include "Blockchain.h"

// ✅ Use global blockchain ledger declared in main.cpp
extern Blockchain ledger;

Wallet::Wallet(const std::string& walletID) {
    this->walletID = walletID;
    this->balance = 0.0;
}

// ✅ Store each transaction persistently
void Wallet::storeTransaction(const Transaction& tx) {
    std::ofstream file("transactions.txt", std::ios::app);
    if (!file) {
        throw std::runtime_error("Unable to open transactions file.");
    }
    file << tx.getTransactionRecord() << std::endl;
    file.close();
}

// ✅ Add Money to wallet and record it in blockchain
void Wallet::addMoney(double amount) {
    if (amount <= 0)
        throw std::invalid_argument("Amount must be positive.");

    balance += amount;

    Transaction tx("Deposit", amount, walletID, walletID);
    storeTransaction(tx);

    ledger.addBlock("User " + walletID + " added ₹" + std::to_string(amount));
}

// ✅ Withdraw Money safely
void Wallet::withdrawMoney(double amount) {
    if (amount <= 0)
        throw std::invalid_argument("Amount must be positive.");
    if (balance < amount)
        throw std::runtime_error("Insufficient balance.");

    balance -= amount;

    Transaction tx("Withdrawal", amount, walletID, walletID);
    storeTransaction(tx);

    ledger.addBlock("User " + walletID + " withdrew ₹" + std::to_string(amount));
}

// ✅ Transfer Money and log in blockchain
void Wallet::transferMoney(Wallet& receiver, double amount) {
    if (amount <= 0)
        throw std::invalid_argument("Amount must be positive.");
    if (balance < amount)
        throw std::runtime_error("Insufficient balance.");

    balance -= amount;
    receiver.balance += amount;

    Transaction txSent("Transfer Sent", amount, walletID, receiver.walletID);
    Transaction txReceived("Transfer Received", amount, walletID, receiver.walletID);

    storeTransaction(txSent);
    storeTransaction(txReceived);

    ledger.addBlock("User " + walletID + " transferred ₹" +
                    std::to_string(amount) + " to " + receiver.walletID);
}

// ✅ Retrieve transaction history for this wallet
std::vector<Transaction> Wallet::getTransactionHistory() const {
    std::ifstream file("transactions.txt");
    if (!file) {
        throw std::runtime_error("Unable to open transactions file.");
    }

    std::string line;
    std::vector<Transaction> history;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string type, sender, receiver, timestamp;
        double amount;

        std::getline(ss, type, ',');
        ss >> amount;
        ss.ignore(1, ',');
        std::getline(ss, sender, ',');
        std::getline(ss, receiver, ',');
        std::getline(ss, timestamp);

        if (sender == walletID || receiver == walletID) {
            history.emplace_back(type, amount, sender, receiver);
        }
    }

    file.close();
    return history;
}
