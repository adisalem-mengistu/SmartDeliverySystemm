#include "../smartDelivery.h"

// ===========================
// Event Handler Implementation
// ===========================
    EventHandler::EventHandler(OrderManager* o, PriorityQueue* p, DriverAssignment* d) {
        orders = o;
        pq = p;
        drivers = d;
    }

    // ===========================
    // Handle new order
    // ===========================
    void EventHandler::newOrderEvent() {
        cout << "\n--- Process New Order ---\n";
        
        // Get current order count before adding
        int oldCount = orders->getOrderCount();
        
        // Add the order
        orders->addOrder();
        
        // Check if order was actually added
        if (orders->getOrderCount() > oldCount) {
            // Get the last added order and add to priority queue
            Order* lastOrder = orders->getOrderByIndex(orders->getOrderCount() - 1);
            if (lastOrder != NULL) {
                pq->insert(*lastOrder);
                cout << "\n🎉 Thank you for your order!\n";
                cout << "✅ Order successfully placed and scheduled for delivery.\n";
                cout << "📱 You will be notified when your order is ready.\n";
                cout << "\nReturning to main menu...\n";
            }
        } else {
            cout << "\n❌ Sorry, your order could not be placed. Please try again.\n";
            cout << "Returning to main menu...\n";
        }
    }

    // ===========================
    // Handle order cancellation
    // ===========================
    void EventHandler::cancelOrderEvent() {
        int id;
        cout << "Enter Order ID to cancel: ";
        cin >> id;

        // Soft delete is not needed, just remove from priority queue logic
        cout << "Order ID " << id << " canceled.\n";
        // In full system, we would also remove from PQ and free driver
    }

    // ===========================
    // Handle driver free event
    // ===========================
    void EventHandler::driverFreeEvent() {
        int id;
        cout << "Enter Driver ID who is now available: ";
        cin >> id;
        drivers->releaseDriver(id);
    }

    // ===========================
    // Event Menu
    // ===========================
    void EventHandler::eventMenu() {
        int choice;

        do {
            cout << "\n--- System Events ---\n";
            cout << "1. Process New Order\n";
            cout << "2. Cancel Order\n";
            cout << "3. Driver Available\n";
            cout << "0. Back\n";
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice) {
            case 1:
                newOrderEvent();
                break;
            case 2:
                cancelOrderEvent();
                break;
            case 3:
                driverFreeEvent();
                break;
            case 0:
                break;
            default:
                cout << "Invalid choice.\n";
            }
        } while (choice != 0);
    }
