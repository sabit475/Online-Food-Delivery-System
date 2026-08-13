# 🍔 Online Food Delivery System

## CSE Data Structure Lab Project

The **Online Food Delivery System** is a console-based application developed using the **C programming language** as a Data Structure Lab Project at **Daffodil International University**.

The main purpose of this project is to demonstrate the practical implementation of fundamental data structures in a real-world food delivery management system. The system manages food items, customer accounts, customer orders, payment history, and basic administrative operations.

The project uses **Singly Linked List, Queue, Stack, Dynamic Memory Allocation, and File Handling** to organize and manage different types of data efficiently.

---

## 👥 Group Members

| Name                         | Student ID |
| ---------------------------- | ---------- |
| **Mir Md Sabit Ishtiaq**     | 253-15-475 |
| **Nusrat Jahan Anika**       | 253-15-733 |
| **Md. Atik Hasan Anik**      | 253-15-544 |
| **Ibthda Thamid Tazim**      | 253-15-353 |
| **Md. Shakib All Hasan Mim** | 252-15-975 |

---

## 🎯 Project Objectives

The main objectives of this project are:

* To implement fundamental data structures in a practical application.
* To understand the practical use of **Linked List, Queue, and Stack**.
* To manage food menu items dynamically.
* To process customer orders using the **FIFO** principle.
* To maintain payment history using the **LIFO** principle.
* To implement customer registration and login functionality.
* To practice dynamic memory allocation using pointers.
* To implement file handling for persistent customer accounts.
* To improve C programming and problem-solving skills.
* To develop a simple and organized food delivery management system.

---

# 🧩 Data Structures Used

## 1. Singly Linked List — Food Menu

A **Singly Linked List** is used to dynamically store and manage food menu items.

Each `FoodNode` contains:

* Food ID
* Food Name
* Price
* Pointer to the next node

The system supports:

* Add Food
* View Food Menu
* Search Food
* Update Food
* Delete Food

The food items are dynamically allocated using `malloc()` and inserted at the end of the list.

---

## 2. Linear Queue (FIFO) — Customer Orders

A **Linear Queue** is used to manage customer orders.

The queue follows the:

**FIFO — First In, First Out**

principle. Therefore, the oldest pending order is processed first.

Each `OrderNode` stores:

* Order ID
* Customer Name
* Food ID
* Food Name
* Quantity
* Total Price
* Next Pointer

The system supports:

* Place Order
* View Pending Orders
* Process Next Order
* FIFO-based Order Processing

---

## 3. Stack (LIFO) — Payment History

A **Stack** is used to maintain payment and transaction records.

The stack follows the:

**LIFO — Last In, First Out**

principle.

Each `PaymentNode` contains:

* Order ID
* Customer Name
* Payment Amount
* Next Pointer

When an order is successfully processed, its payment information is added to the top of the payment stack.

The system can display payment history from the most recent transaction to the oldest transaction.

---

## 4. Linked List — Customer Accounts

A linked list is used to maintain registered customer accounts in memory.

Each `CustomerNode` contains:

* Username
* Password
* Next Pointer

The customer system provides:

* Customer Registration
* Customer Login
* Customer Account Searching
* Persistent Customer Account Storage

---

# 💾 File Handling

The system uses a file named:

```text
customers.txt
```

Customer account information is saved in this file so that registered accounts can remain available after the program is closed.

When the program starts, previously saved customer accounts are loaded from the file into the in-memory linked list.

This provides a simple form of persistent data storage.

---

# 👨‍💼 Admin Panel

The system provides a separate **Admin Panel** for managing the food delivery operations.

### Admin Login

The program uses predefined administrator credentials for authentication.

```text
Username: admin
Password: admin123
```

### Admin Features

The administrator can:

1. Add Food
2. View Menu
3. Search Food
4. Update Food
5. Delete Food
6. View Orders
7. Process Next Order
8. View Payment History
9. View Dashboard
10. Logout

---

# 👤 Customer Panel

Customers can access the Customer Panel to interact with the food delivery system.

### Before Login

Customers can:

* Register
* Login
* View Food Menu
* Search Food

### After Login

Authenticated customers can:

* View Food Menu
* Search Food
* Place Orders
* View Pending Orders
* Logout

The system checks the username and password before allowing access to the authenticated customer menu.

---

# 📊 Admin Dashboard

The system includes an Admin Dashboard that provides a quick overview of the current system status.

The dashboard displays:

* **Food Items in Menu**
* **Orders Pending**
* **Orders Processed**
* **Total Revenue**

This gives the administrator a simple summary of the current food delivery operations.

---

# 🍽️ Initial Food Menu

The program automatically adds some initial food items when it starts.

| Food ID | Food Item      |  Price |
| ------: | -------------- | -----: |
|       1 | Chicken Burger | 250.00 |
|       2 | Beef Kacchi    | 350.00 |
|       3 | Veg Fried Rice | 180.00 |
|       4 | Chicken Pizza  | 550.00 |
|       5 | Cold Coffee    | 120.00 |

---

# ⚙️ Technologies Used

### Programming Language

* **C**

### Concepts Used

* Structures
* Pointers
* Dynamic Memory Allocation
* Singly Linked List
* Queue
* Stack
* File Handling
* Functions
* String Handling
* Searching and Traversal

### Standard Libraries

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
```

---

# 🧠 Main Structures

The project uses four major node structures:

```text
FoodNode
   ↓
