#ifndef MENU_H
#define MENU_H
#include "auth.h"
#include "meds.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cashierMenu();
void managerMenu();
void analyticsMenu();

// Tambahan: Fungsi Analytics
void analyticsMenu() {
    Med meds[100];
    int n = loadMeds(meds);

    if (n == 0) {
        printf("No meds available.\n");
        return;
    }

    int maxPriceIdx = 0, minPriceIdx = 0;
    int maxStockIdx = 0, minStockIdx = 0;

    for (int i = 1; i < n; i++) {
        if (meds[i].price > meds[maxPriceIdx].price) maxPriceIdx = i;
        if (meds[i].price < meds[minPriceIdx].price) minPriceIdx = i;
        if (meds[i].stock > meds[maxStockIdx].stock) maxStockIdx = i;
        if (meds[i].stock < meds[minStockIdx].stock) minStockIdx = i;
    }

    printf("=== Analytics ===\n");
    printf("Most Expensive: %s (Rp%.2f)\n", meds[maxPriceIdx].name, meds[maxPriceIdx].price);
    printf("Cheapest      : %s (Rp%.2f)\n", meds[minPriceIdx].name, meds[minPriceIdx].price);
    printf("Most Stocks   : %s (%d pcs)\n", meds[maxStockIdx].name, meds[maxStockIdx].stock);
    printf("Least Stocks  : %s (%d pcs)\n", meds[minStockIdx].name, meds[minStockIdx].stock);
    printf("Press Enter to continue..."); getchar();
}

void cashierMenu() {
    int choice;
    do {
        printf("=== Cashier Menu ===\n1. Display meds\n2. Calculate cost\n3. Log out\nChoice: ");
        scanf("%d", &choice); getchar(); clearScreen();

        if (choice == 1) {
            displayMeds();
        } else if (choice == 2) {
            Med meds[100];
            int n = loadMeds(meds), qty;
            char code[10];
            float total = 0;

            displayMeds(); // Tampilkan daftar obat dulu
            while (1) {
                printf("Enter med code (or 'done'): "); gets(code);
                if (strcmp(code, "done") == 0) break;
                for (int i = 0; i < n; i++) {
                    if (strcmp(meds[i].code, code) == 0) {
                        printf("Quantity: "); scanf("%d", &qty); getchar();
                        if (qty <= meds[i].stock) {
                            total += meds[i].price * qty;
                            meds[i].stock -= qty;
                        } else {
                            printf("Not enough stock!\n");
                        }
                        break;
                    }
                }
            }

            char deliv;
            printf("Delivery? (y/n): "); scanf("%c", &deliv); getchar();
            if (deliv == 'y') total += 10000;

            printf("TOTAL = Rp%.2f\n", total);
            saveAllMeds(meds, n);
            printf("Press Enter..."); getchar(); clearScreen();
        }
    } while (choice != 3);
}

void managerMenu() {
    int choice;
    do {
        printf("=== Manager Menu ===\n1. Add meds\n2. Display meds\n3. Update meds\n4. Delete meds\n5. Analytics\n6. Log out\nChoice: ");
        scanf("%d", &choice); getchar(); clearScreen();

        switch (choice) {
            case 1: addMed(); break;
            case 2: displayMeds(); break;
            case 3:
                displayMeds(); // Tampilkan meds dulu
                updateMed();
                break;
            case 4: deleteMed(); break;
            case 5: analyticsMenu(); break;
        }
    } while (choice != 6);
}

#endif
