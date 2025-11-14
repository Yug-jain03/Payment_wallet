#ifndef REPORT_H
#define REPORT_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

template <typename T>
class TransactionList {
    vector<T> transactions;
public:
    void addTransaction(T t) { transactions.push_back(t); }
    void showAll() {
        if (transactions.empty()) {
            cout << "No transactions to display!\n";
            return;
        }
        for (auto &t : transactions) cout << t << endl;
    }
};

class Report {
public:
    void showStatement(const string& userID);
};

#endif
