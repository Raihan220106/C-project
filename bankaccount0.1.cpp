#include <iostream>
#include <string>
#include <iomanip>

class BankAccount {
private:
    // Encapsulated properties
    std::string accountNumber;
    std::string holderName;
    double balance;

public:
    // Constructor
    BankAccount(std::string accNum, std::string name, double initialBalance = 0.0) {
        accountNumber = accNum;
        holderName = name;

        // Validation for initial balance
        if (initialBalance < 0) {
            std::cout << "Initial balance cannot be negative. Setting balance to 0." << std::endl;
            balance = 0.0;
        } else {
            balance = initialBalance;
        }

        std::cout << "Account created for " << holderName << " with account number " << accountNumber << std::endl;
    }

    // Destructor
    ~BankAccount() {
        std::cout << "Account " << accountNumber << " for " << holderName << " is being closed." << std::endl;
    }

    // Getter methods
    std::string getAccountNumber() const {
        return accountNumber;
    }

    std::string getHolderName() const {
        return holderName;
    }

    double getBalance() const {
        return balance;
    }

    // Deposit method
    bool deposit(double amount) {
        if (amount <= 0) {
            std::cout << "Deposit amount must be positive." << std::endl;
            return false;
        }

        balance += amount;
        std::cout << "Deposited: " << amount << ". New balance: " << balance << std::endl;
        return true;
    }

    // Withdraw method with validation
    bool withdraw(double amount) {
        if (amount <= 0) {
            std::cout << "Withdrawal amount must be positive." << std::endl;
            return false;
        }

        if (amount > balance) {
            std::cout << "Insufficient funds. Current balance: " << balance << std::endl;
            return false;
        }

        balance -= amount;
        std::cout << "Withdrawn: " << amount << ". New balance: " << balance << std::endl;
        return true;
    }

    // Transfer method with validation
    bool transfer(BankAccount &recipient, double amount) {
        if (amount <= 0) {
            std::cout << "Transfer amount must be positive." << std::endl;
            return false;
        }

        if (amount > balance) {
            std::cout << "Insufficient funds for transfer. Current balance: " << balance << std::endl;
            return false;
        }

        balance -= amount;
        recipient.balance += amount;

        std::cout << "Transferred: " << amount << " from account " << accountNumber
                  << " to account " << recipient.accountNumber << std::endl;
        std::cout << "Your new balance: " << balance << std::endl;

        return true;
    }

    // Display account information
    void displayInfo() const {
        std::cout << "\n----- Account Information -----" << std::endl;
        std::cout << "Account Number: " << accountNumber << std::endl;
        std::cout << "Account Holder: " << holderName << std::endl;
        std::cout << "Current Balance: " << std::fixed << std::setprecision(2) << balance << std::endl;
        std::cout << "-------------------------------\n" << std::endl;
    }
};

// Main function to demonstrate the BankAccount class
int main() {
    // Create bank account objects
    BankAccount account1("AC001", "Raihan", 1000.0);
    BankAccount account2("AC002", "kankan", 500.0);

    // Display initial account information
    account1.displayInfo();
    account2.displayInfo();

    // Test deposit functionality
    account1.deposit(500.0);
    account1.deposit(-100.0); // Invalid deposit

    // Test withdrawal functionality
    account1.withdraw(200.0);
    account1.withdraw(2000.0); // Insufficient funds
    account1.withdraw(-50.0);  // Invalid withdrawal

    // Test transfer functionality
    account1.transfer(account2, 300.0);
    account2.transfer(account1, 1000.0); // Insufficient funds

    // Display final account information
    account1.displayInfo();
    account2.displayInfo();

    // Destructor will be called automatically when program ends

    return 0;
}
