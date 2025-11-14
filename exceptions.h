#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <exception>

class InvalidPINException : public std::exception {
public:
    const char* what() const throw() { return "Invalid PIN entered!"; }
};

class InsufficientBalanceException : public std::exception {
public:
    const char* what() const throw() { return "Insufficient balance!"; }
};

class InvalidAmountException : public std::exception {
public:
    const char* what() const throw() { return "Invalid transaction amount!"; }
};

class UserNotFoundException : public std::exception {
public:
    const char* what() const throw() { return "User not found!"; }
};

#endif
