#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "auth.h"
#include "meds.h"
#include "utils.h"
#include "menu.h"

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
