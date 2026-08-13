
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* ------------------------------------------------------------
   1. DATA STRUCTURE DEFINITIONS
   ------------------------------------------------------------ */

/* ---- Singly Linked List node : Food Menu ---- */
typedef struct FoodNode {
    int id;
    char name[50];
    float price;
    struct FoodNode *next;
} FoodNode;

/* ---- Queue node : Customer Orders (FIFO) ---- */
typedef struct OrderNode {
    int orderId;
    char customerName[50];
    int foodId;
    char foodName[50];
    int quantity;
    float totalPrice;
    struct OrderNode *next;
} OrderNode;

/* ---- Stack node : Payment History (LIFO) ---- */
typedef struct PaymentNode {
    int orderId;
    char customerName[50];
    float amount;
    struct PaymentNode *next;
} PaymentNode;

/* ---- Simple in-RAM customer account list ---- */
typedef struct CustomerNode {
    char username[30];
    char password[30];
    struct CustomerNode *next;
} CustomerNode;

/* ------------------------------------------------------------
   2. GLOBAL POINTERS (heads / front / rear / top)
   ------------------------------------------------------------ */
FoodNode    *menuHead   = NULL;   /* Linked List head   */
FoodNode    *menuTail   = NULL;   /* Linked List tail (for O(1) append) */
OrderNode   *queueFront = NULL;   /* Queue front         */
OrderNode   *queueRear  = NULL;   /* Queue rear          */
PaymentNode *stackTop   = NULL;   /* Stack top            */
CustomerNode *custHead  = NULL;   /* Registered customers */

int nextFoodId  = 1;
int nextOrderId = 1;
float totalRevenue = 0.0f;
int totalOrdersProcessed = 0;

const char ADMIN_USER[] = "admin";
const char ADMIN_PASS[] = "admin123";
const char CUSTOMER_FILE[] = "customers.txt";   /* persistent storage for customer accounts */

/* ------------------------------------------------------------
   3. UTILITY
   ------------------------------------------------------------ */
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void pause_screen() {
    printf("\nPress ENTER to continue...");
    clearInputBuffer();
}

/* ------------------------------------------------------------
   4. LINKED LIST OPERATIONS  ->  FOOD MENU
   ------------------------------------------------------------ */

/* addFood(): O(1) insert at tail using malloc(), so IDs stay in ascending
   order (ID 1 always shows first) when the menu is printed.
   verbose=1 -> prints a confirmation (used when admin adds an item)
   verbose=0 -> silent (used for startup seed data) */
