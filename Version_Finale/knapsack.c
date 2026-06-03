#include "knapsack.h"
#include <string.h>

int knapsack_recursive(Item* items, int n, int W, int* selected, int* sel_len) {
    int total_weight = 0, total_value = 0;
    *sel_len = 0;
    
    // Tri par ratio valeur/poids (algo glouton sûr)
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            double r1 = (double)items[i].value / items[i].weight;
            double r2 = (double)items[j].value / items[j].weight;
            if (r1 < r2) {
                Item tmp = items[i];
                items[i] = items[j];
                items[j] = tmp;
            }
        }
    }
    
    // Sélection gloutonne
    for (int i = 0; i < n && total_weight < W; i++) {
        if (total_weight + items[i].weight <= W) {
            selected[(*sel_len)++] = i;
            total_weight += items[i].weight;
            total_value += items[i].value;
        }
    }
    return total_value;
}
