#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 10

struct Local {
    int room_id, host_id, reviews, accommodates;
    char room_type[20], coutry[20], city[20], neighborhood[20], property_type[20];
    float overall_satisfaction, bedrooms, price;
};

//http://www.programasprontos.com/algoritmos-de-ordenacao/algortimo-quick-sort/
void quick_sort(struct Local *a, int left, int right) {
    int i, j, x;
    struct Local y;
    i = left;
    j = right;
    x = a[(left + right) / 2].room_id;

    while(i <= j) {
        while(a[i].room_id < x && i < right) {
            i++;
        }
        while(a[j].room_id > x && j > left) {
            j--;
        }
        if(i <= j) {
            y = a[i];
            a[i] = a[j];
            a[j] = y;
            i++;
            j--;
        }
    }

    if(j > left) {
        quick_sort(a, left, j);
    }
    if(i < right) {
        quick_sort(a, i, right);
    }
}
