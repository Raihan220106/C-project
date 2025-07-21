#include <iostream>
#include <string>

class BankAccount {
private:
    std::string accountNumber;
    std::string holderName;
    double balance;

public:
    // Konstruktor
    BankAccount(std::string accNumber, std::string name, double initialBalance) {
        accountNumber = accNumber;
        holderName = name;
        balance = initialBalance >= 0 ? initialBalance : 0; // Validasi saldo awal
    }

    // Destruktor
    ~BankAccount() {
        std::cout << "Akun " << holderName << " dengan nomor " << accountNumber << " telah ditutup." << std::endl;
    }

    // Metode untuk menyetor uang
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            std::cout << "Setoran berhasil: " << amount << ". Saldo saat ini: " << balance << std::endl;
        } else {
            std::cout << "Jumlah setoran harus positif." << std::endl;
        }
    }

    // Metode untuk menarik uang
    void withdraw(double amount) {
        if (amount > 0) {
            if (amount <= balance) {
                balance -= amount;
                std::cout << "Penarikan berhasil: " << amount << ". Saldo saat ini: " << balance << std::endl;
            } else {
                std::cout << "Saldo tidak cukup untuk menarik " << amount << "." << std::endl;
            }
        } else {
            std::cout << "Jumlah penarikan harus positif." << std::endl;
        }
    }

    // Metode untuk mentransfer uang
    void transfer(BankAccount &toAccount, double amount) {
        if (amount > 0) {
            if (amount <= balance) {
                balance -= amount;
                toAccount.balance += amount;
                std::cout << "Transfer berhasil: " << amount << " dari " << holderName << " ke " << toAccount.holderName << "." << std::endl;
                std::cout << "Saldo " << holderName << " saat ini: " << balance << std::endl;
                std::cout << "Saldo " << toAccount.holderName << " saat ini: " << toAccount.balance << std::endl;
            } else {
                std::cout << "Saldo tidak cukup untuk mentransfer " << amount << "." << std::endl;
            }
        } else {
            std::cout << "Jumlah transfer harus positif." << std::endl;
        }
    }
};

int main() {
    // Membuat objek akun bank
    BankAccount account1("123456", "Alice", 1000);
    BankAccount account2("654321", "Bob", 500);

    // Melakukan setoran
    account1.deposit(200);

    // Melakukan penarikan
    account1.withdraw(150);

    // Melakukan transfer
    account1.transfer(account2, 300);

    // Menutup program
    return 0;
}
