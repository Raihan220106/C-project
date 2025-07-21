#include <iostream>
#include <string>
#include <iomanip>
#include <vector>

// Product class for e-commerce catalog
class Product {
private:
    // Encapsulated properties
    int id;
    std::string name;
    double price;
    int stock;
    std::string category;
    double discountPercentage;

public:
    // Constructor
    Product(int productId, std::string productName, double productPrice,
            int productStock, std::string productCategory) {
        id = productId;
        name = productName;

        // Validate price
        if (productPrice < 0) {
            std::cout << "Price cannot be negative. Setting price to 0." << std::endl;
            price = 0.0;
        } else {
            price = productPrice;
        }

        // Validate stock
        if (productStock < 0) {
            std::cout << "Stock cannot be negative. Setting stock to 0." << std::endl;
            stock = 0;
        } else {
            stock = productStock;
        }

        category = productCategory;
        discountPercentage = 0.0; // No discount by default

        std::cout << "Product created: " << name << " (ID: " << id << ")" << std::endl;
    }

    // Destructor
    ~Product() {
        std::cout << "Product deleted: " << name << " (ID: " << id << ")" << std::endl;
    }

    // Getter methods
    int getId() const {
        return id;
    }

    std::string getName() const {
        return name;
    }

    double getPrice() const {
        return price;
    }

    double getDiscountedPrice() const {
        return price * (1 - discountPercentage / 100.0);
    }

    int getStock() const {
        return stock;
    }

    std::string getCategory() const {
        return category;
    }

    double getDiscountPercentage() const {
        return discountPercentage;
    }

    // Update price method
    void updatePrice(double newPrice) {
        if (newPrice < 0) {
            std::cout << "Price cannot be negative." << std::endl;
            return;
        }

        std::cout << "Price updated for " << name << ": $" << price << " -> $" << newPrice << std::endl;
        price = newPrice;
    }

    // Update stock method
    void updateStock(int quantity) {
        int newStock = stock + quantity;

        if (newStock < 0) {
            std::cout << "Cannot reduce stock below 0." << std::endl;
            return;
        }

        stock = newStock;

        if (quantity > 0) {
            std::cout << "Added " << quantity << " units to stock. New stock: " << stock << std::endl;
        } else if (quantity < 0) {
            std::cout << "Removed " << -quantity << " units from stock. New stock: " << stock << std::endl;
        }
    }

    // Set discount method
    void setDiscount(double percentage) {
        if (percentage < 0 || percentage > 100) {
            std::cout << "Discount percentage must be between 0 and 100." << std::endl;
            return;
        }

        discountPercentage = percentage;
        std::cout << "Discount set to " << percentage << "% for " << name << std::endl;
        std::cout << "Original price: $" << price << " - Discounted price: $" << getDiscountedPrice() << std::endl;
    }

    // Calculate total price after discount for a given quantity
    double calculateTotalPrice(int quantity) const {
        if (quantity <= 0) {
            std::cout << "Quantity must be positive." << std::endl;
            return 0.0;
        }

        if (quantity > stock) {
            std::cout << "Not enough stock available. Only " << stock << " units in stock." << std::endl;
            return 0.0;
        }

        return getDiscountedPrice() * quantity;
    }

    // Display product information
    void displayInfo() const {
        std::cout << "\n----- Product Information -----" << std::endl;
        std::cout << "ID: " << id << std::endl;
        std::cout << "Name: " << name << std::endl;
        std::cout << "Category: " << category << std::endl;
        std::cout << "Price: $" << std::fixed << std::setprecision(2) << price << std::endl;

        if (discountPercentage > 0) {
            std::cout << "Discount: " << discountPercentage << "%" << std::endl;
            std::cout << "Discounted Price: $" << std::fixed << std::setprecision(2) << getDiscountedPrice() << std::endl;
        }

        std::cout << "Stock: " << stock << " units" << std::endl;
        std::cout << "-------------------------------\n" << std::endl;
    }
};

// Catalog class to manage multiple products
class Catalog {
private:
    std::vector<Product*> products;

public:
    // Constructor
    Catalog() {
        std::cout << "Product Catalog created." << std::endl;
    }

    // Destructor
    ~Catalog() {
        // Clean up all products
        for (Product* p : products) {
            delete p;
        }
        products.clear();
        std::cout << "Product Catalog deleted." << std::endl;
    }

    // Add a product to the catalog
    void addProduct(Product* product) {
        products.push_back(product);
        std::cout << "Product added to catalog: " << product->getName() << std::endl;
    }

    // Find a product by ID
    Product* findProductById(int id) {
        for (Product* p : products) {
            if (p->getId() == id) {
                return p;
            }
        }
        return nullptr;
    }

    // Display all products in the catalog
    void displayAllProducts() const {
        std::cout << "\n===== PRODUCT CATALOG =====" << std::endl;
        if (products.empty()) {
            std::cout << "Catalog is empty." << std::endl;
        } else {
            for (const Product* p : products) {
                p->displayInfo();
            }
        }
        std::cout << "==========================\n" << std::endl;
    }

    // Apply category discount (to all products in a specific category)
    void applyCategoryDiscount(const std::string& category, double discountPercentage) {
        bool found = false;
        for (Product* p : products) {
            if (p->getCategory() == category) {
                p->setDiscount(discountPercentage);
                found = true;
            }
        }

        if (!found) {
            std::cout << "No products found in category: " << category << std::endl;
        }
    }
};

int main() {
    // Create a catalog
    Catalog catalog;

    // Create products and add them to the catalog
    Product* laptop = new Product(1001, "Gaming Laptop", 1299.99, 10, "Electronics");
    Product* phone = new Product(1002, "Smartphone", 699.99, 25, "Electronics");
    Product* tshirt = new Product(1003, "T-Shirt", 19.99, 100, "Clothing");
    Product* jeans = new Product(1004, "Jeans", 49.99, 50, "Clothing");

    catalog.addProduct(laptop);
    catalog.addProduct(phone);
    catalog.addProduct(tshirt);
    catalog.addProduct(jeans);

    // Display all products
    catalog.displayAllProducts();

    // Test update price
    laptop->updatePrice(1199.99);

    // Test update stock
    phone->updateStock(-5);  // Remove 5 from stock
    tshirt->updateStock(20); // Add 20 to stock

    // Test discount calculation
    laptop->setDiscount(15.0);  // 15% discount

    // Apply category discount
    catalog.applyCategoryDiscount("Clothing", 30.0);

    // Calculate total price for an order
    int quantity = 2;
    double totalPrice = laptop->calculateTotalPrice(quantity);
    std::cout << "Total price for " << quantity << " units of " << laptop->getName()
              << ": $" << std::fixed << std::setprecision(2) << totalPrice << std::endl;

    // Test invalid operations
    laptop->updateStock(-100); // Should fail (not enough stock)
    phone->setDiscount(120.0); // Should fail (invalid discount percentage)

    // Display the updated catalog
    catalog.displayAllProducts();

    // The catalog destructor will automatically delete all products
    return 0;
}
