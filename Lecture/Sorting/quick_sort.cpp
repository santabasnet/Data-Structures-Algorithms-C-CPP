#include <malloc.h>

/**
 * Quick Sort Implementation for Array of structure In C.
 *
 * Two steps involved.
 * a. Partition
 *  >> is done with pivot element.
 *
 *  >> generally selected either beginning or end located item.
 *
 *  >> try to bring all the smaller elements left to pivot element
 *     and larger elements right to the pivot element.
 *     This is all about finding the proper position of pivot element.
 *
 * b. Sort
 *
 * Partition Example
 * ----------------------------------
 *
 * Iteration Steps
 * ----------------
 * i and j becomes 0 and pivot element is 7.
 *  [9, 6, 5, 0, 8, 2, 4, 7]
 * 0. increment j.
 * a. 9 is not less than that of 7, no operation.
 *
 * b. 6 < 7, so, exchange 9 and 7, increment i.
 *  [6, 9, 5, 0, 8, 2, 4, 7]
 *
 * c. 5 < 7, so, exchange 9 and 5. increment i.
 *  [6, 5, 9, 0, 8, 2, 4, 7]
 *
 * d. 0 < 7, so, exchange 0 and 9. increment i.
 *  [6, 5, 0, 9, 8, 2, 4, 7]
 *
 * e. 8 > 7, so, no operation.
 *
 * f. 2 < 7, so, exchange 9 and 2. increment i.
 *  [6, 5, 0, 2, 8, 9, 4, 7]
 *
 * g. 4 < 7, so, exchange 8 and 4. increment i.
 *  [6, 5, 0, 2, 4, 9, 8, 7]
 *
 *  h. finally, exchange i+1 indexed item with pivot element.
 *  [6, 5, 0, 2, 4, (7), 8, 9]
 *
 *  Now 7 has its position.
 *  And apply partition operation begin to i and ((i+1)+1) to end.
 *  Computation of partition is from 0 to n - 1, so O(n).
 *
 *  Quick Sort
 *  ---------------
 *  0. Initialize begin to 0 and end to length of the list.
 *  1. find partition index.
 *  2. quick sort from begin to partition index.
 *  3. quick sort from partition index + 1 to end.
 *
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
    return a <= b;
}

/**
 * Descending Order Compare.
 */
static int descending(int a, int b) {
    return a >= b;
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
    for (int i = 0; i < MAX_SIZE; i++)
        printf("\t%d", (elements + i)->item);
}

/**
 * Build an Element.
 */
struct Element *buildElement(struct Element *dataItem) {
    struct Element *element = (struct Element *) malloc(sizeof(Element));
    element->item = dataItem->item;
    return element;
}

/**
 * Function to inter change the position of two elements.
 */
static void interChange(Element *source, Element *destination) {
    int tempItem = source->item;
    source->item = destination->item;
    destination->item = tempItem;
}

/**
 * Display Pivot item.
 */
void displayPivotElement(struct Element *elements, int index) {
    printf("\n-----------------------------------------------------");
    printf("\nPivot Key: %d", (elements + index)->item);
    printf("\n----------------------------------------------------");
}

/**
 * Perform partition of the data elements by,
 * 0. Select a pivot element first, try to re-arrange items in,
 * 1. smaller are placed in the left.
 * 2. bigger are place int he right.
 * 3. When pivot is created, we can partition the problem in two parts
 *    like left sub-problem and right-sub problem.
 */
int partition(struct Element *elements, int down, int up, SortingOrder sortingOrder) {
    struct Element *pivotKey = buildElement(elements + down);
    displayPivotElement(elements, down);

    int lowerIndex = down;
    int upperIndex = up;
    while (lowerIndex < upperIndex) {
        /* Find bigger number than the pivotal number */
        do {
            lowerIndex++;
        } while (sortingOrder((elements + lowerIndex)->item, pivotKey->item));
        /* Find smaller number than the pivotal number */
        do {
            upperIndex--;
        } while (!sortingOrder((elements + upperIndex)->item, pivotKey->item));

        if (lowerIndex < upperIndex)
            interChange((elements + lowerIndex), (elements + upperIndex));
    }
    interChange((elements + down), (elements + upperIndex));
    return upperIndex;
}

/**
 * Perform Sort Operation using Selection Sort.
 * We do not need the auxiliary memory arrays as we saw in the Merge sort.
 */
static struct Element *quickSortWith(struct Element *elements, int begin, int end, SortingOrder sortingOrder) {
    if (begin < end) {
        displayData(elements);

        int partitionIndex = partition(elements, begin, end, sortingOrder);
        quickSortWith(elements, begin, partitionIndex, sortingOrder);
        quickSortWith(elements, partitionIndex + 1, end, sortingOrder);
    }
    return elements;
}

/**
 * Input Data.
 */
static struct Element *initializeData() {
    struct Element *dataElements = (struct Element *) malloc(sizeof(struct Element) * MAX_SIZE);
    (dataElements + 0)->item = 24;
    (dataElements + 1)->item = 11;
    (dataElements + 2)->item = 49;
    (dataElements + 3)->item = 20;
    (dataElements + 4)->item = 84;
    (dataElements + 5)->item = 75;
    (dataElements + 6)->item = 19;
    (dataElements + 7)->item = 56;
    (dataElements + 8)->item = 99;
    (dataElements + 9)->item = 45;
    return dataElements;
}

/**
 * Main function for Bubble Sort.
 * @return 1 for successful exits.
 */
int main() {
    printf("Insertion Sort Implementation");
    printf("\n---------------------------------------------------------");
    struct Element *data = initializeData();
    printf("\n1. Initial Unordered Data: \n");

    SortingOrder ascendingOrder = &ascending;
    struct Element *sortedData = quickSortWith(data, 0, MAX_SIZE, ascendingOrder);
    printf("\n2. Ascending Ordered Data:");
    displayData(sortedData);

    printf("\n--------------------------------------------------------\n");
    return 1;
}