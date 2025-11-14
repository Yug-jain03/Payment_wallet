#include <iostream>
#include <string>
#include <vector>
#include <limits>

#include "User.h"
#include "Wallet.h"
#include "Report.h"
#include "exceptions.h"
#include "Blockchain.h"   // ✅ Added for blockchain integration

using namespace std;

// ✅ Global Blockchain Ledger
Blockchain ledger;

void showMenu() {
    cout << "\n=====================================\n";
    cout << "        PAYMENT WALLET SYSTEM        \n";
    cout << "=====================================\n";
    cout << "1. Register\n";
    cout << "2. Login\n";
    cout << "3. Add Money\n";
    cout << "4. Transfer Money\n";
    cout << "5. Transaction History\n";
    cout << "6. Exit\n";
    cout << "7. View Blockchain Ledger\n";
    cout << "8. Verify Blockchain Integrity\n";
    cout << "=====================================\n";
    cout << "Enter your choice: ";
}

int main() {
    User currentUser;
    Wallet* userWallet = nullptr; 
    Report report;
    bool isLoggedIn = false;

    int choice;

    do {
        showMenu();
        cin >> choice;

        // ✅ Handle invalid input
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << ">> Invalid input! Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1: { // Register
                string name, id, pin;
                cout << "Enter Name: ";
                cin >> name;
                cout << "Enter UserID: ";
                cin >> id;
                cout << "Enter PIN: ";
                cin >> pin;

                if (User::userExists(id)) {
                    cout << ">> UserID already exists! Please try another.\n";
                } else {
                    User newUser(name, id, pin);
                    newUser.registerUser();
                    cout << ">> Registration successful!\n";
                }
                break;
            }

            case 2: { // Login
                string id, pin;
                cout << "Enter UserID: ";
                cin >> id;
                cout << "Enter PIN: ";
                cin >> pin;
                try {
                    currentUser = User::login(id, pin);
                    userWallet = new Wallet(currentUser.getUserID()); 
                    isLoggedIn = true;
                    cout << ">> Login successful!\n";
                    currentUser.displayDetails();
                } catch (const exception &e) {
                    cout << ">> Login failed: " << e.what() << endl;
                }
                break;
            }

            case 3: { // Add Money
                if (isLoggedIn) {
                    double amt;
                    cout << "Enter amount to add: ";
                    cin >> amt;
                    try {
                        userWallet->addMoney(amt);
                        ledger.addBlock("User " + currentUser.getUserID() + 
                                        " added ₹" + to_string(amt));  // ✅ Blockchain log
                        cout << ">> Amount added successfully!\n";
                        cout << ">> Current Balance: " << userWallet->getBalance() << endl;
                    } catch (const exception &e) {
                        cout << ">> Error: " << e.what() << endl;
                    }
                } else {
                    cout << ">> Please login first!\n";
                }
                break;
            }

            case 4: { // Transfer Money
                if (isLoggedIn) {
                    double amt;
                    string receiverID;
                    cout << "Enter receiver's UserID: ";
                    cin >> receiverID;
                    cout << "Enter amount to transfer: ";
                    cin >> amt;

                    if (!User::userExists(receiverID)) {
                        cout << ">> Receiver user not found!\n";
                        break;
                    }
                    try {
                        Wallet receiverWallet(receiverID); 
                        userWallet->transferMoney(receiverWallet, amt);
                        ledger.addBlock("User " + currentUser.getUserID() +
                                        " transferred ₹" + to_string(amt) + 
                                        " to " + receiverID);  // ✅ Blockchain log
                        cout << ">> Amount transferred successfully!\n";
                        cout << ">> Your New Balance: " << userWallet->getBalance() << endl;
                    } catch (const exception &e) {
                        cout << ">> Error: " << e.what() << endl;
                    }
                } else {
                    cout << ">> Please login first!\n";
                }
                break;
            }

            case 5: { // Transaction History
                if (isLoggedIn) {
                    report.showStatement(currentUser.getUserID());
                } else {
                    cout << ">> Please login first!\n";
                }
                break;
            }

            case 6: { // Exit
                cout << ">> Exiting... Thank you!\n";
                break;
            }

            case 7: { // ✅ Blockchain: View Ledger
                ledger.displayChain();
                break;
            }

            case 8: { // ✅ Blockchain: Verify Integrity
                cout << (ledger.verifyChain() 
                        ? "✅ Blockchain integrity verified.\n"
                        : "⚠️ Blockchain tampering detected!\n");
                break;
            }

            default: {
                cout << ">> Invalid choice! Try again.\n";
                break;
            }
        }

    } while (choice != 6);

    if (userWallet != nullptr) {
        delete userWallet;
    }

    return 0;
}