Food Menu Linked List


OrderNode
   ↓
Customer Order Queue


PaymentNode
   ↓
Payment History Stack


CustomerNode
   ↓
Customer Account Linked List
```

---

# 🔄 System Workflow

```text
                    ONLINE FOOD DELIVERY SYSTEM
                              |
                +-------------+-------------+
                |                           |
                v                           v
          ADMIN PANEL                CUSTOMER PANEL
                |                           |
                v                           v
        Manage Food Menu            Register / Login
        Manage Orders                     |
        Payment History                   v
        Dashboard                   View Food Menu
                                    Search Food
                                    Place Order
                                         |
                                         v
                                  Order Queue
                                         |
                                         v
                                 Process Order
                                         |
                         +---------------+---------------+
                         |                               |
                         v                               v
                  Payment Stack                  Revenue Update
                         |
                         v
                  Payment History
```

---

# 🔗 Data Structure Workflow

### Food Management

```text
Add Food
   ↓
FoodNode
   ↓
Singly Linked List
   ↓
View / Search / Update / Delete
```

### Order Management

```text
Place Order
     ↓
OrderNode
     ↓
Queue
     ↓
FIFO
     ↓
Process Order
```

### Payment Management

```text
Processed Order
      ↓
PaymentNode
      ↓
Stack
      ↓
LIFO
      ↓
Payment History
```

### Customer Management

```text
Registration
      ↓
CustomerNode
      ↓
Linked List
      ↓
customers.txt
```

---

# 💡 Dynamic Memory Management

The project uses dynamic memory allocation to create nodes during program execution.

The `malloc()` function is used to allocate memory for:

* Food Nodes
* Order Nodes
* Payment Nodes
* Customer Nodes

The program also includes a `freeAll()` function to release allocated memory before the program terminates.

This helps prevent unnecessary memory usage and demonstrates proper memory management in C.

---

# 📈 Performance

The system uses efficient operations for its major data structures.

| Operation            | Complexity |
| -------------------- | ---------: |
| Add Food at Tail     |       O(1) |
| View Food Menu       |       O(n) |
| Search Food          |       O(n) |
| Add Order to Queue   |       O(1) |
| Process Order        |       O(1) |
| Push Payment         |       O(1) |
| View Payment History |       O(n) |
| Search Customer      |       O(n) |

The use of `menuTail`, `queueRear`, `queueFront`, and `stackTop` allows several major insertion and removal operations to be performed efficiently.

---

# 🗂️ Project Structure

```text
Online-Food-Delivery-System/
│
├── food_delivery.c
├── README.md
└── DS Project Report.pdf
```

### Runtime File

```text
customers.txt
```

The `customers.txt` file is created/used by the program for storing customer account information.

---

# 🛠️ Compilation

The project can be compiled using the GCC compiler.

```bash
gcc food_delivery.c -o food_delivery
```

---

# ▶️ Run the Program

### Windows

```bash
food_delivery.exe
```

### Linux / macOS

```bash
./food_delivery
```

---

# 🖥️ Main Menu

The program starts with the following main options:

```text
================ MAIN MENU ================

1. Admin Panel
2. Customer Panel
0. Exit
```

---

# 🔐 Basic Security

The system includes basic authentication for both administrator and customer accounts.

* Admin login requires predefined credentials.
* Customers must register before logging in.
* Customer passwords are checked during login.
* Invalid login attempts are rejected.

> Note: This is an academic console-based project, so advanced security features such as password encryption are not implemented.

---

# 📌 Limitations

The current version has some limitations:

* Console-based interface only.
* No graphical user interface.
* No online payment gateway.
* No real-time delivery tracking.
* No external database integration.
* Basic password storage is used for academic demonstration.

---

# 🚀 Future Improvements

The system can be further improved by adding:

* Graphical User Interface (GUI)
* Web-based or mobile application
* MySQL/PostgreSQL database integration
* Online payment gateway
* Real-time delivery tracking
* Delivery personnel management
* Order cancellation and refund system
* Password encryption
* OTP-based authentication
* Customer order history
* Food category management
* Restaurant management
* Rating and review system

---

# 📚 Learning Outcomes

Through this project, we gained practical experience in:

* Implementing Linked Lists
* Implementing Queue using dynamic nodes
* Implementing Stack using dynamic nodes
* Working with structures and pointers
* Dynamic memory allocation
* File handling in C
* Searching and traversal
* Modular programming
* Basic authentication
* Problem-solving and algorithmic thinking

---

# 🎓 Academic Information

**Project Title:** Online Food Delivery System

**Course:** Data Structure Lab

**Department:** Computer Science and Engineering

**Institution:** Daffodil International University

**Project Type:** Academic Lab Project

---

## 👥 Group

This project was developed collaboratively by the following team members:

* **Mir Md Sabit Ishtiaq** — 253-15-475
* **Nusrat Jahan Anika** — 253-15-733
* **Md. Atik Hasan Anik** — 253-15-544
* **Ibthda Thamid Tazim** — 253-15-353
* **Md. Shakib All Hasan Mim** — 252-15-975

---

## 📄 Project Report

The complete project report is included in this repository:

**DS Project Report.pdf**

---

## 📜 License

This project was developed for **academic and educational purposes** as part of the Data Structure Lab course at Daffodil International University.
