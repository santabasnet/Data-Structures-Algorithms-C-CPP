#include <malloc.h>

/**
 * Bubble Sort Implementation for Array In C.
 * Perform sorting comparing the consecutive elements in the collection [Array].
 *
 * 1. Begin from 0 index, compare the first and the second elements.
 * 2. data[index] > data[index+1], perform swap operation.
 * 3. Process 'a' goes till the last element.
 *
 * By: Santa Basnet
 * Everest Engineering College.
 * Date: 2021-12-09
 */

const int TRUE = 1;
const int FALSE = 0;

/*
 * Data Representation.
 */
struct Element {
    int item;
};

/**
 * Ascending Order Compare.
 */
int ascending(int a, int b) {
    return a > b;
}

/**
 * Descending Order Compare.
 */
int descending(int a, int b) {
    return a < b;
}

/**
 * Function signature for sorting comparator.
 */
typedef int (*SortingOrder)(int, int);

/**
 * Input Data.
 */
const int MAX_SIZE = 10;

void displayData(struct Element *data){
    printf("\n");
    for (int i = 0; i < MAX_SIZE; i++) printf("\t%d", (data + i)->item);
}

/**
 * Perform Sort Operation using Bubble Sort.
 */
struct Element *bubbleSortWith(struct Element *elements, int size, SortingOrder sortingOrder) {
    for (int index = 0; index < size - 1; index++) {
        int flag = FALSE; // For Optimisation purpose only.
        for (int innerIndex = 0; innerIndex < size - index - 1; innerIndex++) {
            if (sortingOrder((elements + innerIndex)->item, (elements + innerIndex + 1)->item)) {
                struct Element *tempItem = (struct Element *) malloc(sizeof(Element));
                tempItem->item = (elements + innerIndex)->item;
                (elements + innerIndex)->item = (elements + innerIndex + 1)->item;
                (elements + innerIndex + 1)->item = tempItem->item;
                flag = TRUE;
                free(tempItem);
            }
        }
        if (!flag) break;
    }
    return elements;
}



struct Element *initializeData() {
    struct Element *dataElements = (struct Element *) malloc(sizeof(struct Element) * MAX_SIZE);
    (dataElements + 0)->item = 200;
    (dataElements + 1)->item = 100;
    (dataElements + 2)->item = 50;
    (dataElements + 3)->item = 80;
    (dataElements + 4)->item = 90;
    (dataElements + 5)->item = 10;
    (dataElements + 6)->item = 0;
    (dataElements + 7)->item = 70;
    (dataElements + 8)->item = 20;
    (dataElements + 9)->item = 30;
    return dataElements;
}


/**
 * Main function for Bubble Sort.
 * @return 1 for successful exits.
 */
int main() {
    printf("Bubble Sort Implementation");
    printf("\n-------------------------------------------------------------");

    struct Element *data = initializeData();
    printf("\n1. Initial Unordered Data: \n");
    for (int i = 0; i < MAX_SIZE; i++) printf("\t%d", (data + i)->item);

    SortingOrder ascendingOrder = &ascending;
    struct Element *sortedData = bubbleSortWith(data, MAX_SIZE, ascendingOrder);
    printf("\n2. Ascending Ordered Data: \n");
    for (int i = 0; i < MAX_SIZE; i++) printf("\t%d", (sortedData + i)->item);

    SortingOrder descendingOrder = &descending;
    struct Element *sortedData1 = bubbleSortWith(data, MAX_SIZE, descendingOrder);
    printf("\n3. Descending Ordered Data: \n");
    for (int i = 0; i < MAX_SIZE; i++) printf("\t%d", (sortedData1 + i)->item);

    printf("\n-------------------------------------------------------------\n");
    return 1;
}