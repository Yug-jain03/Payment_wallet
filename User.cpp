#include "User.h"
#include <iostream>

User::User() : name(""), userID(""), pin(""), balance(0.0) {}

User::User(const std::string &name, const std::string &userID, const std::string &pin)
    : name(name), userID(userID), pin(pin), balance(0.0) {}

std::string User::getUserID() const {
    return userID;
}

bool User::authenticate(const std::string &enteredPin) const {
    return pin == enteredPin;
}

void User::registerUser() {
    std::ofstream out("users.txt", std::ios::app);
    out << name << "," << userID << "," << pin << "," << balance << std::endl;
    out.close();
}

bool User::userExists(const std::string &userID) {
    std::ifstream in("users.txt");
    std::string line;
    while (std::getline(in, line)) {
        if (line.find(userID) != std::string::npos) {
            in.close();
            return true;
        }
    }
    in.close();
    return false;
}

User User::login(const std::string &userID, const std::string &enteredPin) {
    std::ifstream in("users.txt");
    std::string line;
    while (std::getline(in, line)) {
        std::string uname, uid, upin;
        double ubalance;
        size_t p1 = line.find(",");
        size_t p2 = line.find(",", p1 + 1);
        size_t p3 = line.find(",", p2 + 1);

        uname = line.substr(0, p1);
        uid = line.substr(p1 + 1, p2 - p1 - 1);
        upin = line.substr(p2 + 1, p3 - p2 - 1);
        ubalance = std::stod(line.substr(p3 + 1));

        if (uid == userID && upin == enteredPin) {
            in.close();
            User u(uname, uid, upin);
            return u;
        }
    }
    in.close();
    throw std::runtime_error("Login failed: Invalid credentials");
}

void User::displayDetails() const {
    std::cout << "User: " << name << " | ID: " << userID << " | Balance: " << balance << std::endl;
}
