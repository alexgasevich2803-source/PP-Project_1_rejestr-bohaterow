#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// DEFINIOWANIE STRUKTUR
#define MAX_IMIE 100  // Maksymalna dlugosc imienia

// Statusy bohatera
#define AKTYWNY 0
#define NA_MISJI 1
#define RANNY 2
#define ZAGINIONY 3
#define ZAWIESZONY 4

// Struktura bohatera
typedef struct {
    char imie[MAX_IMIE];  // Imie bohatera
    int poziom;           // Poziom doswiadczenia
    int reputacja;        // Reputacja (0-100)
    int status;           // Aktualny status
} Hero;

// Wezel listy
typedef struct Node {
    Hero dane;
    struct Node* next;
} Node;

int main() {
    printf("=== REJESTR BOHATEROW GILDII ===\n");
    printf("Projekt...\n");
    
    return 0;
}
