#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "app.h"

#define MEDS_FILE "meds_data.txt"

typedef struct {
    char name[MAX];
    int stock;
    int price;
} Med;

void addNewMeds() {
    FILE* file = fopen(MEDS_FILE, "a");
    if (!file) {
        printf("Gagal membuka file obat.\n");
        return;
    }

    Med med;
    printf("\n--- Add New Meds ---\n");
    printf("Name: ");
    scanf(" %[^\n]", med.name);
    printf("Total stock: ");
    scanf("%d", &med.stock);
    printf("Price: ");
    scanf("%d", &med.price);

    fprintf(file, "%s,%d,%d\n", med.name, med.stock, med.price);
    fclose(file);
    printf("Obat berhasil ditambahkan!\n");
}

void displayMeds() {
    FILE* file = fopen(MEDS_FILE, "r");
    if (!file) {
        printf("Belum ada data obat.\n");
        return;
    }

    Med meds[100];
    int count = 0;

    printf("\n--- List of Meds ---\n");
    printf("| No | Name                  | Stock | Price |\n");
    printf("-----------------------------------------------\n");

    while (fscanf(file, " %[^,],%d,%d\n", meds[count].name, &meds[count].stock, &meds[count].price) == 3) {
        printf("| %-2d | %-20s | %-5d | %-5d |\n", count + 1, meds[count].name, meds[count].stock, meds[count].price);
        count++;
    }
    fclose(file);

    if (count == 0) {
        printf("Tidak ada data obat.\n");
        return;
    }

    int maxPrice = meds[0].price, minPrice = meds[0].price;
    int maxStock = meds[0].stock, minStock = meds[0].stock;
    char* maxPriceName = meds[0].name;
    char* minPriceName = meds[0].name;
    char* maxStockName = meds[0].name;
    char* minStockName = meds[0].name;

    for (int i = 1; i < count; i++) {
        if (meds[i].price > maxPrice) {
            maxPrice = meds[i].price;
            maxPriceName = meds[i].name;
        }
        if (meds[i].price < minPrice) {
            minPrice = meds[i].price;
            minPriceName = meds[i].name;
        }
        if (meds[i].stock > maxStock) {
            maxStock = meds[i].stock;
            maxStockName = meds[i].name;
        }
        if (meds[i].stock < minStock) {
            minStock = meds[i].stock;
            minStockName = meds[i].name;
        }
    }

    printf("\nMost Expensive Meds: %s\n", maxPriceName);
    printf("Cheapest Meds: %s\n", minPriceName);
    printf("Most Stock Available: %s\n", maxStockName);
    printf("Least Stock Available: %s\n", minStockName);
}

void updateMeds() {
    FILE* file = fopen(MEDS_FILE, "r");
    if (!file) {
        printf("Tidak dapat membuka file untuk update.\n");
        return;
    }

    Med meds[100];
    int count = 0;

    while (fscanf(file, " %[^,],%d,%d\n", meds[count].name, &meds[count].stock, &meds[count].price) == 3) {
        count++;
    }
    fclose(file);

    if (count == 0) {
        printf("Tidak ada data obat untuk diupdate.\n");
        return;
    }

    displayMeds();

    int index;
    printf("\nWhich Meds (Meds number): ");
    scanf("%d", &index);
    index--;

    if (index < 0 || index >= count) {
        printf("Nomor tidak valid.\n");
        return;
    }

    printf("New Total Stock: ");
    scanf("%d", &meds[index].stock);
    printf("New Price: ");
    scanf("%d", &meds[index].price);

    file = fopen(MEDS_FILE, "w");
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s,%d,%d\n", meds[i].name, meds[i].stock, meds[i].price);
    }
    fclose(file);
    printf("Obat berhasil diupdate.\n");
}

void deleteMeds() {
    FILE* file = fopen(MEDS_FILE, "r");
    if (!file) {
        printf("Tidak ada data untuk dihapus.\n");
        return;
    }

    Med meds[100];
    int count = 0;

    while (fscanf(file, " %[^,],%d,%d\n", meds[count].name, &meds[count].stock, &meds[count].price) == 3) {
        count++;
    }
    fclose(file);

    if (count == 0) {
        printf("Tidak ada data obat.\n");
        return;
    }

    displayMeds();

    int index;
    printf("\nWhich meds you want to throw away? (in number!): ");
    scanf("%d", &index);
    index--;

    if (index < 0 || index >= count) {
        printf("Nomor tidak valid.\n");
        return;
    }

    file = fopen(MEDS_FILE, "w");
    for (int i = 0; i < count; i++) {
        if (i != index) {
            fprintf(file, "%s,%d,%d\n", meds[i].name, meds[i].stock, meds[i].price);
        }
    }
    fclose(file);
    printf("Obat berhasil dihapus.\n");
}

void managerMenu() {
    int choice;
    while (1) {
        printf("\n=== MANAGER MENU ===\n");
        printf("1. Add new meds\n");
        printf("2. Display meds\n");
        printf("3. Update meds\n");
        printf("4. Delete meds\n");
        printf("5. Log out\n");
        printf("Pilihan: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addNewMeds();
                break;
            case 2:
                displayMeds();
                break;
            case 3:
                updateMeds();
                break;
            case 4:
                deleteMeds();
                break;
            case 5:
                printf("Logging out...\n");
                return;
            default:
                printf("Pilihan tidak valid.\n");
        }
    }
}
