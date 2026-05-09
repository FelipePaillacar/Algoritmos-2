#include "quick_sort.h"
#include "utils.h"

int partition(Deportista arr[], int low, int high) {

    float pivot = arr[high].puntaje;

    int i = low - 1;

    for (int j = low; j < high; j++) {

        if (arr[j].puntaje < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);

    return i + 1;
}

void quickSort(Deportista arr[], int low, int high) {

    if (low < high) {

        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}