void addFood(const char *name, float price, int verbose) {
    FoodNode *node = (FoodNode *)malloc(sizeof(FoodNode));
    if (node == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    node->id = nextFoodId++;
    strcpy(node->name, name);
    node->price = price;
    node->next = NULL;

    if (menuHead == NULL) {         /* empty list */
        menuHead = menuTail = node;
    } else {
        menuTail->next = node;      /* attach after current tail */
        menuTail = node;
    }
    if (verbose)
        printf("Food item '%s' added successfully with ID %d.\n", name, node->id);
}

/* viewMenu(): traverse the singly linked list */
void viewMenu() {
    if (menuHead == NULL) {
        printf("Menu is currently empty.\n");
        return;
    }
    printf("\n---------------------------------------------\n");
    printf("%-6s %-25s %-10s\n", "ID", "Food Name", "Price");
    printf("---------------------------------------------\n");
    FoodNode *cur = menuHead;
    while (cur != NULL) {
        printf("%-6d %-25s %-10.2f\n", cur->id, cur->name, cur->price);
        cur = cur->next;
    }
    printf("---------------------------------------------\n");
}

/* searchFood(): linear traversal, match by ID or name substring */
FoodNode* searchFoodById(int id) {
    FoodNode *cur = menuHead;
    while (cur != NULL) {
        if (cur->id == id) return cur;
        cur = cur->next;
    }
    return NULL;
}

/* containsIgnoreCase(): manual case-insensitive substring search
   (portable — doesn't rely on the non-standard strcasestr) */
int containsIgnoreCase(const char *haystack, const char *needle) {
    if (*needle == '\0') return 1;  /* empty search matches everything */
    for (int i = 0; haystack[i] != '\0'; i++) {
        int j = 0;
        while (haystack[i + j] != '\0' && needle[j] != '\0' &&
               tolower((unsigned char)haystack[i + j]) == tolower((unsigned char)needle[j])) {
            j++;
        }
        if (needle[j] == '\0') return 1;   /* matched the whole needle */
    }
    return 0;
}

void searchFood(const char *keyword) {
    FoodNode *cur = menuHead;
    int found = 0;
    printf("\nSearch results for \"%s\":\n", keyword);
    printf("---------------------------------------------\n");
    while (cur != NULL) {
        if (containsIgnoreCase(cur->name, keyword)) {
            printf("%-6d %-25s %-10.2f\n", cur->id, cur->name, cur->price);
            found = 1;
        }
        cur = cur->next;
    }
    if (!found) printf("No matching food item found.\n");
}

/* updateFood(): find node and update price/name in place */
int updateFood(int id, const char *newName, float newPrice) {
    FoodNode *node = searchFoodById(id);
    if (node == NULL) return 0;
    strcpy(node->name, newName);
    node->price = newPrice;
    return 1;
}

/* deleteFood(): unlink node from the singly linked list and free() it */
int deleteFood(int id) {
    FoodNode *cur = menuHead, *prev = NULL;
    while (cur != NULL && cur->id != id) {
        prev = cur;
        cur = cur->next;
    }
    if (cur == NULL) return 0;            /* not found */
    if (prev == NULL) menuHead = cur->next; /* deleting head */
    else prev->next = cur->next;
    if (cur == menuTail) menuTail = prev;   /* deleting tail: fix tail pointer */
    free(cur);
    return 1;
}

/* ------------------------------------------------------------
   5. QUEUE OPERATIONS (FIFO)  ->  ORDER DISPATCH
   ------------------------------------------------------------ */

/* enqueueOrder(): append at rear in O(1) */
void enqueueOrder(const char *custName, int foodId, int quantity) {
    FoodNode *food = searchFoodById(foodId);
    if (food == NULL) {
        printf("Invalid Food ID. Order not placed.\n");
        return;
    }
    OrderNode *node = (OrderNode *)malloc(sizeof(OrderNode));
    if (node == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    node->orderId = nextOrderId++;
    strcpy(node->customerName, custName);
    node->foodId = foodId;
    strcpy(node->foodName, food->name);
    node->quantity = quantity;
    node->totalPrice = food->price * quantity;
    node->next = NULL;

    if (queueRear == NULL) {           /* empty queue */
        queueFront = queueRear = node;
    } else {
        queueRear->next = node;
        queueRear = node;
    }
    printf("Order placed! Order ID: %d | %s x%d | Total: %.2f\n",
           node->orderId, node->foodName, node->quantity, node->totalPrice);
}

/* viewOrders(): traverse the queue from front to rear */
void viewOrders() {
    if (queueFront == NULL) {
        printf("No pending orders in the queue.\n");
        return;
    }
    printf("\n---------------------------------------------------------\n");
    printf("%-8s %-15s %-20s %-6s %-8s\n", "OrderID", "Customer", "Food", "Qty", "Total");
    printf("---------------------------------------------------------\n");
    OrderNode *cur = queueFront;
    while (cur != NULL) {
        printf("%-8d %-15s %-20s %-6d %-8.2f\n",
               cur->orderId, cur->customerName, cur->foodName, cur->quantity, cur->totalPrice);
        cur = cur->next;
    }
    printf("---------------------------------------------------------\n");
}

/* pushPayment(): forward declaration (defined in section 6) */
void pushPayment(int orderId, const char *custName, float amount);

/* processOrder(): dequeue from front (kitchen serves oldest order first),
   then push its bill onto the payment stack */
int processOrder() {
    if (queueFront == NULL) {
        printf("No orders to process.\n");
        return 0;
    }
    OrderNode *served = queueFront;
    queueFront = queueFront->next;
    if (queueFront == NULL) queueRear = NULL;  /* queue became empty */

    printf("Processed Order #%d for %s -> %s x%d (Total: %.2f)\n",
           served->orderId, served->customerName, served->foodName,
           served->quantity, served->totalPrice);

    pushPayment(served->orderId, served->customerName, served->totalPrice);
    totalRevenue += served->totalPrice;
    totalOrdersProcessed++;

    free(served);
    return 1;
}

/* ------------------------------------------------------------
   6. STACK OPERATIONS (LIFO)  ->  PAYMENT / TRANSACTION LEDGER
   ------------------------------------------------------------ */

/* pushPayment(): O(1) push, attach directly to top */
void pushPayment(int orderId, const char *custName, float amount) {
    PaymentNode *node = (PaymentNode *)malloc(sizeof(PaymentNode));
    if (node == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    node->orderId = orderId;
    strcpy(node->customerName, custName);
    node->amount = amount;
    node->next = stackTop;       /* update top */
    stackTop = node;
}

/* viewPaymentHistory(): traverse top -> bottom (most recent first) */
void viewPaymentHistory() {
    if (stackTop == NULL) {
        printf("No completed transactions yet.\n");
        return;
    }
    printf("\n----- Payment History (Most Recent First) -----\n");
    printf("%-8s %-15s %-10s\n", "OrderID", "Customer", "Amount");
    printf("------------------------------------------------\n");
    PaymentNode *cur = stackTop;
    while (cur != NULL) {
        printf("%-8d %-15s %-10.2f\n", cur->orderId, cur->customerName, cur->amount);
        cur = cur->next;
    }
    printf("------------------------------------------------\n");
}

/* ------------------------------------------------------------
   7. CUSTOMER ACCOUNTS (register / login)
   ------------------------------------------------------------ */

CustomerNode* findCustomer(const char *username) {
    CustomerNode *cur = custHead;
    while (cur != NULL) {
        if (strcmp(cur->username, username) == 0) return cur;
        cur = cur->next;
    }
    return NULL;
}

/* saveCustomerToFile(): append one "username password" line to customers.txt
   so the account survives after the program closes */
void saveCustomerToFile(const char *username, const char *password) {
    FILE *fp = fopen(CUSTOMER_FILE, "a");   /* "a" = append, keeps old records */
    if (fp == NULL) {
        printf("Warning: could not save customer data to file.\n");
        return;
    }
    fprintf(fp, "%s %s\n", username, password);
    fclose(fp);
}

/* loadCustomersFromFile(): read customers.txt (if it exists) into the
   in-RAM linked list at program startup, so old accounts still work */
void loadCustomersFromFile() {
    FILE *fp = fopen(CUSTOMER_FILE, "r");
    if (fp == NULL) return;   /* first run: file doesn't exist yet, that's fine */

    char user[30], pass[30];
    int count = 0;
    while (fscanf(fp, "%29s %29s", user, pass) == 2) {
        CustomerNode *node = (CustomerNode *)malloc(sizeof(CustomerNode));
        strcpy(node->username, user);
        strcpy(node->password, pass);
        node->next = custHead;
        custHead = node;
        count++;
    }
    fclose(fp);
    if (count > 0)
        printf("Loaded %d saved customer account(s) from %s.\n", count, CUSTOMER_FILE);
}

int registerCustomer(const char *username, const char *password) {
    if (findCustomer(username) != NULL) return 0;  /* already exists */
    CustomerNode *node = (CustomerNode *)malloc(sizeof(CustomerNode));
    strcpy(node->username, username);
    strcpy(node->password, password);
    node->next = custHead;
    custHead = node;
    saveCustomerToFile(username, password);   /* persist to customers.txt */
    return 1;
}

int loginCustomer(const char *username, const char *password) {
    CustomerNode *c = findCustomer(username);
    if (c == NULL) return 0;
    return strcmp(c->password, password) == 0;
}

/* ------------------------------------------------------------
   8. DASHBOARD
   ------------------------------------------------------------ */
void showDashboard() {
    int menuCount = 0;
    FoodNode *f = menuHead;
    while (f != NULL) { menuCount++; f = f->next; }

    int pendingCount = 0;
    OrderNode *o = queueFront;
    while (o != NULL) { pendingCount++; o = o->next; }

    printf("\n================ ADMIN DASHBOARD ================\n");
    printf(" Food Items in Menu     : %d\n", menuCount);
    printf(" Orders Pending (Queue) : %d\n", pendingCount);
    printf(" Orders Processed       : %d\n", totalOrdersProcessed);
    printf(" Total Revenue          : %.2f\n", totalRevenue);
    printf("===================================================\n");
}

/* ------------------------------------------------------------
   9. SEED DATA (so the menu isn't empty on first run)
   ------------------------------------------------------------ */
void seedMenu() {
    addFood("Chicken Burger", 250.0f, 0);
    addFood("Beef Kacchi", 350.0f, 0);
    addFood("Veg Fried Rice", 180.0f, 0);
    addFood("Chicken Pizza", 550.0f, 0);
    addFood("Cold Coffee", 120.0f, 0);
}

/* ------------------------------------------------------------
   10. ADMIN PANEL
   ------------------------------------------------------------ */
void adminPanel() {
    char user[30], pass[30];
    printf("\n----- ADMIN LOGIN -----\n");
    printf("Username: ");
    scanf("%29s", user);
    printf("Password: ");
    scanf("%29s", pass);

    if (strcmp(user, ADMIN_USER) != 0 || strcmp(pass, ADMIN_PASS) != 0) {
        printf("Invalid admin credentials.\n");
        return;
    }
    printf("Admin login successful!\n");

    int choice;
    do {
        printf("\n========= ADMIN CONTROL PANEL =========\n");
        printf("1. Add Food\n");
        printf("2. View Menu\n");
        printf("3. Search Food\n");
        printf("4. Update Food\n");
        printf("5. Delete Food\n");
        printf("6. View Orders (Queue)\n");
        printf("7. Process Next Order (FIFO)\n");
        printf("8. Payment History (Stack)\n");
        printf("9. Dashboard\n");
        printf("0. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                char name[50]; float price;
                printf("Food name: ");
                scanf(" %49[^\n]", name);
                printf("Price: ");
                scanf("%f", &price);
                addFood(name, price, 1);
                break;
            }
            case 2:
                viewMenu();
                break;
            case 3: {
                char kw[50];
                printf("Search keyword: ");
                scanf(" %49[^\n]", kw);
                searchFood(kw);
                break;
            }
            case 4: {
                int id; char name[50]; float price;
                printf("Food ID to update: ");
                scanf("%d", &id);
                printf("New name: ");
                scanf(" %49[^\n]", name);
                printf("New price: ");
                scanf("%f", &price);
                if (updateFood(id, name, price))
                    printf("Food item updated.\n");
                else
                    printf("Food ID not found.\n");
                break;
            }
            case 5: {
                int id;
                printf("Food ID to delete: ");
                scanf("%d", &id);
                if (deleteFood(id))
                    printf("Food item deleted.\n");
                else
                    printf("Food ID not found.\n");
                break;
            }
            case 6:
                viewOrders();
                break;
            case 7:
                processOrder();
                break;
            case 8:
                viewPaymentHistory();
                break;
            case 9:
                showDashboard();
                break;
            case 0:
                printf("Admin logged out.\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 0);
}

/* ------------------------------------------------------------
   11. CUSTOMER PANEL
   ------------------------------------------------------------ */
/* Shown once a customer has logged in: no more Register/Login options,
   only actions that make sense for an authenticated customer. */
void loggedInCustomerMenu(const char *loggedInUser) {
    int choice;
    do {
        printf("\n===== Welcome, %s =====\n", loggedInUser);
        printf("1. View Food Menu\n");
        printf("2. Search Food\n");
        printf("3. Place Order\n");
        printf("4. View Pending Orders\n");
        printf("0. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                viewMenu();
                break;
            case 2: {
                char kw[50];
                printf("Search keyword: ");
                scanf(" %49[^\n]", kw);
                searchFood(kw);
                break;
            }
            case 3: {
                int id, qty;
                viewMenu();
                printf("Enter Food ID to order: ");
                scanf("%d", &id);
                printf("Enter quantity: ");
                scanf("%d", &qty);
                if (qty <= 0)
                    printf("Quantity must be positive.\n");
                else
                    enqueueOrder(loggedInUser, id, qty);
                break;
            }
            case 4:
                viewOrders();
                break;
            case 0:
                printf("Logged out. Returning to Customer Panel.\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 0);
}

/* Shown before login: Register / Login / browse-without-account only. */
void customerPanel() {
    int choice;

    do {
        printf("\n========= CUSTOMER PANEL =========\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. View Food Menu\n");
        printf("4. Search Food\n");
        printf("0. Back to Main Menu\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                char user[30], pass[30];
                printf("Choose username: ");
                scanf("%29s", user);
                printf("Choose password: ");
                scanf("%29s", pass);
                if (registerCustomer(user, pass))
                    printf("Registration successful! You can now log in.\n");
                else
                    printf("Username already exists.\n");
                break;
            }
            case 2: {
                char user[30], pass[30];
                printf("Username: ");
                scanf("%29s", user);
                printf("Password: ");
                scanf("%29s", pass);
                if (loginCustomer(user, pass)) {
                    printf("Login successful! Welcome, %s.\n", user);
                    loggedInCustomerMenu(user);   /* switch to the logged-in-only menu */
                } else {
                    printf("Invalid username or password.\n");
                }
                break;
            }
            case 3:
                viewMenu();
                break;
            case 4: {
                char kw[50];
                printf("Search keyword: ");
                scanf(" %49[^\n]", kw);
                searchFood(kw);
                break;
            }
            case 0:
                printf("Returning to main menu.\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 0);
}

/* ------------------------------------------------------------
   12. FREE ALL MEMORY ON EXIT (good practice)
   ------------------------------------------------------------ */
void freeAll() {
    FoodNode *f = menuHead;
    while (f) { FoodNode *t = f; f = f->next; free(t); }

    OrderNode *o = queueFront;
    while (o) { OrderNode *t = o; o = o->next; free(t); }

    PaymentNode *p = stackTop;
    while (p) { PaymentNode *t = p; p = p->next; free(t); }

    CustomerNode *c = custHead;
    while (c) { CustomerNode *t = c; c = c->next; free(t); }
}

/* ------------------------------------------------------------
   13. MAIN
   ------------------------------------------------------------ */
int main() {
    seedMenu();
    loadCustomersFromFile();   /* restore customer accounts saved from previous runs */

    int choice;
    printf("=====================================================\n");
    printf("      ONLINE FOOD DELIVERY SYSTEM (C Language)\n");
    printf("  Linked List + Queue (FIFO) + Stack (LIFO)\n");
    printf("=====================================================\n");

    do {
        printf("\n================ MAIN MENU ================\n");
        printf("1. Admin Panel\n");
        printf("2. Customer Panel\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: adminPanel(); break;
            case 2: customerPanel(); break;
            case 0: printf("Thank you for using the system. Goodbye!\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 0);

    freeAll();
    return 0;
}
