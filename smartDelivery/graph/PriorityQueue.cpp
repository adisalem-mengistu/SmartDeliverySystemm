#include "../smartDelivery.h"
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

// ===========================
// Priority Queue Implementation
// ===========================

PriorityQueue::PriorityQueue() {
    size = 0;
    newOrderCount = 0;  // Initialize notification counter
    loadFromFile(); // Load existing data on startup
}

// Heapify upward
void PriorityQueue::heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[parent].priority < heap[index].priority) {
                Order temp = heap[parent];
                heap[parent] = heap[index];
                heap[index] = temp;
                index = parent;
            } else {
                break;
            }
        }
    }

    // Heapify downward
    void PriorityQueue::heapifyDown(int index) {
        int largest, left, right;

        while (true) {
            largest = index;
            left = 2 * index + 1;
            right = 2 * index + 2;

            if (left < size && heap[left].priority > heap[largest].priority)
                largest = left;

            if (right < size && heap[right].priority > heap[largest].priority)
                largest = right;

            if (largest != index) {
                Order temp = heap[index];
                heap[index] = heap[largest];
                heap[largest] = temp;
                index = largest;
            } else {
                break;
            }
        }
    }

// ===========================
// Insert Order into Heap
// ===========================
    void PriorityQueue::insert(Order o) {
        if (size >= MAX_HEAP) {
            cout << "Delivery schedule is full!\n";
            return;
        }

        heap[size] = o;
        heapifyUp(size);
        size++;
        newOrderCount++;  // Increment notification counter

        saveToFile(); // Save after adding
    }

    // ===========================
    // Extract Highest Priority
    // ===========================
    Order PriorityQueue::extractHighestPriority() {
        if (size == 0) {
            cout << "No deliveries to process!\n";
            return heap[0];
        }

        Order top = heap[0];
        heap[0] = heap[size - 1];
        size--;
        heapifyDown(0);
        saveToFile(); // Save after extracting

        return top;
    }

    // ===========================
    // View Next Order
    // ===========================
    void PriorityQueue::viewTop() {
        if (size == 0) {
            cout << "No urgent deliveries at the moment.\n";
            pressAnyKeyToContinue();
            return;
        }

        cout << "\nNext Urgent Delivery:\n";
        cout << "Order ID: " << heap[0].orderId << endl;
        cout << "Customer: " << heap[0].customerName << endl;
        cout << "Category: " << heap[0].category << endl;
        cout << "Items: " << heap[0].quantity << "x " << heap[0].itemDescription << endl;
        cout << "Urgency: ";
        if (heap[0].priority == 1) cout << "High Priority";
        else if (heap[0].priority == 2) cout << "Standard";
        else cout << "Low Priority";
        cout << endl;
        
        pressAnyKeyToContinue();
    }

    // ===========================
    // Display All Orders in Heap
    // ===========================
    void PriorityQueue::displayAll() {
        if (size == 0) {
            cout << "No deliveries scheduled yet.\n";
            return;
        }

        cout << "\n--- Scheduled Deliveries ---\n";
        for (int i = 0; i < size; i++) {
            cout << "Order ID: " << heap[i].orderId 
                 << " | Category: " << heap[i].category
                 << " | Items: " << heap[i].quantity << "x " << heap[i].itemDescription
                 << " | Urgency: ";
            if (heap[i].priority == 1) cout << "High Priority";
            else if (heap[i].priority == 2) cout << "Standard";
            else cout << "Low Priority";
            cout << endl;
        }
    }

    // ===========================
    // Priority Queue Menu
    // ===========================
    void PriorityQueue::priorityMenu() {
        int choice;

        do {
            cout << "\n--- Delivery Scheduling ---\n";
            cout << "1. View Next Urgent Delivery\n";
            cout << "2. Dispatch Highest Priority Order\n";
            cout << "3. View All Scheduled Deliveries\n";
            cout << "0. Back\n";
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice) {
            case 1:
                viewTop();
                break;

            case 2: {
                Order o = extractHighestPriority();
                cout << "Dispatching Order ID: " << o.orderId << endl;
                break;
            }

            case 3:
                displayAll();
                break;

            case 0:
                break;

            default:
                cout << "Invalid choice.\n";
            }
        } while (choice != 0);
    }
bool PriorityQueue::isEmpty() {
    return size == 0;
}
// ===========================
// File Persistence Methods
// ===========================
void PriorityQueue::saveToFile() {
    ofstream file("data/priority_queue.dat", ios::binary);
    if (!file) {
        cout << "Error: Could not save delivery schedule to file.\n";
        return;
    }
    
    file.write((char*)&size, sizeof(size));
    file.write((char*)heap, sizeof(Order) * size);
    file.close();
}

void PriorityQueue::loadFromFile() {
    ifstream file("data/priority_queue.dat", ios::binary);
    if (!file) {
        // File doesn't exist yet, start with empty data
        size = 0;
        return;
    }
    
    file.read((char*)&size, sizeof(size));
    file.read((char*)heap, sizeof(Order) * size);
    file.close();
}
// ===========================
// Customer-Specific Method
// ===========================
void PriorityQueue::viewMyDeliveryStatus() {
    char customerName[50];
    cout << "Enter your name: ";
    cin >> customerName;
    
    bool found = false;
    int position = 1;
    
    cout << "\n=== Your Delivery Status ===\n";
    
    for (int i = 0; i < size; i++) {
        if (strcmp(heap[i].customerName, customerName) == 0) {
            found = true;
            cout << "Order #" << heap[i].orderId << endl;
            cout << "Category: " << heap[i].category << endl;
            cout << "Items: " << heap[i].quantity << "x " << heap[i].itemDescription << endl;
            cout << "Status: Scheduled for delivery" << endl;
            cout << "Position in queue: #" << position << endl;
            
            if (heap[i].priority == 1) {
                cout << "Priority: High Priority (Express) - Will be delivered soon!" << endl;
            } else if (heap[i].priority == 2) {
                cout << "Priority: Standard Delivery - Normal processing time" << endl;
            } else {
                cout << "Priority: Economy Delivery - Lower cost, longer delivery time" << endl;
            }
            cout << "----------------------\n";
        }
        position++;
    }
    
    if (!found) {
        cout << "No deliveries scheduled for " << customerName << endl;
        cout << "Your orders may have been delivered or are being processed.\n";
    }
    
    pressAnyKeyToContinue();
}
// ===========================
// Helper Method for All Roles
// ===========================
void PriorityQueue::pressAnyKeyToContinue() {
    cout << "\nPress Enter to return to main menu...";
    cin.ignore();
    cin.get();
}
// ===========================
// Manager Notification System
// ===========================
void PriorityQueue::checkNewOrderNotifications() {
    if (newOrderCount > 0) {
        cout << "\n🔔 NOTIFICATION: " << newOrderCount << " new order(s) received!\n";
        cout << "📋 Please review and assign to drivers.\n";
        newOrderCount = 0;  // Reset counter after showing notification
        pressAnyKeyToContinue();
    } else {
        cout << "\n✅ No new order notifications.\n";
        pressAnyKeyToContinue();
    }
}