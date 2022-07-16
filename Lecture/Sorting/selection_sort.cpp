#include <malloc.h>

/**
 * Selection Sort Implementation for Array of structure In C.
 * Perform sorting comparing the consecutive elements in the collection [Array].
 *
 * 1. Begin from 0 index, compare the first with the rest elements.
 * 2. Select minimum index of element and perform interchange operation.
 * 3. Process '2' goes till the last element.
 *
 * By: Santa Basnet
 * Everest Engineering College.
 * Date: 2021-12-10
 */

const int TRUE = 1;
const int FALSE = 0;
const int MAX_SIZE = 10;

/*
 * Data Representation.
 */
struct Element {
    int item;
};

/**
 * Ascending Order Compare.
 */
static int ascending(int a, int b) {
    return a > b;
}

/**
 * Descending Order Compare.
 */
static int descending(int a, int b) {
    return a < b;
}

/**
 * Function signature for sorting comparator.
 */
typedef int (*SortingOrder)(int, int);

/**
 * Display Items.
 */
void displayData(Element *elements) {
    printf("\n");
    for (int i = 0; i < MAX_SIZE; i++) printf("\t%d", (elements + i)->item);
}

/**
 * Function to inter change the position of two elements.
 */
static void interChange(Element *source, Element *destination) {
    int placeValue = source->item;
    source->item = destination->item;
    destination->item = placeValue;
}

/**
 * Perform Sort Operation using Selection Sort.
 *
 */
static struct Element *selectionSortWith(struct Element *elements, int size, SortingOrder sortingOrder) {
    for (int index = 0; index < size - 1; index++) {
        int minIndex = index;
        for (int lookUp = index + 1; lookUp < size; lookUp++) {
            if (sortingOrder((elements + minIndex)->item, (elements + lookUp)->item)) {
                minIndex = lookUp;
            }
        }
        interChange((elements + minIndex), (elements + index));
    }
    return elements;
}


/**
 * Input Data.
 */
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
    printf("Selection Sort Implementation");
    printf("\n------------------------------------------------------------------");
    struct Element *data = initializeData();
    printf("\n1. Initial Unordered Data: \n");
    displayData(data);

    SortingOrder ascendingOrder = &ascending;
    struct Element *sortedData = selectionSortWith(data, MAX_SIZE, ascendingOrder);
    printf("\n2. Ascending Ordered Data: \n");
    displayData(sortedData);

    SortingOrder descendingOrder = &descending;
    struct Element *sortedData1 = selectionSortWith(data, MAX_SIZE, descendingOrder);
    printf("\n3. Descending Ordered Data: \n");
    displayData(sortedData1);

    printf("\n------------------------------------------------------------------\n");
    return 1;
}