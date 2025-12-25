# Smart Delivery System 📦

A comprehensive delivery management system built in C++ that handles orders, drivers, routes, and scheduling with persistent file-based storage.

## 🚀 Quick Start

1. **Compile the program:**
   ```bash
   g++ -o smartDelivery.exe smartDelivery/main.cpp
   ```

2. **Run the program:**
   ```bash
   ./smartDelivery.exe
   ```

3. **Choose your role:**
   - **Customer** - Track orders and delivery status
   - **Operations Manager** - Full system management
   - **Delivery Driver** - View deliveries and update status

## 👥 User Roles & Features

### 🛒 Customer Features
- **Track My Orders** - View all your orders with details
- **Check Delivery Status** - See which orders are scheduled for delivery

### 👔 Operations Manager Features
- **Manage Orders** - Add, view, update, and delete customer orders
- **Schedule Deliveries** - Prioritize orders for delivery dispatch
- **Manage Routes** - Set up delivery locations and distances
- **Optimize Delivery Routes** - Find shortest paths using Dijkstra algorithm
- **Manage Drivers** - Add drivers and track their availability
- **Handle Events** - Process system events and updates

### 🚚 Delivery Driver Features
- **View My Deliveries** - See assigned delivery orders
- **Mark Delivery Complete** - Update status when delivery is finished

## 🏗️ System Architecture

### Core Components

1. **Order Management** (`orders/Order.cpp`)
   - Handles customer orders with priorities
   - Supports CRUD operations
   - Persistent storage in `data/orders.dat`

2. **Priority Queue** (`priority/PriorityQueue.cpp`)
   - Max heap implementation for delivery scheduling
   - Prioritizes urgent orders first
   - Business-friendly interface

3. **Route Management** (`graph/graph.cpp`)
   - Adjacency matrix for location network
   - Distance-based route storage
   - Persistent storage in `data/graph.dat`

4. **Route Optimization** (`graph/Dijkstra.cpp`)
   - Shortest path algorithm implementation
   - Optimizes delivery routes
   - Supports multiple locations

5. **Driver Assignment** (`drivers/DriverAssignment.cpp`)
   - Driver availability tracking
   - Load balancing (assigns least busy driver)
   - Persistent storage in `data/drivers.dat`

6. **Event Handler** (`scheduler/EventHandler.cpp`)
   - Coordinates between system modules
   - Handles real-time events

## 💾 Data Storage

The system uses **file-based persistence** with binary files:

```
data/
├── orders.dat    - Customer orders
├── drivers.dat   - Driver information
└── graph.dat     - Route network
```

**Benefits:**
- ✅ Data persists between program runs
- ✅ Fast binary file operations
- ✅ Automatic save on all changes
- ✅ Automatic load on startup

## 🔧 Technical Details

### Data Structures Used
- **Arrays** - Primary storage for orders, drivers, locations
- **Max Heap** - Priority queue for delivery scheduling
- **Adjacency Matrix** - Graph representation for routes
- **Binary Files** - Persistent data storage

### Algorithms Implemented
- **Heap Operations** - Insert, extract, heapify for priority management
- **Dijkstra's Algorithm** - Shortest path for route optimization
- **Greedy Assignment** - Driver allocation based on current load

### File Structure
```
smartDelivery/
├── main.cpp                 - Main program entry point
├── smartDelivery.h          - Header with all class declarations
├── orders/Order.cpp         - Order management implementation
├── priority/PriorityQueue.cpp - Priority scheduling implementation
├── graph/graph.cpp          - Route network implementation
├── graph/Dijkstra.cpp       - Route optimization implementation
├── drivers/DriverAssignment.cpp - Driver management implementation
└── scheduler/EventHandler.cpp - Event coordination implementation
```

## 🎯 Business Logic

### Order Priority System
- **Priority 1** - High (urgent deliveries)
- **Priority 2** - Medium (standard deliveries)  
- **Priority 3** - Low (flexible deliveries)

### Driver Assignment Logic
- Assigns orders to the **least busy available driver**
- Tracks driver load (number of current deliveries)
- Supports driver availability status

### Route Optimization
- Uses **Dijkstra's algorithm** for shortest path calculation
- Supports weighted edges (distances between locations)
- Handles multiple delivery locations

## 📋 Sample Usage Workflow

### For Operations Manager:
1. **Set up locations** (Manage Routes → Set Number of Locations)
2. **Add routes** (Manage Routes → Add Route with distances)
3. **Add drivers** (Manage Drivers → Add Driver)
4. **Add orders** (Manage Orders → Add Order)
5. **Schedule deliveries** (Schedule Deliveries → View/Process orders)
6. **Optimize routes** (Optimize Delivery Routes → Run Dijkstra)

### For Customers:
1. **Track orders** (Track My Orders)
2. **Check delivery status** (Check Delivery Status)

### For Drivers:
1. **View assigned deliveries** (View My Deliveries)
2. **Mark deliveries complete** (Mark Delivery Complete)

## 🔍 Testing the System

### Test Data Setup:
```bash
# Run as Operations Manager (choice 2)
# Add sample orders:
Order ID: 101, Customer: Alice_Smith, Address: 456_Oak_Ave, Priority: 1
Order ID: 102, Customer: Bob_Johnson, Address: 789_Pine_St, Priority: 2

# Add sample driver:
Driver ID: 1, Name: Driver_Mike

# Set up routes:
Locations: 5
Route: 0 to 1, Distance: 10
```

### Verify Persistence:
1. Add data as manager
2. Exit program
3. Restart and login as customer
4. Verify orders are still visible

## 🚨 Error Handling

The system includes business-friendly error messages:
- "No orders found" (instead of technical jargon)
- "No deliveries scheduled yet"
- "No urgent deliveries at the moment"
- Input validation for all user entries

## 🔧 Compilation Requirements

- **C++ Compiler** (g++, Visual Studio, etc.)
- **C++11 or later** (for file I/O operations)
- **Windows/Linux/Mac** compatible

## 📞 Support

If you encounter issues:
1. Ensure the `data/` folder exists in the same directory as the executable
2. Check file permissions for the `data/` folder
3. Verify all source files are in the correct directory structure
4. Make sure to compile with all dependencies included

---

**Built with:** C++, File-based persistence, Object-oriented design
**Features:** Role-based access, Priority scheduling, Route optimization, Data persistence