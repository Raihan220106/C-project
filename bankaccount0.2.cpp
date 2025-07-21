#include <iostream>
#include <string>

class BankAccount {
private:
    std::string accountNumber;
    std::string holderName;
    double balance;

public:
    // Konstruktor
    BankAccount(std::string accNum, std::string holder, double initialBalance) : accountNumber(accNum), holderName(holder), balance(initialBalance) {
        std::cout << "Rekening Bank untuk " << holderName << " dibuat." << std::endl;
    }

    // Destruktor
    ~BankAccount() {
        std::cout << "Rekening Bank untuk " << holderName << " ditutup." << std::endl;
    }

    // Metode untuk deposit
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            std::cout << "Deposit sebesar Rp" << amount << " berhasil." << std::endl;
        } else {
            std::cout << "Jumlah deposit tidak valid." << std::endl;
        }
    }

    // Metode untuk penarikan
    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            std::cout << "Penarikan sebesar Rp" << amount << " berhasil." << std::endl;
        } else {
            std::cout << "Jumlah penarikan tidak valid atau saldo tidak mencukupi." << std::endl;
        }
    }

    // Metode untuk transfer
    void transfer(BankAccount& recipient, double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            recipient.deposit(amount);
            std::cout << "Transfer sebesar Rp" << amount << " ke " << recipient.holderName << " berhasil." << std::endl;
        } else {
            std::cout << "Jumlah transfer tidak valid atau saldo tidak mencukupi." << std::endl;
        }
    }

    // Metode untuk mendapatkan saldo
    double getBalance() const {
        return balance;
    }

    // Metode untuk mendapatkan nomor rekening
    std::string getAccountNumber() const {
        return accountNumber;
    }

    // Metode untuk mendapatkan nama pemegang rekening
    std::string getHolderName() const {
        return holderName;
    }
};

int main() {
    // Membuat objek BankAccount
    BankAccount account1("1234567890", "John Doe", 1000000);
    BankAccount account2("0987654321", "Jane Doe", 500000);

    // Melakukan deposit, penarikan, dan transfer
    account1.deposit(500000);
    account2.withdraw(200000);
    account1.transfer(account2, 300000);

    // Menampilkan saldo
    std::cout << "Saldo " << account1.getHolderName() << ": Rp" << account1.getBalance() << std::endl;
    std::cout << "Saldo " << account2.getHolderName() << ": Rp" << account2.getBalance() << std::endl;

    return 0;
}
