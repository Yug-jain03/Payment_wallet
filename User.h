#ifndef USER_H
#define USER_H

#include <string>
#include <fstream>

class User {
private:
    std::string name;
    std::string userID;
    std::string pin;
    double balance;

public:
    User();
    User(const std::string &name, const std::string &userID, const std::string &pin);

    std::string getUserID() const;
    bool authenticate(const std::string &enteredPin) const;
    void registerUser();
    static bool userExists(const std::string &userID);
    static User login(const std::string &userID, const std::string &enteredPin);

    void displayDetails() const;
};

#endif
