#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//struktura bohatera
typedef struct Hero {
    char name[100];          //imię
    char race[50];           //rasa
    char class[50];          //klasa
    int level;               //poziom doświadczenia
    int reputation;          //reputacja (0-100)
    char status[50];         //status
    struct Hero* next;       //wskaźnik na następny element listy
} Hero;

//menu
void menu() {
    printf("\n=== REJESTR BOHATERÓW GILDII ===\n");
    printf("1. Dodaj bohatera\n");
    printf("2. Wyświetl wszystkich\n");
    printf("3. Wyszukaj bohatera\n");
    printf("4. Usuń bohatera\n");
    printf("5. Wyjście\n");
    printf("Wybierz opcję: ");
}

int main() {
    Hero* head = NULL;
    int choice;

    printf("=== REJESTR BOHATERÓW GILDII ===\n");
    printf("System rejestracji bohaterów!\n");
    printf("Projekt...\n");
    
    do {
        menu();
        scanf("%d", &choice);
        getchar(); //usunięcie znaku nowej linii

        switch (choice) {
            case 1:
                printf("...\n");
                break;

            case 2:
                printf("...\n");
                break;

            case 3:
                printf("...\n");
                break;

            case 4:
                printf("...\n");
                break;

            case 5:
                printf("Zamykanie programu...\n");
                break;

            default:
                printf("Nieprawidłowa opcja!\n");
                break;
        }
    } while (choice != 5);

    printf("Pamięć zwolniona.\n");
    return 0;
}
