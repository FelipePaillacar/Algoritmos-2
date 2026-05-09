#include <stdio.h>
#include <stdlib.h>

#include "deportista.h"
#include "merge_sort.h"
#include "quick_sort.h"
#include "datos.h"

int main() {

    int n = 20;

    Deportista* deportistas =
        malloc(n * sizeof(Deportista));

    if (deportistas == NULL) {
        printf("Error de memoria.\n");
        return 1;
    }

    generar_deportistas(deportistas, n);

    printf("=== ORIGINAL ===\n");
    imprimirDeportistas(deportistas, n);

    mergeSort(deportistas, 0, n - 1);

    printf("\n=== ORDENADO MERGE SORT ===\n");
    imprimirDeportistas(deportistas, n);

    guardar_csv(
        deportistas,
        n,
        "db/deportistas.csv"
    );

    free(deportistas);

    return 0;
}