#ifndef APP_H
#define APP_H

#define MAX 100

// === AUTHENTICATION ===
void registerAccount();
int login(char* role_out);
int isValidPassword(const char* password);
void saveAccount(const char* name, const char* position, const char* password);

// === MENU ===
void managerMenu();
void cashierMenu();

#endif