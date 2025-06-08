#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "auth.h"
#include "meds.h"
#include "utils.h"
#include "menu.h"

// Fungsi untuk menampilkan tampilan awal
void showWelcomeScreen() {
    printf("===========================================\n");
    printf("        🌿 Welcome to PharmaSys! 🌿\n");
    printf("===========================================\n\n");
    printf(" Your trusted companion in managing and\n");
    printf(" purchasing medications with ease and safety.\n\n");
    printf(" 💊 Stay healthy. Stay in control. 💊\n\n");
    printf("        ➤ Press Enter to continue...\n");
    getchar(); // Tunggu user tekan Enter
}

int main() {
    int status;
    showWelcomeScreen(); // Tampilkan welcome screen

    while (1) {
        status = loginMenu();
        if (status == -1) break;
        else if (status == 1) cashierMenu();
        else if (status == 2) managerMenu();
    }

    return 0;
}
