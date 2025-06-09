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

int loadMeds(Med meds[]);

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

int isMedNameExist(const char* name, Med meds[], int n) {
    for (int i = 0; i < n; i++) {
        if (strcmp(meds[i].name, name) == 0) {
            return 1;
        }
    }
    return 0;
}

void addMed() {
    Med m;
    Med meds[100];
    int n = loadMeds(meds);

    while (1) {
        printf("Name: ");
        fgets(m.name, sizeof(m.name), stdin);
        m.name[strcspn(m.name, "\n")] = '\0';  

        if (isMedNameExist(m.name, meds, n)) {
            printf("Error: Med with the same name already exists!\n");
            printf("Do you still want to add meds? (Y/N): ");
            char choice = getchar(); getchar(); 
            if (choice == 'N' || choice == 'n') {
                printf("Cancelled. Press Enter..."); getchar(); clearScreen();
                return;
            }
            clearScreen();
        } else {
            break; 
        }
    }

    printf("Code: ");
    fgets(m.code, sizeof(m.code), stdin);
    m.code[strcspn(m.code, "\n")] = '\0'; 

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

    printf("Enter med code to update: ");
    fgets(code, sizeof(code), stdin);
    code[strcspn(code, "\n")] = '\0';  // hapus newline

    for (int i = 0; i < n; i++) {
        if (strcmp(meds[i].code, code) == 0) {
            printf("New name: ");
            fgets(meds[i].name, sizeof(meds[i].name), stdin);
            meds[i].name[strcspn(meds[i].name, "\n")] = '\0';

            printf("New stock: ");
            scanf("%d", &meds[i].stock);

            printf("New price: ");
            scanf("%f", &meds[i].price);

            getchar(); // membersihkan newline setelah scanf
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
    printf("Enter med code to delete: ");
    fgets(code, sizeof(code), stdin);
    code[strcspn(code, "\n")] = '\0'; // hapus newline

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
