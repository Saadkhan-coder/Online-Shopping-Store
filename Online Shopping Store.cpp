#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Function to print decorative lines
void printLine(char ch = '=', int length = 50) {
    for (int i = 0; i < length; i++) {
        cout << ch;
    }
    cout << endl;
}

// Product Class
class Product {
public:
    int id;
    string name;
    double price;
    int stock;
    string desc;

    Product(int pId, string pName, double pPrice, int pStock, string pDesc) {
        id = pId;
        name = pName;
        price = pPrice;
        stock = pStock;
        desc = pDesc;
    }

    void displayProduct() {
        printLine('-');
        cout << "\033[1;34mProduct ID: " << id << "\033[0m" << endl;
        cout << "\033[1;32mProduct Name: " << name << "\033[0m" << endl;
        cout << "\033[1;33mPrice: ₹" << price << "\033[0m" << endl;
        cout << "\033[1;31mStock: " << stock << "\033[0m" << endl;
        cout << "\033[1;36mDescription: " << desc << "\033[0m" << endl;
        printLine('-');
    }
};

// ShoppingCart Class
class ShoppingCart {
public:
    vector<pair<Product, int>> cartItems;

    void addItem(Product product, int quantity) {
        cartItems.push_back(make_pair(product, quantity));
        cout << "\033[1;32mAdded " << quantity << " of " << product.name << " to the cart.\033[0m" << endl;
    }

    void viewCart() {
        cout << "\n\033[1;34mYour Cart:\033[0m\n";
        double total = 0;
        if (cartItems.empty()) {
            cout << "\033[1;31mYour cart is empty.\033[0m" << endl;
            return;
        }
        for (auto &item : cartItems) {
            cout << "\033[1;35mProduct: " << item.first.name << "\033[0m" << endl;
            cout << "Quantity: " << item.second << endl;
            cout << "Price per item: ₹" << item.first.price << endl;
            total += item.first.price * item.second;
            printLine('-');
        }
        cout << "\033[1;33mTotal: ₹" << total << "\033[0m" << endl;
        printLine('=');
    }
};

// Function to handle checkout and collect user address details
void checkout(ShoppingCart &cart) {
    if (cart.cartItems.empty()) {
        cout << "\033[1;31mYour cart is empty. Add items before checking out.\033[0m" << endl;
        return;
    }

    // Collect user details
    string name, address, city, state, zip;
    cout << "\n\033[1;34mEnter your details for checkout:\033[0m\n";
    cout << "Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Address: ";
    getline(cin, address);
    cout << "City: ";
    getline(cin, city);
    cout << "State: ";
    getline(cin, state);
    cout << "Zip Code: ";
    getline(cin, zip);

    // Display checkout information
    printLine('=');
    cout << "\033[1;32mChecking out...\033[0m\n";
    cart.viewCart();
    cout << "\033[1;34mYour Details:\033[0m\n";
    cout << "Name: " << name << endl;
    cout << "Address: " << address << endl;
    cout << "City: " << city << endl;
    cout << "State: " << state << endl;
    cout << "Zip code: " << zip << endl;
    cout << "\033[1;32mThank you for your purchase!\033[0m" << endl;
    printLine('=');
}

// Main function
int main() {
    // Sample products
    Product p1(101, "Samsung Galaxy S23 Ultra", 124999.00, 10, "Comes with a 6.8-inch AMOLED display, Snapdragon 8 Gen 2 processor, 200 MP main camera, and S-Pen support.");
    Product p2(102, "HP Spectre x360 (14-inch)", 129999.00, 20, "2-in-1 laptop with a touchscreen, Intel Core i7, 16GB RAM, 512GB SSD, and a 360-degree hinge for flexibility.");
    Product p3(103, "Sony WH-1000XM5", 29999.00, 50, "Noise-canceling over-ear headphones with superior sound quality, up to 30 hours of battery life, and touch controls.");
    Product p4(104, "Apple iPad Pro (12.9-inch)", 114900.00, 15, "Offers a Liquid Retina XDR display, M2 chip, and compatibility with the Apple Pencil and Magic Keyboard.");
    Product p5(105, "LG OLED C3 Series (55-inch)", 152990.00, 5, "4K OLED TV with stunning picture quality, Dolby Vision, webOS interface, and support for gaming features like HDMI 2.1.");
    Product p6(106, "Canon EOS R6 Mark II", 224995.00, 4, "Full-frame mirrorless camera with a 24.2 MP sensor, 4K video recording, and advanced autofocus.");

    vector<Product> products = {p1, p2, p3, p4, p5, p6};

    ShoppingCart cart;
    int choice;

    while (true) {
        printLine('=');
        cout << "\033[1;36m1. View Products\n2. Add to Cart\n3. View Cart\n4. Checkout\n5. Exit\033[0m\n";
        printLine('=');
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            for (auto &product : products) {
                product.displayProduct();
            }
        } else if (choice == 2) {
            int productId, quantity;
            cout << "Enter Product ID to add to cart: ";
            cin >> productId;
            cout << "Enter quantity: ";
            cin >> quantity;

            // Find the product by ID
            bool found = false;
            for (auto &product : products) {
                if (product.id == productId && product.stock >= quantity) {
                    cart.addItem(product, quantity);
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "\033[1;31mProduct not found or insufficient stock.\033[0m" << endl;
            }
        } else if (choice == 3) {
            cart.viewCart();
        } else if (choice == 4) {
            checkout(cart);
            break;
        } else if (choice == 5) {
            cout << "\033[1;32mExiting the program. Goodbye!\033[0m" << endl;
            break;
        } else {
            cout << "\033[1;31mInvalid choice. Please try again.\033[0m" << endl;
        }
    }
    return 0;
}
