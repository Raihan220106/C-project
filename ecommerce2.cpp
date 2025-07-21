#include <iostream>
#include <string>

class Product {
private:
    int id;
    std::string name;
    double price;
    int stock;
    std::string category;

public:
    // Konstruktor
    Product(int id, std::string name, double price, int stock, std::string category)
        : id(id), name(name), price(price), stock(stock), category(category) {
        std::cout << "Produk " << name << " ditambahkan ke katalog." << std::endl;
    }

    // Destruktor
    ~Product() {
        std::cout << "Produk " << name << " dihapus dari katalog." << std::endl;
    }

    // Metode untuk memperbarui harga
    void updatePrice(double newPrice) {
        price = newPrice;
        std::cout << "Harga " << name << " diperbarui menjadi Rp" << price << std::endl;
    }

    // Metode untuk memperbarui stok
    void updateStock(int newStock) {
        stock = newStock;
        std::cout << "Stok " << name << " diperbarui menjadi " << stock << std::endl;
    }

    // Metode untuk menampilkan informasi produk
    void displayInfo() const {
        std::cout << "ID: " << id << std::endl;
        std::cout << "Nama: " << name << std::endl;
        std::cout << "Harga: Rp" << price << std::endl;
        std::cout << "Stok: " << stock << std::endl;
        std::cout << "Kategori: " << category << std::endl;
    }

    // Metode untuk menghitung harga setelah diskon
    double calculateDiscountedPrice(double discountPercentage) const {
        if (discountPercentage > 0 && discountPercentage <= 100) {
            return price * (1 - discountPercentage / 100);
        } else {
            std::cout << "Persentase diskon tidak valid." << std::endl;
            return price; // Mengembalikan harga asli jika diskon tidak valid
        }
    }

    // Metode untuk mendapatkan harga
    double getPrice() const{
        return price;
    }

    // Metode untuk mendapatkan stok
    int getStock() const{
        return stock;
    }

    // Metode untuk mendapatkan nama produk
    std::string getName() const{
        return name;
    }
};

int main() {
    // Membuat objek Product
    Product product1(1, "Laptop", 10000000, 10, "Elektronik");
    Product product2(2, "Buku", 50000, 50, "Buku");

    // Memperbarui harga dan stok
    product1.updatePrice(9500000);
    product2.updateStock(40);

    // Menampilkan informasi produk
    std::cout << "\nInformasi Produk 1:" << std::endl;
    product1.displayInfo();

    std::cout << "\nInformasi Produk 2:" << std::endl;
    product2.displayInfo();

    // Menghitung harga setelah diskon
    double discountedPrice1 = product1.calculateDiscountedPrice(10); // Diskon 10%
    double discountedPrice2 = product2.calculateDiscountedPrice(20); // Diskon 20%

    std::cout << "\nHarga " << product1.getName() << " setelah diskon 10%: Rp" << discountedPrice1 << std::endl;
    std::cout << "Harga " << product2.getName() << " setelah diskon 20%: Rp" << discountedPrice2 << std::endl;

    return 0;
}
