#include <stdio.h>

#include "deportista.h"
#include "merge_sort.h"
#include "quick_sort.h"

int main() {

    Deportista deportistas[] = {
        {1, "Ana", 80.5},
        {2, "Luis", 92.0},
        {3, "Carlos", 70.3},
        {4, "Maria", 88.1}
    };

    int n = sizeof(deportistas) / sizeof(deportistas[0]);

    printf("=== ORIGINAL ===\n");
    imprimirDeportistas(deportistas, n);

    mergeSort(deportistas, 0, n - 1);

    printf("\n=== ORDENADO MERGE SORT ===\n");
    imprimirDeportistas(deportistas, n);

    return 0;
}