#include <malloc.h>

/**
 * Insertion Sort Implementation for Array of structure In C.
 *
 * 1. Begin from 0 index, the first element is sorted as a key and start from index 1.
 * 2. Take next element as unsorted one and make its suitable placement compared
 *    with the first one.
 * 3. Process '2' goes till the last element.
 *
 * Insertion Sort Trace-out Example:
 *
 * Input Data:
 *
 *  200	100	50	80	90	10	0	70	20	30
 *
 * Iter 1 >>		100	200	50	80	90	10	0	70	20	30
 * Iter 2 >>		50	100	200	80	90	10	0	70	20	30
 * Iter 3 >>		50	80	100	200	90	10	0	70	20	30
 * Iter 4 >>		50	80	90	100	200	10	0	70	20	30
 * Iter 5 >>		10	50	80	90	100	200	0	70	20	30
 * Iter 6 >>		0	10	50	80	90	100	200	70	20	30
 * Iter 7 >>		0	10	50	70	80	90	100	200	20	30
 * Iter 8 >>		0	10	20	50	70	80	90	100	200	30
 * Iter 9 >>		0	10	20	30	50	70	80	90	100	200
 *
 * Time Complexity:
 *  1. Base Case: O(n)
 *  2. Average Case: O(n^2)
 *  3. Worst Case: O(n^2)
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
    for (int i = 0; i < MAX_SIZE; i++)
        printf("\t%d", (elements + i)->item);
}

/**
 * Build an Element.
 */
struct Element *buildElement(struct Element *itemElement) {
    struct Element *element = (struct Element *) malloc(sizeof(Element));
    element->item = itemElement->item;
    return element;
}

/**
 * Perform Sort Operation using Selection Sort.
 *
 */
static struct Element *insertionSortWith(struct Element *elements, int size, SortingOrder sortingOrder) {
    int leftBound = -1;
    for (int index = 1; index < size; index++) {
        struct Element *keyItem = buildElement(elements + index);
        int shifter = index - 1;
        /* Perform shift operation till the beginning.*/
        while (sortingOrder((elements + shifter)->item, keyItem->item) && shifter > leftBound) {
            (elements + shifter + 1)->item = (elements + shifter)->item;
            shifter--;
        }
        (elements + shifter + 1)->item = keyItem->item;
        //printf("\n* Iter %d >>\t", index);
        displayData(elements);
        free(keyItem);
    }
    return elements;
}

/**
 * Input Data.
 */
static struct Element *initializeData() {
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
    printf("Insertion Sort Implementation");
    printf("\n------------------------------------------------------------------");
    struct Element *data = initializeData();
    printf("\n1. Initial Unordered Data: \n");
    displayData(data);

    SortingOrder ascendingOrder = &ascending;
    struct Element *sortedData = insertionSortWith(data, MAX_SIZE, ascendingOrder);
    printf("\n2. Ascending Ordered Data: \n");
    displayData(sortedData);

    SortingOrder descendingOrder = &descending;
    struct Element *sortedData1 = insertionSortWith(data, MAX_SIZE, descendingOrder);
    printf("\n3. Descending Ordered Data: \n");
    displayData(sortedData1);

    printf("\n------------------------------------------------------------------\n");

    return 1;
}