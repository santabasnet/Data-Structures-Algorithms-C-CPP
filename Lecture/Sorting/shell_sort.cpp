#include <malloc.h>

/**
 * Shell Sort Implementation for Array of structure In C.
 * Perform sorting comparing the elements with the defined
 * period in the collection [Array].
 *
 * It is generalized version of Selection sort. In spite of comparing
 * with all the successive elements, it compares with the given
 * interval.
 *
 * Period, initially assign to n/2 and goes by 1/2 in every iteration
 * till period becomes 1.
 *
 * 1. Begin from 0 index, compare the first with the rest elements through
 *    constant period.
 * 2. Select minimum index of element and perform interchange operation.
 * 3. Process '2' goes till the last element.
 *
 * Example:
 * n = 6
 * list = [8, 9, 2, 4, 5, 6]
 *
 * Iteration 1
 * -------------
 * period = n/2 = 3
 * so, perform exchange on:
 * list[0] with period indices,
 *  i.e. list[0] <> list[3], list[1] <> list[4] and list[2] <> list[5]
 *
 * Iteration 2
 * -----------
 * period = 3/2 = 1
 * So, selection on:
 * 0th index, to 1, 2, 3, 4, 5.
 * 1st index, to 2, 3, 4, 5.
 * 2nd index, to 3, 4, 5.
 * 3rd index, to 4, 5.
 * 4th index, to 5.
 *
 * One more example with the current program example:
 *
 * Input Data >>
 * 200	100	50	80	90	10	0	70	20	30
 *
 * Interval size: 5 >>
	10	100	50	80	90	200	0	70	20	30
	10	0	50	80	90	200	100	70	20	30
	10	0	50	80	90	200	100	70	20	30
	10	0	50	20	90	200	100	70	80	30
	10	0	50	20	30	200	100	70	80	90
 *
 * Interval size: 2 >>
	10	0	50	20	30	200	100	70	80	90
	10	0	50	20	30	200	100	70	80	90
	10	0	30	20	50	200	100	70	80	90
	10	0	30	20	50	200	100	70	80	90
	10	0	30	20	50	200	100	70	80	90
	10	0	30	20	50	70	100	200	80	90
	10	0	30	20	50	70	80	200	100	90
	10	0	30	20	50	70	80	90	100	200
 *
 * Interval size: 1 >>
	0	10	30	20	50	70	80	90	100	200
	0	10	30	20	50	70	80	90	100	200
	0	10	20	30	50	70	80	90	100	200
	0	10	20	30	50	70	80	90	100	200
	0	10	20	30	50	70	80	90	100	200
	0	10	20	30	50	70	80	90	100	200
	0	10	20	30	50	70	80	90	100	200
	0	10	20	30	50	70	80	90	100	200
	0	10	20	30	50	70	80	90	100	200
 *
 * Stop.
 *
 * Time Complexity:
 *  1. Base Case: O(n log(n))
 *  2. Average Case: O(n log(n))
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
 * Build an Element.
 */
struct Element *buildElement(struct Element *dataItem) {
    struct Element *element = (struct Element *) malloc(sizeof(Element));
    element->item = dataItem->item;
    return element;
}

/**
 * Perform Sort Operation using Shell Sort.
 *
 */
static struct Element *shellSortWith(struct Element *elements, int size, SortingOrder sortingOrder) {
    /** Select an interval to make interchange the elements, first consider size/3 **/
    for (int interval = size / 2; interval > 0; interval /= 2) {
        for (int index = interval; index < size; index++) {
            struct Element *tempElement = buildElement(elements + index);
            int counter;
            for (counter = index; counter >= interval && sortingOrder((elements + counter - interval)->item,
                                                                      tempElement->item); counter -= interval)
                interChange((elements + counter), (elements + counter - interval));
            interChange((elements + counter), tempElement);
            free(tempElement);
        }


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
    printf("Shell Sort Algorithm Implementation");
    printf("\n------------------------------------------------------------------");
    struct Element *data = initializeData();
    printf("\n1. Initial Unordered Data: \n");
    displayData(data);

    SortingOrder ascendingOrder = &ascending;
    struct Element *sortedData = shellSortWith(data, MAX_SIZE, ascendingOrder);
    printf("\n2. Ascending Ordered Data: \n");
    displayData(sortedData);

    SortingOrder descendingOrder = &descending;
    struct Element *sortedData1 = shellSortWith(data, MAX_SIZE, descendingOrder);
    printf("\n3. Descending Ordered Data: \n");
    displayData(sortedData1);

    printf("\n------------------------------------------------------------------\n");
    return 1;
}