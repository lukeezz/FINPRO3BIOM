#ifndef MEDS_H
#define MEDS_H
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    char code[10];
    int stock;
    float price;
} Med;

void storeMed(Med m) {
    FILE *file = fopen("meds.txt", "ab");
    fwrite(&m, sizeof(Med), 1, file);
    fclose(file);
}

void displayMeds() {
    Med m;
    FILE *file = fopen("meds.txt", "rb");
    if (!file) {
        printf("No meds found.\n");
    } else {
        printf("=== List of Meds ===\n");
        while (fread(&m, sizeof(Med), 1, file)) {
            printf("%s (%s) - Stock: %d - Rp%.2f\n", m.name, m.code, m.stock, m.price);
        }
        fclose(file);
    }
    printf("Press Enter..."); getchar();
}

void addMed() {
    Med m;
    printf("Name: "); gets(m.name);
    printf("Code: "); gets(m.code);
    printf("Stock: "); scanf("%d", &m.stock);
    printf("Price: "); scanf("%f", &m.price);
    getchar();
    storeMed(m);
    printf("Added. Press Enter..."); getchar(); clearScreen();
}

int loadMeds(Med meds[]) {
    FILE *file = fopen("meds.txt", "rb");
    int count = 0;
    if (file) {
        while (fread(&meds[count], sizeof(Med), 1, file)) count++;
        fclose(file);
    }
    return count;
}

void saveAllMeds(Med meds[], int n) {
    FILE *file = fopen("meds.txt", "wb");
    fwrite(meds, sizeof(Med), n, file);
    fclose(file);
}

void updateMed() {
    Med meds[100];
    int n = loadMeds(meds);
    char code[10];
    printf("Enter med code to update: "); gets(code);
    for (int i = 0; i < n; i++) {
        if (strcmp(meds[i].code, code) == 0) {
            printf("New name: "); gets(meds[i].name);
            printf("New stock: "); scanf("%d", &meds[i].stock);
            printf("New price: "); scanf("%f", &meds[i].price); getchar();
            break;
        }
    }
    saveAllMeds(meds, n);
    printf("Updated. Press Enter..."); getchar(); clearScreen();
}

void deleteMed() {
    Med meds[100];
    int n = loadMeds(meds);
    char code[10];
    displayMeds();
    printf("Enter med code to delete: "); gets(code);
    for (int i = 0; i < n; i++) {
        if (strcmp(meds[i].code, code) == 0) {
            for (int j = i; j < n - 1; j++) meds[j] = meds[j + 1];
            n--;
            break;
        }
    }
    saveAllMeds(meds, n);
    printf("Deleted. Press Enter..."); getchar(); clearScreen();
}


#endif
