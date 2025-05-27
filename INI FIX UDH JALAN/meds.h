#ifndef MEDS_H
#define MEDS_H

typedef struct {
    char name[50];
    char code[10];
    int stock;
    float price;
} Med;

void displayMeds();
void addMed();
void updateMed();
void deleteMed();
int loadMeds(Med meds[]);
void saveAllMeds(Med meds[], int n);

#endif
