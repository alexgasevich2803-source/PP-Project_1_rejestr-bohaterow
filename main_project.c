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

//tworzenie nowego bohatera
Hero* create_hero(const char* name, const char* race, const char* class, int level, int reputation, const char* status) {
    Hero* new_hero = (Hero*)calloc(1, sizeof(Hero));
    if (new_hero == NULL) {
        printf("Błąd alokacji pamięci!\n");
        return NULL;
    }
    strcpy(new_hero->name, name);
    strcpy(new_hero->race, race);
    strcpy(new_hero->class, class);
    new_hero->level = level;
    new_hero->reputation = reputation;
    strcpy(new_hero->status, status);
    new_hero->next = NULL;
    return new_hero;
}

//dodanie bohatera na koniec listy
Hero* push_back(Hero* head, const char* name, const char* race, const char* class, int level, int reputation, const char* status) {
    Hero* new_hero = create_hero(name, race, class, level, reputation, status);
    if (new_hero == NULL) return head;

    if (head == NULL) {
        return new_hero;
    }

    Hero* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new_hero;
    return head;
}

//wypisywanie wszystkich bohaterów
void print_list(Hero* head) {
    if (head == NULL) {
        printf("Rejestr jest pusty.\n");
        return;
    }
    printf("=== Rejestr Bohaterów ===\n");
    Hero* temp = head;
    while (temp != NULL) {
        printf("Imię: %s | Rasa: %s | Klasa: %s | Poziom: %d | Reputacja: %d | Status: %s\n",
               temp->name, temp->race, temp->class, temp->level, temp->reputation, temp->status);
        temp = temp->next;
    }
    printf("\n");
}

//wyszukiwanie bohatera po imieniu
Hero* find_hero(Hero* head, const char* name) {
    Hero* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

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
    char name[100], race[50], class[50], status[50];
    int level, reputation;

    printf("=== REJESTR BOHATERÓW GILDII ===\n");
    
    
    do {
        menu();
        scanf("%d", &choice);
        getchar(); // usunięcie z naku nowej linii

        switch (choice) {
            case 1:
                printf("Imię: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0;
                printf("Rasa: ");
                fgets(race, sizeof(race), stdin);
                race[strcspn(race, "\n")] = 0;
                printf("Klasa: ");
                fgets(class, sizeof(class), stdin);
                class[strcspn(class, "\n")] = 0;
                printf("Poziom: ");
                scanf("%d", &level);
                printf("Reputacja (0-100): ");
                scanf("%d", &reputation);
                getchar();
                printf("Status (aktywny/na misji/ranny/zaginiony/zawieszony): ");
                fgets(status, sizeof(status), stdin);
                status[strcspn(status, "\n")] = 0;

                head = push_back(head, name, race, class, level, reputation, status);
                printf("Bohater dodany!\n");
                break;

            case 2:
                print_list(head);
                break;

            case 3:
                printf("Podaj imię do wyszukania: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0;
                Hero* found = find_hero(head, name);
                if (found != NULL) {
                    printf("Znaleziono: %s | Rasa: %s | Klasa: %s | Poziom: %d | Reputacja: %d | Status: %s\n",
                           found->name, found->race, found->class, found->level, found->reputation, found->status);
                } else {
                    printf("Nie znaleziono bohatera o imieniu '%s'\n", name);
                }
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
