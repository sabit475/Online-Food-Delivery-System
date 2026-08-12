# Online Food Delivery System

## CSE Data Structure Lab Project

A console-based **Online Food Delivery System** developed using the **C programming language** for the Data Structure Lab project at **Daffodil International University**.

The project demonstrates the practical implementation of different data structures in a real-world food delivery system.

---

## Data Structures Used

### 1. Singly Linked List

Used for managing the dynamic food menu.

Operations include:

* Add Food
* View Menu
* Search Food
* Update Food
* Delete Food

### 2. Linear Queue (FIFO)

Used for managing customer orders.

Orders are processed according to the **First In, First Out (FIFO)** principle.

Operations include:

* Place Order
* View Pending Orders
* Process Next Order

### 3. Stack (LIFO)

Used for maintaining payment and transaction history.

Payment records follow the **Last In, First Out (LIFO)** principle.

### 4. Linked List

Used for managing customer accounts.

Operations include:

* Customer Registration
* Customer Login
* Customer Search

### 5. File Handling

Customer account information is stored in:

`customers.txt`

The system loads previously saved customer accounts when the program starts.

---

## Features

### Admin Panel

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

### Customer Panel

Customers can:

1. Register
2. Login
3. View Food Menu
4. Search Food
5. Place Order
6. View Pending Orders
7. Logout

### Dashboard

The admin dashboard displays:

* Total Food Items
* Pending Orders
* Processed Orders
* Total Revenue

---

## Initial Food Menu

The system starts with the following food items:

| Food           |  Price |
| -------------- | -----: |
| Chicken Burger | 250.00 |
| Beef Kacchi    | 350.00 |
| Veg Fried Rice | 180.00 |
| Chicken Pizza  | 550.00 |
| Cold Coffee    | 120.00 |

---

## Technologies Used

* C Programming Language
* Structures
* Pointers
* Singly Linked List
* Queue
* Stack
* Dynamic Memory Allocation
* File Handling
* Standard C Libraries

### Libraries

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
```

---

## Project Structure

```text
Online-Food-Delivery-System/
│
├── food_delivery.c
├── customers.txt
├── README.md
└── Project-Report.pdf
```

---

## Compilation

Using GCC:

```bash
gcc food_delivery.c -o food_delivery
```

## Run

### Windows

```bash
food_delivery.exe
```

### Linux / macOS

```bash
./food_delivery
```

---

## System Flow

```text
                 ONLINE FOOD DELIVERY SYSTEM
                            |
              +-------------+-------------+
              |                           |
              v                           v
        ADMIN PANEL                 CUSTOMER PANEL
              |                           |
              v                           v
       Food Management             Register / Login
       Order Management                  |
       Payment History                   v
       Dashboard                    View Menu
                                     Search Food
                                     Place Order
                                          |
                                          v
                                   Order Queue
                                          |
                                          v
                                  Process Order
                                          |
                                          v
                                  Payment Stack
```

---

## Data Structure Workflow

```text
Food Menu
    |
    v
Singly Linked List
    |
    v
Search / Update / Delete


Customer Order
    |
    v
Queue
    |
    v
FIFO Processing
    |
    v
Payment
    |
    v
Stack
    |
    v
Payment History
```

---

## Memory Management

The project uses dynamic memory allocation with `malloc()` for creating food, order, payment, and customer nodes.

The program also releases dynamically allocated memory before termination using `free()`.

---

## File Storage

Customer account information is stored in:

```text
customers.txt
```

The file is used to save registered customer accounts and reload them when the program starts.

---

## Project Objectives

* To implement fundamental data structures in a practical application.
* To understand the use of Linked List, Queue, and Stack.
* To practice dynamic memory allocation.
* To implement file handling in C.
* To improve programming and problem-solving skills.
* To develop a functional console-based food delivery system.

---

## Author

**CSE Data Structure Lab Project**

**Department of Computer Science and Engineering**
**Daffodil International University**

---

## License

This project was developed for academic and educational purposes.
