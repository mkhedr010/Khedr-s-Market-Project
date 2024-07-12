#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STOCK_SIZE 1000
struct Item {
    int barcode;
    char name[50];
    char size[20];
    int numAvailable;
    char production_date[11];
    char expiration_date[11];
    float price;
    float offer;
    char category[20];
};

void display (struct Item stock[], int numItems) //display al items in the stock
{
	printf("Here is a list of all items \n");

    for (int i = 0; i < numItems; i++) {
			printf("Item number %d \n", i);
        printf("Barcode: %d | Name: %s | Size: %s | Available amount: %d | Production date: %s \nExpiration date: %s | Price: %.2f | Offer: %.2f | Catefory: %s\n", stock[i].barcode, stock[i].name,
                stock[i].size, stock[i].numAvailable, stock[i].production_date,
                stock[i].expiration_date, stock[i].price, stock[i].offer, stock[i].category);
                			printf("\n");
                			printf("\n");

    }
	
	}
// update changes into file & write another file 
void writeF(struct Item stock[], int numItems) {
    FILE *fp;
    char filename[100];

    printf("Enter name for the file you want to save the changes in: ");
    scanf("%s", filename);

    fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Failed to create file.\n");
        return;
    }

    for (int i = 0; i < numItems; i++) {
        fprintf(fp, "%d,%s,%s,%d,%s,%s,%.2f,%.2f,%s\n", stock[i].barcode, stock[i].name,
                stock[i].size, stock[i].numAvailable, stock[i].production_date,
                stock[i].expiration_date, stock[i].price, stock[i].offer, stock[i].category);
    }

    fclose(fp);
    printf("Wrote %d items to file.\n", numItems);
}
// read all the items exist allready in the file
void readf(struct Item stock[], int *numItems) {
    FILE *fp;
    char filename[100];

    printf("Enter the refrence file name: ");
    scanf("%s", filename);
    getchar();  
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Failed to open file.\n");
        return;
    }

    *numItems = 0;
    while (*numItems < MAX_STOCK_SIZE && fscanf(fp, "%d,%[^,],%[^,],%d,%[^,],%[^,],%f,%f,%[^,\n]",
                                           &stock[*numItems].barcode, stock[*numItems].name,
                                           stock[*numItems].size, &stock[*numItems].numAvailable,
                                           stock[*numItems].production_date, stock[*numItems].expiration_date,
                                           &stock[*numItems].price, &stock[*numItems].offer,
                                           stock[*numItems].category) == 9) {
        (*numItems)++;
    }

    fclose(fp);
    printf("Read %d items from file.\n", *numItems);
}
// add another item to the stock
void addItem(struct Item *stock, int *numItems) {
    printf("Enter barcode: ");
    scanf("%d", &stock[*numItems].barcode);
    printf("Enter name: ");
    scanf(" %[^\n]s", stock[*numItems].name);
    printf("Enter size: ");
    scanf(" %[^\n]s", stock[*numItems].size);
    printf("Enter number of available items: ");
    scanf("%d", &stock[*numItems].numAvailable);
    printf("Enter production date (dd/mm/yyyy): ");
    scanf("%s", stock[*numItems].production_date);
    printf("Enter expiration date (dd/mm/yyyy): ");
    scanf("%s", stock[*numItems].expiration_date);
    printf("Enter price: ");
    scanf("%f", &stock[*numItems].price);
    printf("Enter offer: ");
    scanf("%f", &stock[*numItems].offer);
    printf("Enter category: ");
    scanf(" %[^\n]s", stock[*numItems].category);

    (*numItems)++;
}
//search for an item by the barecode or the name 
int findItemcode(struct Item stock[], int numItems, int barcode) {
    for (int i = 0; i < numItems; i++) {
        if (stock[i].barcode == barcode) {
            return i;  
        }
    }
    return -1;  
}
// update any changes for sepcfic item in the stock
 void update(struct Item stock[], int numItems) {
    int barcode;
    int choice;

    printf("Enter barcode: ");
    scanf("%d", &barcode);
    getchar();  

    int index = findItemcode(stock, numItems, barcode);
    if (index == -1) {
        printf("Item not found.\n");
        return;
    }

    printf("Select an option to update:\n");
    printf("1. Number of available items\n");
    printf("2. Production date\n");
    printf("3. Expiration date\n");
    printf("4. Price\n");
    printf("5. Offer\n");
    printf("6. Category\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    getchar();  

    switch (choice) {
        case 1:
            printf("Enter new number of available items: ");
            scanf("%d", &stock[index].numAvailable);
            getchar(); 
            break;
        case 2:
            printf("Enter new production date (dd/mm/yyyy): ");
            scanf("%10[^\n]", stock[index].production_date);
            getchar();  
            break;
        case 3:
            printf("Enter new expiration date (dd/mm/yyyy): ");
            scanf("%10[^\n]", stock[index].expiration_date);
            getchar();  
            break;
        case 4:
            printf("Enter new price: ");
            scanf("%f", &stock[index].price);
            getchar(); 
            break;
        case 5:
            printf("Enter new offer: ");
            scanf("%f", &stock[index].offer);
            getchar();  
            break;
        case 6:
            printf("Enter new category: ");
            scanf("%s", stock[index].category);
            getchar();  
            break;
        default:
            printf("Invalid choice.\n");
            return;
    }

    printf("Item updated successfully.\n");
}

void delet(struct Item *stock, int *numItems) {
    int barcode;
    printf("Enter barcode of item to delete: ");
    scanf("%d", &barcode);

    int i;
    for (i = 0; i < *numItems; i++) {
        if (stock[i].barcode == barcode) {
            int j;
            for (j = i; j < *numItems - 1; j++) {
                stock[j] = stock[j + 1];
            }
            (*numItems)--;
            printf("Item with barcode %d deleted successfully!\n", barcode);
            return;
        }
    }

    printf("Item with barcode %d not found in stock.\n", barcode);
}
//update the offers of all items in the stock according to the current date and the their expiration date
void updateOffers(struct Item *stock, int numItems) {
    char currentDate[11];
    printf("Enter current date (dd/mm/yyyy): ");
    scanf("%s", currentDate);

    int i;
    for (i = 0; i < numItems; i++) {
        int dayProd, monthProd, yearProd;
        sscanf(stock[i].production_date, "%d/%d/%d", &dayProd, &monthProd, &yearProd);

        int dayExp, monthExp, yearExp;
        sscanf(stock[i].expiration_date, "%d/%d/%d", &dayExp, &monthExp, &yearExp);

        int dayCurr, monthCurr, yearCurr;   
        sscanf(currentDate, "%d/%d/%d", &dayCurr, &monthCurr, &yearCurr);

        int daysPassed = ((yearCurr - yearProd) * 365) + ((monthCurr - monthProd) * 30) + (dayCurr - dayProd);
        int daysToExpire = ((yearExp - yearProd) * 365) + ((monthExp - monthProd) * 30) + (dayExp - dayProd);

        if (daysPassed > 0 && daysPassed <= daysToExpire) {
            float discountPercentage = (float)daysPassed / daysToExpire * 100;
            stock[i].offer = discountPercentage;
        } else {
            stock[i].offer = 0;
        }
    }

    printf("Offers updated based on expiration date.\n");
}
// takes order from the user and compute the total price and saving and also update the stock after items been bought

void takeOrder(struct Item *stock, int numItems) {
  
    char search[50]; 
    printf("Enter barcode or name of item to order: ");
    scanf("%s", search); 

    int i;
    int found = 0;
    float totalPrice = 0;
    float totalSavings = 0;
    for (i = 0; i < numItems; i++) {
        if ((strcmp(search, stock[i].name) == 0) || (atoi(search) == stock[i].barcode)) { 
            found = 1;
            printf("Item: %s\n", stock[i].name);
            printf("Size: %s\n", stock[i].size);
            printf("Number of available items: %d\n", stock[i].numAvailable);
            printf("Production date: %s\n", stock[i].production_date);
            printf("Expiration date: %s\n", stock[i].expiration_date);
            printf("Price: $%.2f\n", stock[i].price);
            printf("Offer: %.2f%%\n", stock[i].offer);

            float discount = (stock[i].offer / 100) * stock[i].price;
            float discountedPrice = stock[i].price - discount;

            printf("Discounted price: $%.2f\n", discountedPrice);
            printf("Enter quantity to order: ");
            int quantity;
            scanf("%d", &quantity);

            if (quantity <= stock[i].numAvailable) {
                totalPrice += (discountedPrice * quantity);
                totalSavings += (discount * quantity);

                stock[i].numAvailable -= quantity;
                printf("Order placed successfully!\n");
            } else {
                printf("Error: Quantity exceeds available stock.\n");
            }
            break;
        }
    }

    if (!found) {
        printf("Error: Item not found in stock.\n");
    }

    printf("Total Price: $%.2f\n", totalPrice);
    printf("Total Savings: $%.2f\n", totalSavings);
}

// display warning massege for each expited item in the stock 
void sendWarning(struct Item *stock, int numItems) {
    char currentDate[11];
    printf("Enter current date (dd/mm/yyyy): ");
    scanf("%s", currentDate);

    int i;
    for (i = 0; i < numItems; i++) {
        int dayExp, monthExp, yearExp;
        sscanf(stock[i].expiration_date, "%d/%d/%d", &dayExp, &monthExp, &yearExp);

        int dayCurr, monthCurr, yearCurr;
        sscanf(currentDate, "%d/%d/%d", &dayCurr, &monthCurr, &yearCurr);

        if (yearCurr > yearExp || (yearCurr == yearExp && monthCurr > monthExp) || (yearCurr == yearExp && monthCurr == monthExp && dayCurr > dayExp)) {
            printf("Warning: Item with barcode %d has expired!\n", stock[i].barcode);
        }
    }
}



int main() {
    struct Item stock[MAX_STOCK_SIZE];
    // array (stock) of items 
    int numItems = 0;
    readf(stock, &numItems);

    int choice;
    do {
        printf("\nWelcome to << Bakr & Sisi & Hashem Market! >>\n");
        printf("1. Add item to stock\n");
        printf("2. Update item in stock\n");
        printf("3. Delete item from stock\n");
        printf("4. Update offers based on expiration date\n");
        printf("5. Send warning for expired items\n");
        printf("6. Take order\n");
         printf("7. Display all Items of the Stock\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addItem(stock, &numItems);
                break;
            case 2:
                update(stock, numItems);
                break;
            case 3:
                delet(stock, &numItems);
                break;
            case 4:
                updateOffers(stock, numItems);
                break;
            case 5:
                sendWarning(stock, numItems);
                break;
            case 6:
                takeOrder(stock, numItems);
                break;
            case 7:
                display(stock, numItems);
                break;
            case 8:
                printf("Thank you for using <<Bakr & Sisi & Hashem Market!>>\n");
                break;
                
            default:
                printf("Error: Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 8);

    writeF(stock, numItems);
   

    return 0;
}
