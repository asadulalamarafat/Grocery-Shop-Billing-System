#include <stdio.h>
#include <string.h>

#define MAX 100
#define ADMIN_PASS "1234"

struct Product {
    int id;
    char name[30];
    float price;
    int qty;
};

struct Product p[MAX];
int count = 0;
int autoID = 1;

float totalSales = 0;
float VAT = 0.05;
float DISCOUNT = 0.10;

//Admin Check
int isAdmin() {
    char pass[20];
    printf("Enter admin password: ");
    scanf("%s", pass);
    return strcmp(pass, ADMIN_PASS) == 0;
}

//  Add Product
void addProduct() {
    p[count].id = autoID++;

    printf("Product name: ");
    scanf("%s", p[count].name);

    printf("Price: ");
    scanf("%f", &p[count].price);

    printf("Quantity: ");
    scanf("%d", &p[count].qty);

    count++;
    printf(" Product added!\n");
}

//  Display Products
void displayProducts() {
    if (count == 0) {
        printf("No products found!\n");
        return;
    }

    printf("\nID  Name   Price  Qty  Status\n");
    printf("--------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("%d  %s  %.2f  %d  ",
               p[i].id, p[i].name, p[i].price, p[i].qty);

        if (p[i].qty == 0)
            printf("OUT\n");
        else if (p[i].qty <= 5)
            printf("LOW\n");
        else
            printf("OK\n");
    }
}

//  Update Product
void updateProduct() {
    int id;
    printf("Enter product ID: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (p[i].id == id) {
            printf("New price: ");
            scanf("%f", &p[i].price);
            printf("New quantity: ");
            scanf("%d", &p[i].qty);
            printf("Updated!\n");
            return;
        }
    }
    printf("Product not found!\n");
}

// Delete Product
void deleteProduct() {
    if (!isAdmin()) {
        printf(" Wrong password!\n");
        return;
    }

    int id;
    printf("Enter product ID: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (p[i].id == id) {
            for (int j = i; j < count - 1; j++)
                p[j] = p[j + 1];

            count--;
            printf(" Product deleted!\n");
            return;
        }
    }
    printf(" Product not found!\n");
}

//  Generate Bill
void generateBill() {
    int id, q;
    char ch;
    float sum = 0;

    do {
        printf("Product ID: ");
        scanf("%d", &id);

        for (int i = 0; i < count; i++) {
            if (p[i].id == id) {
                printf("Quantity: ");
                scanf("%d", &q);

                if (q > p[i].qty) {
                    printf("Not enough stock!\n");
                    return;
                }

                sum += p[i].price * q;
                p[i].qty -= q;
            }
        }

        printf("Add more? (y/n): ");
        scanf(" %c", &ch);

    } while (ch == 'y');

    float vat = sum * VAT;
    float dis = sum * DISCOUNT;
    float bill = sum + vat - dis;

    totalSales += bill;

    printf("\nTotal: %.2f\n", sum);
    printf("VAT: %.2f\n", vat);
    printf("Discount: %.2f\n", dis);
    printf("Final Bill: %.2f\n", bill);
}

// Sales Report
void salesReport() {
    printf("Total Sales: %.2f\n", totalSales);
}

// Search Product
void searchProduct() {
    char name[30];
    printf("Enter name: ");
    scanf("%s", name);

    for (int i = 0; i < count; i++) {
        if (strcmp(p[i].name, name) == 0) {
            printf("Found: ID %d | Price %.2f | Qty %d\n",
                   p[i].id, p[i].price, p[i].qty);
            return;
        }
    }
    printf("Product not found!\n");
}

 // Low Stock
void lowStock() {
    printf("Low stock products:\n");
    for (int i = 0; i < count; i++) {
        if (p[i].qty <= 5)
            printf("%s (%d)\n", p[i].name, p[i].qty);
    }
}

//  Change VAT & Discount
void changeVat() {
    if (!isAdmin()) {
        printf(" Wrong password!\n");
        return;
    }
    printf("New VAT: ");
    scanf("%f", &VAT);
    printf("New Discount: ");
    scanf("%f", &DISCOUNT);
}

//  Total Products 
void totalProducts() {
    printf("Total products: %d\n", count);
}

void menu() {
    int c;
    while (1) {
        printf("\n--- Grocery Billing ---\n");
        printf("1. Add Product\n");
        printf("2. Display Products\n");
        printf("3. Update Product\n");
        printf("4. Delete Product\n");
        printf("5. Generate Bill\n");
        printf("6. Sales Report\n");
        printf("7. Search Product\n");
        printf("8. Low Stock\n");
        printf("9. Change VAT & Discount\n");
        printf("10. Total Products\n");
        printf("11. Exit\n");

        scanf("%d", &c);

        switch (c) {
            case 1: addProduct(); break;
            case 2: displayProducts(); break;
            case 3: updateProduct(); break;
            case 4: deleteProduct(); break;
            case 5: generateBill(); break;
            case 6: salesReport(); break;
            case 7: searchProduct(); break;
            case 8: lowStock(); break;
            case 9: changeVat(); break;
            case 10: totalProducts(); break;
            case 11: return;
            default: printf("Wrong choice!\n");
        }
    }
}

int main() {
    menu();
    return 0;
}
