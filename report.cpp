#include "Report.h"

void Report::showStatement(const string& userID) {
    ifstream file("transactions.txt");
    if (!file) {
        cout << "Transaction file not found!\n";
        return;
    }

    string line;
    bool found = false;
    cout << "\n--- Transaction History for " << userID << " ---\n";
    while (getline(file, line)) {
        if (line.find(userID) != string::npos) {
            cout << line << endl;
            found = true;
        }
    }

    if (!found) cout << "No transactions found for this user.\n";
    file.close();
}
