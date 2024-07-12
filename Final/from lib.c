#include "market.h"
int main() {
    struct Item stock[MAX_STOCK_SIZE];
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
