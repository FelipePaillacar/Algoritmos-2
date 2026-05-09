#include "utils.h"

void swap(Deportista *a, Deportista *b) {
    Deportista temp = *a;
    *a = *b;
    *b = temp;
}