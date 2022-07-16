#include <malloc.h>

/**
 * Lab-Sheet - 7: Sorting Algorithms.
 * Merge Sort Implementation for Array of structure In C.
 *
 * Example: Data
 * -------------------------------------------------------
 *  begin                    mid                     end
 *  38       27      43      3       9       82      10
 *  -------------------------|----------------------------
 *  begin                   mid     mid+1           end
 *  38      27      43      3       9       82      10
 *  ------------ | ------------     ------------ | -------
 *  38      27      43      3       9       82      10
 *  -----|-----   -----|-----      ------|------  --------
 *  38      27      43      3       9       82      10
 * ------------ | ------------- ---------------- | -------
 *  27      38      3      43       9       82      10
 *  ------------ | ------------- ---------------- | ------
 *  3      27      38      43       9       10      82
 * ---------------------------- | ------------------------
 *  3       9       10      27      38      43      82
 * -------------------------------------------------------
 *
 * By: Santa Basnet
 * Everest Engineering College.
 * Date: 2021-12-10
 */

const int TRUE = 1;
const int FALSE = 0;
const int MAX_SIZE = 7;

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
 * Allocate memory for temporary sub elements.
 */
struct Element *createSubElements(int size) {
    struct Element *dataElements = (struct Element *) malloc(sizeof(struct Element) * size);
    return dataElements;
}

/**
 * Perform partition of the data elements by,
 * 1. smaller are placed in the left.
 * 2. bigger are place int he right.
 */
struct Element *mergeOperation(struct Element *elements, int begin, int midIndex, int end, SortingOrder sortingOrder) {
    int leftSize = midIndex - begin + 1;
    int rightSize = end - midIndex;

    /** Temporary Elements **/
    struct Element *leftElements = createSubElements(leftSize);
    struct Element *rightElements = createSubElements(rightSize);

    /* Copy Operation to the Left Elements. */
    for (int i = 0; i < leftSize; i++) (leftElements + i)->item = (elements + begin + i)->item;

    /* Copy Operation to the Right Elements. */
    for (int j = 0; j < rightSize; j++) (rightElements + j)->item = (elements + midIndex + 1 + j)->item;

    /**
     * Merge Operation of the temporary left and right elements.
     * Merging is done with item picking from the smallest one
     * from either left or right elements.
     *
     * If an item in the head pointer of left elements is smaller than that of
     * right elements, pick from left and continue that process for left and
     * right elements.
     *
     * When completed, copy the remaining elements from the left and the right elements.
     */
    int i = 0, j = 0, k = begin;
    for (; i < leftSize && j < rightSize;) {
        if (sortingOrder((leftElements + i)->item, (rightElements + j)->item))
            (elements + k++)->item = (leftElements + i++)->item;
        else (elements + k++)->item = (rightElements + j++)->item;
    }

    /** Copy the remaining elements of left elements **/
    for (; i < leftSize;) (elements + k++)->item = (leftElements + i++)->item;

    /** Copy the remaining elements of right elements **/
    for (; j < rightSize;) (elements + k++)->item = (rightElements + j++)->item;
    return elements;
}

/**
 * Perform Sort Operation using Selection Sort.
 */
static struct Element *mergeSortWith(struct Element *elements, int begin, int end, SortingOrder sortingOrder) {
    if (begin < end) {
        //printf("\n");
        //displayData(elements);
        int midIndex = begin + (end - begin) / 2;
        elements = mergeSortWith(elements, begin, midIndex, sortingOrder);
        elements = mergeSortWith(elements, midIndex + 1, end, sortingOrder);
        elements = mergeOperation(elements, begin, midIndex, end, sortingOrder);
    }
    return elements;
}

/**
 * Input Data.
 */
static struct Element *initializeData() {
    struct Element *dataElements = (struct Element *) malloc(sizeof(struct Element) * MAX_SIZE);
    (dataElements + 0)->item = 38;
    (dataElements + 1)->item = 27;
    (dataElements + 2)->item = 43;
    (dataElements + 3)->item = 3;
    (dataElements + 4)->item = 9;
    (dataElements + 5)->item = 82;
    (dataElements + 6)->item = 10;
    return dataElements;
}

/**
 * Main function for Bubble Sort.
 * @return 1 for successful exits.
 */
int main() {
    printf("\n------------------------------------------------------------------\n");
    printf("Merge Sort Implementation");
    printf("\n------------------------------------------------------------------\n");
    struct Element *data = initializeData();
    printf("\n1. Initial Unordered Data: \n");
    displayData(data);
    printf("\n");

    SortingOrder ascendingOrder = &ascending;
    struct Element *sortedData = mergeSortWith(data, 0, MAX_SIZE, ascendingOrder);
    printf("\n2. Ascending Ordered Data: \n");
    displayData(sortedData);

    printf("\n------------------------------------------------------------------\n");
    return 1;
}