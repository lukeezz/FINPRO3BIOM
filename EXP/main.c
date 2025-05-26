#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_OBAT 100
#define MAX_USER 50

typedef struct {
    char kode[10];
    char nama[50];
    int stok;
    int harga;
} Obat;

typedef struct {
    char username[50];
    char password[50];
    char role[10]; // "kasir" atau "manajer"
} User;

Obat daftarObat[MAX_OBAT];
int jumlahObat = 0;

User daftarUser[MAX_USER];
int jumlahUser = 0;

// Fungsi-fungsi
void loadUser();
void simpanUser();
void registerUser();
int login(char *role);
void menuKasir();
void menuManajer();
void tambahObat();
void tampilObat();

int main() {
    int pilihan;
    char role[10];
    loadUser();

    do {
        printf("=== Menu Utama ===\n");
        printf("1. Login\n");
        printf("2. Register\n");
        printf("3. Exit\n");
        printf("Pilih: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                if (login(role)) {
                    if (strcmp(role, "kasir") == 0)
                        menuKasir();
                    else
                        menuManajer();
                }
                break;
            case 2:
                registerUser();
                break;
        }
    } while (pilihan != 3);

    return 0;
}

void loadUser() {
    FILE *f = fopen("user.txt", "r");
    if (!f) return;

    while (fscanf(f, "%s %s %s", daftarUser[jumlahUser].username, daftarUser[jumlahUser].password, daftarUser[jumlahUser].role) != EOF) {
        jumlahUser++;
    }
    fclose(f);
}

void simpanUser() {
    FILE *f = fopen("user.txt", "w");
    for (int i = 0; i < jumlahUser; i++) {
        fprintf(f, "%s %s %s\n", daftarUser[i].username, daftarUser[i].password, daftarUser[i].role);
    }
    fclose(f);
}

void registerUser() {
    printf("=== Register ===\n");
    printf("Username: ");
    scanf("%s", daftarUser[jumlahUser].username);
    printf("Password: ");
    scanf("%s", daftarUser[jumlahUser].password);
    printf("Role (kasir/manajer): ");
    scanf("%s", daftarUser[jumlahUser].role);
    jumlahUser++;
    simpanUser();
}

int login(char *role) {
    char username[50], password[50];
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);
    for (int i = 0; i < jumlahUser; i++) {
        if (strcmp(daftarUser[i].username, username) == 0 &&
            strcmp(daftarUser[i].password, password) == 0) {
            strcpy(role, daftarUser[i].role);
            return 1;
        }
    }
    printf("Login gagal.\n");
    return 0;
}

void menuKasir() {
    int pilihan;
    do {
        printf("=== Menu Kasir ===\n");
        printf("1. Tampilkan Obat\n");
        printf("2. Hitung Biaya\n");
        printf("3. Logout\n");
        printf("Pilih: ");
        scanf("%d", &pilihan);
        switch (pilihan) {
            case 1:
                tampilObat();
                break;
            case 2:
                // hitungBiaya();
                break;
        }
    } while (pilihan != 3);
}

void menuManajer() {
    int pilihan;
    do {
        printf("=== Menu Manajer ===\n");
        printf("1. Tambah Obat\n");
        printf("2. Tampilkan Obat\n");
        printf("3. Logout\n");
        printf("Pilih: ");
        scanf("%d", &pilihan);
        switch (pilihan) {
            case 1:
                tambahObat();
                break;
            case 2:
                tampilObat();
                break;
        }
    } while (pilihan != 3);
}

void tambahObat() {
    printf("Kode Obat: ");
    scanf("%s", daftarObat[jumlahObat].kode);
    printf("Nama Obat: ");
    scanf("%s", daftarObat[jumlahObat].nama);
    printf("Stok: ");
    scanf("%d", &daftarObat[jumlahObat].stok);
    printf("Harga: ");
    scanf("%d", &daftarObat[jumlahObat].harga);
    jumlahObat++;
    // simpan ke file jika perlu
}

void tampilObat() {
    printf("=== Daftar Obat ===\n");
    for (int i = 0; i < jumlahObat; i++) {
        printf("%s | %s | Stok: %d | Harga: Rp%d\n", daftarObat[i].kode, daftarObat[i].nama, daftarObat[i].stok, daftarObat[i].harga);
    }
}
