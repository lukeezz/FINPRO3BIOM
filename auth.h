#ifndef AUTH_H
#define AUTH_H
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char username[50];
    char password[50];
    int isManager;
} User;

int loginMenu();

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
