#include "../smartDelivery.h"

// =====================
// Order Manager Implementation
// =====================
OrderManager::OrderManager() {
    count = 0;
    loadFromFile(); // Load existing data on startup
}
    // =====================
// Add New Order
// =====================
void OrderManager::addOrder() {
    if (count >= MAX_ORDERS) {
        cout << "Order system is full!\n";
        return;
    }

    // Auto-generate order ID
    orders[count].orderId = 1000 + count + 1;

    cout << "Enter Your Name: ";
    cin >> orders[count].customerName;

    cout << "Enter Delivery Address: ";
    cin >> orders[count].address;

    // Category selection
    int categoryChoice;
    cout << "\nSelect Item Category:\n";
    cout << "1. Food & Beverages\n";
    cout << "2. Personal Care (Soap, Shampoo, etc.)\n";
    cout << "3. Electronics\n";
    cout << "4. Clothing & Accessories\n";
    cout << "5. Books & Stationery\n";
    cout << "6. Home & Garden\n";
    cout << "7. Other\n";
    cout << "Enter choice: ";
    cin >> categoryChoice;

    // Set category name and show sample items
    switch(categoryChoice) {
        case 1: {
            strcpy(orders[count].category, "Food_&_Beverages");
            cout << "\nSample Food & Beverages:\n";
            cout << "Foods: Shiro, Firfir, Doro_Wat, Injera, Kitfo, Tibs\n";
            cout << "Beverages: Water, Mirinda, Coca_Cola, Coffee, Tea, Juice\n";
            cout << "Snacks: Bread, Biscuits, Nuts, Fruits\n";
            break;
        }
        case 2: {
            strcpy(orders[count].category, "Personal_Care");
            cout << "\nSample Personal Care Items:\n";
            cout << "Bath: Hand_Soap, Body_Wash, Shampoo, Conditioner\n";
            cout << "Oral: Toothpaste, Toothbrush, Mouthwash\n";
            cout << "Skin: Lotion, Cream, Sunscreen, Deodorant\n";
            break;
        }
        case 3: {
            strcpy(orders[count].category, "Electronics");
            cout << "\nSample Electronics:\n";
            cout << "Mobile: Smartphone, Phone_Charger, Power_Bank\n";
            cout << "Audio: Headphones, Speakers, Earbuds\n";
            cout << "Computing: Laptop, Mouse, Keyboard, USB_Cable\n";
            break;
        }
        case 4: {
            strcpy(orders[count].category, "Clothing");
            cout << "\nSample Clothing & Accessories:\n";
            cout << "Clothing: T_Shirt, Jeans, Dress, Jacket, Shoes\n";
            cout << "Accessories: Watch, Belt, Hat, Bag, Sunglasses\n";
            break;
        }
        case 5: {
            strcpy(orders[count].category, "Books_&_Stationery");
            cout << "\nSample Books & Stationery:\n";
            cout << "Books: Novel, Textbook, Magazine, Newspaper\n";
            cout << "Stationery: Pen, Pencil, Notebook, Paper, Eraser\n";
            break;
        }
        case 6: {
            strcpy(orders[count].category, "Home_&_Garden");
            cout << "\nSample Home & Garden Items:\n";
            cout << "Home: Pillow, Blanket, Candle, Cleaning_Supplies\n";
            cout << "Garden: Plant, Seeds, Fertilizer, Garden_Tools\n";
            break;
        }
        default: {
            strcpy(orders[count].category, "Other");
            cout << "\nOther Items: Anything not listed above\n";
            break;
        }
    }

    cout << "\nWhat specific item would you like? ";
    cin >> orders[count].itemDescription;

    cout << "How many items? ";
    cin >> orders[count].quantity;

    cout << "\nSelect Delivery Urgency:\n";
    cout << "1. High Priority (Express)\n";
    cout << "2. Standard Delivery\n";
    cout << "3. Low Priority (Economy)\n";
    cout << "Enter choice: ";
    cin >> orders[count].priority;

    if (orders[count].priority < 1 || orders[count].priority > 3) {
        orders[count].priority = 2; // Default to standard
    }

    orders[count].active = true;
    count++;

    cout << "\n🎉 Order #" << orders[count-1].orderId << " placed successfully!\n";
    cout << "Category: " << orders[count-1].category << endl;
    cout << "Items: " << orders[count-1].quantity << "x " << orders[count-1].itemDescription << endl;
    cout << "Thank you for your order!\n";
    saveToFile(); // Save after adding
}

    // =====================
    // View Single Order
    // =====================
    void OrderManager::viewOrder() {
        int id;
        cout << "Enter Order ID: ";
        cin >> id;

        int index = findOrderIndex(id);
        if (index == -1 || !orders[index].active) {
            cout << "Order not found.\n";
            return;
        }

        displayOrder(orders[index]);
    }

    // =====================
    // View All Orders
    // =====================
    void OrderManager::viewAllOrders() {
        if (count == 0) {
            cout << "No orders found.\n";
            return;
        }

        for (int i = 0; i < count; i++) {
            if (orders[i].active) {
                displayOrder(orders[i]);
            }
        }
    }

    // =====================
    // Update Order (Manager Only)
    // =====================
    void OrderManager::updateOrder() {
        int id;
        cout << "Enter Order ID to update: ";
        cin >> id;

        int index = findOrderIndex(id);
        if (index == -1 || !orders[index].active) {
            cout << "Order not found.\n";
            return;
        }

        cout << "Enter New Customer Name: ";
        cin >> orders[index].customerName;

        cout << "Enter New Address: ";
        cin >> orders[index].address;

        cout << "Enter New Category: ";
        cin >> orders[index].category;

        cout << "Enter New Item Description: ";
        cin >> orders[index].itemDescription;

        cout << "Enter New Quantity: ";
        cin >> orders[index].quantity;

        cout << "Enter New Urgency Level: ";
        cin >> orders[index].priority;

        cout << "Order updated successfully.\n";
        saveToFile(); // Save after updating
    }

    // =====================
    // Delete Order (Manager Only)
    // =====================
    void OrderManager::deleteOrder() {
        int id;
        cout << "Enter Order ID to delete: ";
        cin >> id;

        int index = findOrderIndex(id);
        if (index == -1 || !orders[index].active) {
            cout << "Order not found.\n";
            return;
        }

        orders[index].active = false;
        cout << "Order deleted successfully.\n";
        saveToFile(); // Save after deleting
    }

    // =====================
    // Get Order Pointer (For Priority Queue)
    // =====================
    Order* OrderManager::getOrder(int id) {
        int index = findOrderIndex(id);
        if (index == -1 || !orders[index].active)
            return NULL;

        return &orders[index];
    }

    // =====================
    // Order Management Menu
    // =====================
    void OrderManager::orderMenu(int role) {
        int choice;

        do {
            cout << "\n--- Order Management ---\n";
            cout << "1. Add Order\n";
            cout << "2. View Order\n";
            cout << "3. View All Orders\n";

            if (role == 2) { // Manager
                cout << "4. Update Order\n";
                cout << "5. Delete Order\n";
            }

            cout << "0. Back\n";
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice) {
            case 1:
                addOrder();
                break;
            case 2:
                viewOrder();
                break;
            case 3:
                viewAllOrders();
                break;
            case 4:
                if (role == 2)
                    updateOrder();
                else
                    cout << "Access Denied!\n";
                break;
            case 5:
                if (role == 2)
                    deleteOrder();
                else
                    cout << "Access Denied!\n";
                break;
            case 0:
                break;
            default:
                cout << "Invalid choice.\n";
            }
        } while (choice != 0);
    }

