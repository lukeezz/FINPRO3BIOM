#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include "auth.h"
#include "meds.h"
#include "utils.h"
#include "menu.h"


void showWelcomeScreen() {
    printf("===========================================\n");
    printf("        🌿 Welcome to PharmaSys! 🌿\n");
    printf("===========================================\n\n");
    printf(" Your trusted companion in managing and\n");
    printf(" purchasing medications with ease and safety.\n\n");
    printf(" 💊 Stay healthy. Stay in control. 💊\n\n");
    printf("        ➤ Press Enter to continue...\n");
    getchar(); 
}

int main() {
    SetConsoleOutputCP(65001);
    showWelcomeScreen(); 
    int status;

    while (1) {
        status = loginMenu();
        if (status == -1) break;
        else if (status == 1) cashierMenu();
        else if (status == 2) managerMenu();
    }

    return 0;
}
