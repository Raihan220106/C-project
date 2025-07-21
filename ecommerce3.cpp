#include <iostream>
#include <string>
#include <iomanip> // Untuk std::setprecision

class Product {
private:
    int id;
    std::string name;
    double price;
    int stock;
    std::string category;

public:
    // Konstruktor
    Product(int productId, std::string productName, double productPrice, int productStock, std::string productCategory) {
        id = productId;
        name = productName;
        price = productPrice >= 0 ? productPrice : 0; // Validasi harga
        stock = productStock >= 0 ? productStock : 0; // Validasi stok
        category = productCategory;
    }

    // Destruktor
    ~Product() {
        std::cout << "Produk " << name << " dengan ID " << id << " telah dihapus." << std::endl;
    }

    // Metode untuk memperbarui harga
    void updatePrice(double newPrice) {
        if (newPrice >= 0) {
            price = newPrice;
            std::cout << "Harga produk " << name << " telah diperbarui menjadi: " << price << std::endl;
        } else {
            std::cout << "Harga tidak boleh negatif." << std::endl;
        }
    }

    // Metode untuk memperbarui stok
    void updateStock(int newStock) {
        if (newStock >= 0) {
            stock = newStock;
            std::cout << "Stok produk " << name << " telah diperbarui menjadi: " << stock << std::endl;
        } else {
            std::cout << "Stok tidak boleh negatif." << std::endl;
        }
    }

    // Metode untuk menampilkan informasi produk
    void displayInfo() const {
        std::cout << "ID Produk: " << id << std::endl;
        std::cout << "Nama Produk: " << name << std::endl;
        std::cout << "Harga: " << std::fixed << std::setprecision(2) << price << std::endl;
        std::cout << "Stok: " << stock << std::endl;
        std::cout << "Kategori: " << category << std::endl;
    }

    // Metode untuk menghitung diskon
    double calculateDiscount(double discountPercentage) const {
        if (discountPercentage < 0 || discountPercentage > 100) {
            std::cout << "Persentase diskon tidak valid. Harus antara 0 dan 100." << std::endl;
            return price; // Kembalikan harga asli jika diskon tidak valid
        }
        double discountAmount = (discountPercentage / 100) * price;
        return price - discountAmount; // Kembalikan harga setelah diskon
    }
};

int main() {
    // Membuat objek produk
    Product product1(1, "Laptop", 1500.00, 10, "Elektronik");
    Product product2(2, "Smartphone", 800.00, 20, "Elektronik");

    // Menampilkan informasi produk
    product1.displayInfo();
    product2.displayInfo();

    // Memperbarui harga dan stok
    product1.updatePrice(1400.00);
    product1.updateStock(8);


    // Menutup program
    return 0;
}
