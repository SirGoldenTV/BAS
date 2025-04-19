#include <stdio.h>

#define TAILLE_GRILLE 1
#define START_GOLD 20
#define WIN_GOLD 50


int grille[TAILLE_GRILLE][TAILLE_GRILLE];
int gold = START_GOLD;

// enum section.
enum ACTION {
    END = 0,
    BUILD = 1,
    PASS = 2,
};

enum BUILDING {
    HOUSE = 1,
    TOWER = 2,
};

/**
 * Show the grid content.
 */
void show_grille() {
    printf("\n");
    for (int i = 0 ; i < TAILLE_GRILLE ; i++) {
        for(int j = 0 ; j < TAILLE_GRILLE; j++) {
            printf("%d ", grille[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void show_gold() {
    printf("Gold restant : %d\n", gold);
}

/**
 * Win some gold by the value given.
 */
void add_gold(int value) {
    gold += value;
}

/**
 * Loose some gold by the value given.
 */
void pay_gold(int value) {
    gold -= value;
}

/**
 * Determine if the game is finished. 0 for no, 1 for yes.
 */
int is_end_of_game() {
    if (gold > WIN_GOLD) {
        printf("GG ! La partie est finie. Le quota a ete atteint !\n");
        return 1;
    }

    for (int i = 0 ; i < TAILLE_GRILLE ; i++) {
        for(int j = 0 ; j < TAILLE_GRILLE; j++) {
            if (grille[i][j] == 0) {
                return 0; // Not end.
            }
        }
    }
    printf("GG ! La partie est finie. Il n'y a plus de place.\n");
    return 1; // The game is finished.
}

void show_one_action(enum ACTION a) {
    switch (a)
    {
        case BUILD:
            printf("\n- BUILD : tape : 1");
            break;
        case PASS:
            printf("\n- PASS : tape : 2");
            break;

        case END:
            printf("\n- END : tape : 0");
            break;
    
    default:
        break;
    }
}

void show_actions() {
    printf("\nAction select : \n");
    enum ACTION actions[] = { BUILD, PASS, END};
    int size = sizeof(actions) / sizeof(actions[0]);
    for (int i = 0; i < size; i++)
    {
        show_one_action(actions[i]);
    }
    
    printf("\n");
}

void calcul_gold() {
    for (int i = 0 ; i < TAILLE_GRILLE ; i++) {
        for(int j = 0 ; j < TAILLE_GRILLE; j++) {
            if (grille[i][j] == HOUSE) {
                add_gold(HOUSE);
            } 
            else if (grille[i][j] == TOWER) {
                add_gold(TOWER);
            }
        }
    }
}

void show_one_build(enum BUILDING a) {
    switch (a)
    {
        case HOUSE:
            printf("\n- HOUSE (PRIX : %d): tape : 1", HOUSE);
            break;

        case TOWER:
            printf("\n- TOWER (PRIX : %d): tape : 2", TOWER);
            break;
    
    default:
        break;
    }
}

void show_menu_build() {
    printf("\nBuild select : \n");
    enum BUILDING actions[] = { HOUSE, TOWER};
    int size = sizeof(actions) / sizeof(actions[0]);
    for (int i = 0; i < size; i++)
    {
        show_one_build(actions[i]);
    }
    
    printf("\n");
}

int is_correct_building(int building) {
    enum BUILDING actions[] = { HOUSE, TOWER};
    int size = sizeof(actions) / sizeof(actions[0]);
    for (int i = 0; i < size; i++) {
        if (building == (int)actions[i]) {
            return 0;
        }
    }

    printf("\nBatiment incorrect ! \n");
    return 1;
}

void apply_build(int building, int x, int y) {
    if (x < 0 || x >= TAILLE_GRILLE) {
        fprintf(stderr, "Erreur, X en dehors de la grille.");
        return;
    }

    if (y < 0 || y >= TAILLE_GRILLE) {
        fprintf(stderr, "Erreur, Y en dehors de la grille.");
        return;
    }

    grille[x][y] = building;
    pay_gold(building);
}

void play_build() {
    int action_build;
    do {
        show_menu_build();
        scanf("%d", &action_build);
    } while (is_correct_building(action_build));
    
    printf("\nEntrer les coordonnees du batiment \"X Y\" : \n");
    int x,y;
    scanf("%d %d", &x, &y);
    apply_build(action_build, x, y);
}

void play_action(int action) {
    switch (action)
    {
        case BUILD:
            calcul_gold();
            play_build();
            break;
        case PASS:    
            printf("\nYou pass a turn.\n");
            calcul_gold();
        default:
            break;
    }
    
}

int main() {
  
    show_grille();
    show_gold();

    while (is_end_of_game() == 0) {
        show_actions();
        int action_user;
        scanf("%d", &action_user);
        if (action_user == END)
        {
            printf("\nEND REQUESTED\n");
            break;
        }
        play_action(action_user);
        show_grille();
        show_gold();
    }

    return 0;
}

