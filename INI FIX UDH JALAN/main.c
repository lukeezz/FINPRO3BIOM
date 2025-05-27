#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "auth.h"
#include "meds.h"
#include "utils.h"

typedef struct {
    char username[50];
    char password[50];
    int isManager;
} User;

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// === AUTH ===
int loginMenu() {
    int choice;
    do {
        printf("=== AUTHENTICATION ===\n1. Login\n2. Register\n3. Exit\nChoice: ");
        scanf("%d", &choice); getchar(); clearScreen();
        switch (choice) {
            case 1: return login();
            case 2: registerUser(); break;
            case 3: return -1;
        }
    } while (1);
}

int login() {
    char username[50], password[50];
    FILE *file = fopen("users.txt", "rb");
    if (!file) return 0;
    User u;
    printf("Username: "); gets(username);
    printf("Password: "); gets(password);
    while (fread(&u, sizeof(User), 1, file)) {
        if (strcmp(u.username, username) == 0 && strcmp(u.password, password) == 0) {
            fclose(file);
            return u.isManager ? 2 : 1;
        }
    }
    fclose(file);
    printf("Login failed. Press Enter..."); getchar(); clearScreen();
    return loginMenu();
}

void registerUser() {
    User u;
    printf("New username: "); gets(u.username);
    printf("New password: "); gets(u.password);
    printf("Is Manager? (1=Yes, 0=No): "); scanf("%d", &u.isManager); getchar();
    FILE *file = fopen("users.txt", "ab");
    fwrite(&u, sizeof(User), 1, file);
    fclose(file);
    printf("Registered. Press Enter..."); getchar(); clearScreen();
}

// === MEDS ===
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
    printf("Press Enter..."); getchar(); clearScreen();
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
    displayMeds();
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

// === MENUS ===
void cashierMenu() {
    int choice;
    do {
        printf("=== Cashier Menu ===\n1. Display meds\n2. Calculate cost\n3. Log out\nChoice: ");
        scanf("%d", &choice); getchar(); clearScreen();
        if (choice == 1) displayMeds();
        else if (choice == 2) {
            Med meds[100];
            int n = loadMeds(meds), qty;
            char code[10];
            float total = 0;
            while (1) {
                printf("Enter med code (or 'done'): "); gets(code);
                if (strcmp(code, "done") == 0) break;
                for (int i = 0; i < n; i++) {
                    if (strcmp(meds[i].code, code) == 0) {
                        printf("Quantity: "); scanf("%d", &qty); getchar();
                        if (qty <= meds[i].stock) {
                            total += meds[i].price * qty;
                            meds[i].stock -= qty;
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
        printf("=== Manager Menu ===\n1. Add meds\n2. Display meds\n3. Update meds\n4. Delete meds\n5. Log out\nChoice: ");
        scanf("%d", &choice); getchar(); clearScreen();
        switch (choice) {
            case 1: addMed(); break;
            case 2: displayMeds(); break;
            case 3: updateMed(); break;
            case 4: deleteMed(); break;
        }
    } while (choice != 5);
}

// === MAIN ===
int main() {
    int status;
    while (1) {
        status = loginMenu();
        if (status == -1) break;
        else if (status == 1) cashierMenu();
        else if (status == 2) managerMenu();
    }
    return 0;
}
