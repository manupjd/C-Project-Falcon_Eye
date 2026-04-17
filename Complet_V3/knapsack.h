// knapsack.h
#ifndef KNAPSACK_H
#define KNAPSACK_H

typedef struct {
    char name[50];
    int weight;
    int value;
} Item;

int knapsack_recursive(Item* items, int n, int W, int* selected, int* sel_len);

#endif
