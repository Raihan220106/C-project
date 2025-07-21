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
    // Constructor
    Product(int p_id, std::string p_name, double p_price, int p_stock, std::string p_category) {
        id = p_id;
        name = p_name;
        price = (p_price > 0) ? p_price : 0; // Ensure price is not negative
        stock = (p_stock >= 0) ? p_stock : 0; // Ensure stock is not negative
        category = p_category;
        std::cout << "Product Created: " << name << " (ID: " << id << ")\n";
    }

    // Destructor
    ~Product() {
        std::cout << "Product Deleted: " << name << " (ID: " << id << ")\n";
    }

    // Update Price Method
    void updatePrice(double newPrice) {
        if (newPrice > 0) {
            price = newPrice;
            std::cout << "Price updated for " << name << " to " << price << "\n";
        } else {
            std::cout << "Invalid price update!\n";
        }
    }

    // Update Stock Method
    void updateStock(int newStock) {
        if (newStock >= 0) {
            stock = newStock;
            std::cout << "Stock updated for " << name << " to " << stock << "\n";
        } else {
            std::cout << "Invalid stock update!\n";
        }
    }

    // Apply Discount Method
    void applyDiscount(double percentage) {
        if (percentage > 0 && percentage <= 100) {
            double discountAmount = (percentage / 100) * price;
            price -= discountAmount;
            std::cout << "Discount of " << percentage << "% applied to " << name << ". New price: " << price << "\n";
        } else {
            std::cout << "Invalid discount percentage!\n";
        }
    }

    // Display Product Info
    void displayInfo() {
        std::cout << "Product ID: " << id << " | Name: " << name << " | Price: " << price
                  << " | Stock: " << stock << " | Category: " << category << "\n";
    }
};

int main() {
    // Create Products
    Product product1(101, "Laptop", 1500.0, 10, "Electronics");
    Product product2(102, "Smartphone", 800.0, 20, "Electronics");

    // Perform Operations
    product1.updatePrice(1400.0);
    product1.applyDiscount(10);
    product1.updateStock(15);

    product2.applyDiscount(15);

    // Display Final Product Info
    product1.displayInfo();
    product2.displayInfo();

    return 0;
}