// =====================
// Helper Functions
// =====================
int OrderManager::findOrderIndex(int id) {
    for (int i = 0; i < count; i++) {
        if (orders[i].orderId == id)
            return i;
    }
    return -1;
}

void OrderManager::displayOrder(Order o) {
    cout << "----------------------\n";
    cout << "Order ID   : " << o.orderId << endl;
    cout << "Customer   : " << o.customerName << endl;
    cout << "Category   : " << o.category << endl;
    cout << "Items      : " << o.quantity << "x " << o.itemDescription << endl;
    cout << "Address    : " << o.address << endl;
    
    // Display business-friendly priority
    cout << "Urgency    : ";
    if (o.priority == 1) cout << "High Priority";
    else if (o.priority == 2) cout << "Standard";
    else cout << "Low Priority";
    cout << endl;
    
    cout << "----------------------\n";
}

// =====================
// File Persistence Methods
// =====================
void OrderManager::saveToFile() {
    ofstream file("data/orders.dat", ios::binary);
    if (!file) {
        cout << "Error: Could not save orders to file.\n";
        return;
    }
    
    file.write((char*)&count, sizeof(count));
    file.write((char*)orders, sizeof(Order) * count);
    file.close();
}

void OrderManager::loadFromFile() {
    ifstream file("data/orders.dat", ios::binary);
    if (!file) {
        // File doesn't exist yet, start with empty data
        count = 0;
        return;
    }
    
    file.read((char*)&count, sizeof(count));
    file.read((char*)orders, sizeof(Order) * count);
    file.close();
}
// =====================
// Get Order by Index (for EventHandler)
// =====================
Order* OrderManager::getOrderByIndex(int index) {
    if (index < 0 || index >= count || !orders[index].active)
        return NULL;
    
    return &orders[index];
}
// =====================
// Customer-Specific Methods
// =====================
void OrderManager::viewMyOrders() {
    char customerName[50];
    cout << "Enter your name: ";
    cin >> customerName;
    
    bool found = false;
    cout << "\n=== Your Orders ===\n";
    
    for (int i = 0; i < count; i++) {
        if (orders[i].active && strcmp(orders[i].customerName, customerName) == 0) {
            displayOrder(orders[i]);
            found = true;
        }
    }
    
    if (!found) {
        cout << "No orders found for " << customerName << endl;
    }
}

void OrderManager::viewMyDeliveryStatus() {
    char customerName[50];
    cout << "Enter your name: ";
    cin >> customerName;
    
    cout << "\n=== Your Delivery Status ===\n";
    cout << "Customer: " << customerName << endl;
    cout << "Checking delivery schedule...\n\n";
}
// =====================
// Helper Method for All Roles
// =====================
void OrderManager::pressAnyKeyToContinue() {
    cout << "\nPress Enter to return to main menu...";
    cin.ignore();
    cin.get();
}