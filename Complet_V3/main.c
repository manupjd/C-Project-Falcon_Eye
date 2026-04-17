#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "knapsack.h"

int is_in_path(int* path, int len, int node) {
    for (int i = 0; i < len; i++) {
        if (path[i] == node) return 1;
    }
    return 0;
}

void print_banner() {
    printf("\n=== FALCON EYE : IA Tactique de Police ===\n");
    printf("Carte 10x10 - Poursuite longue et intense\n\n");
}

// Carte STRUCTURE avec rues -+| ET positions * X
void display_city_structure(int police, int voleur) {
    printf("--- CARTE STRUCTURE (Rues + Positions) ---\n");
    printf("Légende: * = Police(%d)  X = Voleur(%d)  -+| = Rues\n\n", police, voleur);
    
    for (int row = 0; row < 10; row++) {
        for (int col = 0; col < 10; col++) {
            int node = row * 10 + col;
            if (node == police) {
                printf("*  ");
            } else if (node == voleur) {
                printf("X  ");
            } else {
                // RUES comme tu veux exactement
                if (row % 2 == 0 && col % 3 == 0) printf("-  ");
                else if (col % 2 == 0 && row % 3 == 0) printf("|  ");
                else if (row % 3 == 1) printf("+  ");
                else printf("-  ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

// Carte chemin SIMPLE (comme avant)
void display_path_map(int start, int target, int* path, int path_len) {
    printf("--- CARTE CHEMIN OPTIMAL ---\n");
    printf("Légende: * = Police(%d)  X = Voleur(%d)  # = Chemin  . = Libre\n\n", start, target);
    
    for (int row = 0; row < 10; row++) {
        for (int col = 0; col < 10; col++) {
            int node = row * 10 + col;
            if (node == start) {
                printf("*  ");
            } else if (node == target) {
                printf("X  ");
            } else if (path_len > 0 && is_in_path(path, path_len, node)) {
                printf("#  ");
            } else {
                printf(".  ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    print_banner();
    
    printf("## 1. RECHERCHE DU CHEMIN LE PLUS COURT ##\n");
    Graph* g = create_big_city_graph();
    int start = 0;   
    int target = 69;
    int path[100];
    int path_len;
    
    double dist = dijkstra(g, start, target, path, &path_len);
    printf("Chemin optimal Police(%d) -> Voleur(%d): ", start, target);
    for (int i = 0; i < path_len; i++) printf("%d ", path[i]);
    printf("\nDistance totale: %.1f unites (vitesse+trafic)\n", dist);
    printf("%d intersections traversee\n", path_len);
    
    // LES 2 CARTES!
    display_city_structure(start, target);
    display_path_map(start, target, path, path_len);
    
    printf("\n[VOLEUR ZIGZAGUE vers 89] Recalcul...\n");
    target = 89;
    dist = dijkstra(g, start, target, path, &path_len);
    printf("Nouveau chemin (%d etapes): ", path_len);
    for (int i = 0; i < path_len; i++) printf("%d ", path[i]);
    printf("\nDistance: %.1f\n", dist);
    
    display_city_structure(start, target);
    display_path_map(start, target, path, path_len);
    
    free_graph(g);
    
    printf("\n## 2. SURVEILLANCE URBAINE ##\n");
    printf("Cameras minimales: intersections 5, 25, 50, 75\n");
    
    printf("\n## 3. LOGISTIQUE VEHICULES ##\n");
    Item items[] = {
        {"Bandes a pointes", 12, 85},
        {"Barriere portable", 20, 70},
        {"Drone tactique", 5, 90},
        {"Brouilleur", 10, 60},
        {"Trousse medicale", 3, 30},
        {"Gaz lacrymo", 8, 50},
        {"Treuil robuste", 15, 40},
        {"Scanner portable", 2, 25}
    };
    int n = 8, W = 40;
    int selected[8], sel_len;
    int max_value = knapsack_recursive(items, n, W, selected, &sel_len);
    printf("Charge max tactique: %d (poids <=40kg)\n", max_value);
    printf("Equipement: ");
    for (int i = 0; i < sel_len; i++) {
        printf("%s ", items[selected[i]].name);
    }
    printf("\n");
    
    printf("\nMISSION PRETE - INTERCEPTION IMMINENTE\n");
    return 0;
}
