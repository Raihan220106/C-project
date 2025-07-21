#include <iostream>
#include <string>

class BankAccount {
private:
    std::string accountNumber;
    std::string holderName;
    double balance;

public:
    // Constructor
    BankAccount(std::string accNumber, std::string name, double initialBalance) {
        accountNumber = accNumber;
        holderName = name;
        balance = (initialBalance >= 0) ? initialBalance : 0; // Pastikan saldo tidak negatif
        std::cout << "Account Created: " << holderName << " (" << accountNumber << ")\n";
    }

    // Destructor
    ~BankAccount() {
        std::cout << "Account Closed: " << holderName << " (" << accountNumber << ")\n";
    }

    // Deposit Method
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            std::cout << "Deposited: " << amount << ", New Balance: " << balance << "\n";
        } else {
            std::cout << "Invalid deposit amount!\n";
        }
    }

    // Withdraw Method
    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            std::cout << "Withdrawn: " << amount << ", New Balance: " << balance << "\n";
        } else {
            std::cout << "Invalid withdrawal! Insufficient balance or negative amount.\n";
        }
    }

    // Transfer Method
    void transfer(BankAccount &recipient, double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            recipient.deposit(amount);
            std::cout << "Transferred: " << amount << " to " << recipient.holderName << "\n";
        } else {
            std::cout << "Transfer failed! Insufficient balance or invalid amount.\n";
        }
    }

    // Display Account Info
    void display() {
        std::cout << "Account: " << accountNumber << " | Holder: " << holderName << " | Balance: " << balance << "\n";
    }
};

int main() {
    // Create Bank Accounts
    BankAccount acc1("12345", "Raihan", 1000.0);
    BankAccount acc2("678910", "Fandi", 500.0);

    // Perform Transactions
    acc1.deposit(500);
    acc1.withdraw(300);
    acc1.transfer(acc2, 200);

    // Display Final Balances
    acc1.display();
    acc2.display();

    return 0;
}

