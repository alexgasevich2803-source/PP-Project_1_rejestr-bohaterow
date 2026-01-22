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

//modyfikacja bohatera
void modify_hero(Hero* hero) {
    if (hero == NULL) {
        printf("Błąd: bohater nie istnieje!\n");
        return;
    }
    char input[100];
    printf("\n Modyfikacja bohatera: %s\n", hero->name);

    
    printf("Aktualna rasa: %s\n", hero->race);
    printf("Nowa rasa (Enter aby zachować obecną): ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;
    if (strlen(input) > 0) {
        strcpy(hero->race, input);
    }

    printf("Aktualna klasa: %s\n", hero->class);
    printf("Nowa klasa: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;
    if (strlen(input) > 0) {
        strcpy(hero->class, input);
    }
    
    printf("Aktualny poziom: %d\n", hero->level);
    printf("Nowy poziom: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;
    if (strlen(input) > 0) {
        hero->level = atoi(input);
    }
    
    printf("Aktualna reputacja: %d\n", hero->reputation);
    printf("Nowa reputacja (0-100): ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;
    if (strlen(input) > 0) {
        int new_reputation = atoi(input);
        if (new_reputation >= 0 && new_reputation <= 100) {
            hero->reputation = new_reputation;
        } else {
            printf("Błąd wartośći reputacji.");
        }
    }
    
    printf("Aktualny status: %s\n", hero->status);
    printf("Nowy status (aktywny/na misji/ranny/zaginiony/zawieszony): ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;
    if (strlen(input) > 0) {
        strcpy(hero->status, input);
    }
    
    printf("Dane bohatera zostały zaktualizowane!\n");
}

//sprawdzanie unikalnośći imienia
bool is_name_unique(Hero* head, const char* name) {
    return find_hero(head, name) == NULL;
}

//usuwanie bohatera (!jeśli nie jest na misji)
Hero* delete_hero(Hero* head, const char* name) {
    if (head == NULL) return NULL;

    //sprawdzenie istnienia bohatera
    Hero* to_delete = find_hero(head, name);
    if (to_delete == NULL) {
        printf("Bohater o imieniu '%s' nie istnieje.\n", name);
        return head;
    }
    //czy jest na misji
    if (strcmp(to_delete->status, "na misji") == 0) {
        printf("Nie można usunąć bohatera '%s' - jest na misji!\n", name);
        return head;
    }

    //usuwanie pierwszego elementu
    if (strcmp(head->name, name) == 0) {
        Hero* new_head = head->next;
        free(head);
        printf("Usunięto bohatera: %s\n", name);
        return new_head;
    }

    //usuwanie elementu ze środka/końca
    Hero* temp = head;
    while (temp->next != NULL && strcmp(temp->next->name, name) != 0) {
        temp = temp->next;
    }
    if (temp->next != NULL) {
        Hero* next_next = temp->next->next;
        free(temp->next);
        temp->next = next_next;
        printf("Usunięto bohatera: %s\n", name);
    }
    return head;
}

//zapisanie listy do pliku tekstowego
void save_to_file(Hero* head, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Nie można otworzyć pliku do zapisu.\n");
        return;
    }
    Hero* temp = head;
    while (temp != NULL) {
        fprintf(file, "%s;%s;%s;%d;%d;%s\n",
                temp->name, temp->race, temp->class,
                temp->level, temp->reputation, temp->status);
        temp = temp->next;
    }
    fclose(file);
    printf("Zapisano rejestr do pliku: %s\n", filename);
}

//wczytanie listy z pliku
Hero* load_from_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Nie można otworzyć pliku do odczytu.\n");
        return NULL;
    }
    Hero* head = NULL;
    char line[300];
    
    while (fgets(line, sizeof(line), file)) {
        char name[100], race[50], class[50], status[50];
        int level, reputation;
        
        if (sscanf(line, "%99[^;];%49[^;];%49[^;];%d;%d;%49s",
                  name, race, class, &level, &reputation, status) >= 5) {
            head = push_back(head, name, race, class, level, reputation, status); 
        }
    }
    
    fclose(file);
    printf("Wczytano rejestr z pliku: %s\n", filename);
    return head;
}

//zwolnienie listy
void free_list(Hero* head) {
    Hero* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
    printf("Pamięć zwolniona.\n");
}

//menu
void menu() {
    printf("\n=== REJESTR BOHATERÓW GILDII ===\n");
    printf("1. Dodaj bohatera\n");
    printf("2. Wyświetl wszystkich\n");
    printf("3. Wyszukaj bohatera\n");
    printf("4. Modyfikuj bohatera\n");
    printf("5. Usuń bohatera\n");
    printf("6. Zapisz do pliku\n");
    printf("7. Wczytaj z pliku\n");
    printf("8. Wyjście\n");
    printf("Wybierz opcję: ");
}

int main() {
    Hero* head = NULL;
    int choice;
    char name[100], race[50], class[50], status[50];
    int level, reputation;
    char filename[100];

    do {
        menu();
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Imię: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0;
                if (!is_name_unique(head, name)) {
                    printf("Błąd: Bohater '%s' już istnieje.\n", name);
                    break;
                }
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
                while (reputation < 0 || reputation > 100) {
                    printf("Błąd: Reputacja musi byc w zakresie 0-100!\n");
                    printf("Reputacja: ");
                    scanf("%d", &reputation);
                }
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
                printf("Podaj imię bohatera do modyfikacji: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0;

                Hero* to_modify = find_hero(head, name);
                if (to_modify != NULL) {
                    modify_hero(to_modify);
                } else {
                    printf("Nie znaleziono bohatera '%s'\n", name);
                }
                break;
                    
            
            case 5:
                printf("Podaj imię bohatera do usunięcia: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0;
                head = delete_hero(head, name);
                break;

            case 6:
                printf("Podaj nazwę pliku do zapisu: ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = 0;
                save_to_file(head, filename);
                break;

            case 7:
                printf("Podaj nazwę pliku do odczytu: ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = 0;
                free_list(head);
                head = load_from_file(filename);
                break;

            case 8:
                printf("Zamykanie programu...\n");
                break;

            default:
                printf("Nieprawidłowa opcja!\n");
                break;
        }
    } while (choice != 8);

    free_list(head);
    return 0;
}
