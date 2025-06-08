#ifndef AUTH_H
#define AUTH_H
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char username[50];
    char password[50];
    int isManager;
} User;

int loginMenu();

int isValidPassword(const char *password) {
    int len = strlen(password);
    if (len < 8) return 0;

    int hasUpper = 0, hasDigit = 0;
    for (int i = 0; i < len; i++) {
        if (isupper(password[i])) hasUpper = 1;
        if (isdigit(password[i])) hasDigit = 1;
    }

    return hasUpper && hasDigit;
}

int login() {
    char username[50], password[50];
    FILE *file = fopen("users.txt", "rb");
    if (!file) return 0;
    User u;

    printf("Username: "); fgets(username, sizeof(username), stdin);
    printf("Password: "); fgets(password, sizeof(password), stdin);

    username[strcspn(username, "\n")] = '\0';
    password[strcspn(password, "\n")] = '\0';

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
    char tempPassword[50];
    printf("New username: "); fgets(u.username, sizeof(u.username), stdin);
    u.username[strcspn(u.username, "\n")] = '\0';

    do {
        printf("New password: "); fgets(tempPassword, sizeof(tempPassword), stdin);
        tempPassword[strcspn(tempPassword, "\n")] = '\0';
        if (!isValidPassword(tempPassword)) {
            printf("Password must be at least 8 characters long, contain one uppercase letter, and one number.\n");
        }
    } while (!isValidPassword(tempPassword));
    
    strcpy(u.password, tempPassword);

    printf("Is Manager? (1=Yes, 0=No): "); scanf("%d", &u.isManager); getchar();
    FILE *file = fopen("users.txt", "ab");
    fwrite(&u, sizeof(User), 1, file);
    fclose(file);
    printf("Registered. Press Enter..."); getchar(); clearScreen();
}

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

#endif
