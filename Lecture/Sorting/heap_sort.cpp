/**
 * Max Heap Implementation with support of insertion and
 * deletion operation in a sequential form with an array.
 *
 * It follows Max Heap property, means, parent is larger than of its child.
 *
 * 1. One dimensional array to represent a tree.
 * 2. The root is in the first location i.e. root = Tree[1], the location
 *    in array would be 0.
 * 3. The children are stored in (2 × k) and (2 × k + 1) locations.
 * 4. Max size of tree would be: 2^h, where h is the height of the tree.
 * 5. The empty tree or sub tree is given by -1.
 *
 * By Santa Basnet.
 * Everest Engineering College.
 * Date: 2021-12-05
 */

#include <cstdio>

/**
 * Constants for Maximum elements, 5 level depths.
 */
static const int MAX_TREE = 256;
static const int TRUE = 1;
static const int FALSE = 0;

/**
 * Heap Element.
 */
struct Element {
    int item;
};

/**
 * Define Heap Storage.
 */
struct HeapStorage {
    int tail, head;
    struct Element arrayTree[MAX_TREE + 1];
} maxHeap;


/**
 * Initialize Demo Data.
 */
const int MAX_DATA = 13;
const int data[MAX_DATA] = {
        20, 15, 35, 12, 17,
        21, 39, 16, 18, 36,
        45, 100, 6
};

/**
 * Perform print operation of the array with display message.
 */
void printData(int *array, int begin, int size, const char *message) {
    printf(message);
    for (int index = begin; index < size; index++)
        printf("| %3d ", array[index]);
    printf("|");
}

/**
 * Display Data.
 */
void displayData() {
    printData((int *) &data, 0, MAX_DATA, "\nInitial Data : \n");
}

/**
 * Display Heap Sorted Array.
 */
void displayTree() {
    printData((int *) &maxHeap.arrayTree, maxHeap.head, maxHeap.tail, "\n\nTree Data : \n");
}

/**
 * Initialize the items with 0 values.
 */
void initializeHeap() {
    maxHeap.tail = 1;
    maxHeap.head = 1;
}

/**
 * Build an item Element.
 */
struct Element itemElement(int item) {
    struct Element emptyElement;
    emptyElement.item = item;
    return emptyElement;
}

/**
 * Default Empty Element.
 */
struct Element anEmptyElement() {
    return itemElement(-1);
}

/**
 * Finds the position to insert an item to the tree.
 * Insert at last position and make max heap valid.
 *
 * The children are stored in (2 × k + 1) and (2 × k + 2) locations.
 * @param dataItem
 * @return position
 */
int findPosition() {
    return maxHeap.tail++;
}

/**
 * Perform Interchange Operation;
 */
void interChange(int from, int to) {
    struct Element tElement = maxHeap.arrayTree[from];
    maxHeap.arrayTree[from] = maxHeap.arrayTree[to];
    maxHeap.arrayTree[to] = tElement;
}

/**
 * Find the location where to go downward.
 */
int changeLocation(int left, int right) {
    return maxHeap.arrayTree[left].item > maxHeap.arrayTree[right].item ? left : right;
}

/**
 * Compare by value.
 */
int compareByValue(struct Element from, struct Element to) {
    return from.item < to.item;
}

/**
 * Make adjustment if it follows MaxHeap property or not after insertion.
 * @param position
 */
void upWardAdjustment(int position) {
    if (position == 1) return;
    for (int tPosition = position, parent = tPosition / 2; parent > 0; tPosition = parent, parent = tPosition / 2)
        if (compareByValue(maxHeap.arrayTree[parent], maxHeap.arrayTree[tPosition]))
            interChange(tPosition, parent);
}

/**
 * Make adjustment if it follows MaxHeap Property or not after deletion.
 */
void downWardAdjustment() {
    /** Improvement, we can set a break statement, if there is no change a head. **/
    for (int begin = maxHeap.head; begin < maxHeap.tail;) {
        int leftLocation = begin * 2, rightLocation = begin * 2 + 1;
        int maxChildLocation = changeLocation(leftLocation, rightLocation);
        if (maxHeap.arrayTree[begin].item < maxHeap.arrayTree[maxChildLocation].item)
            interChange(begin, maxChildLocation);
        begin = maxChildLocation;
    }
}

/**
 * Perform insertion operation.
 * @param dataItem
 */
void insertInTree(int dataItem) {
    int position = findPosition();
    maxHeap.arrayTree[position] = itemElement(dataItem);
    upWardAdjustment(position);
}

/**
 * Perform delete operation in the tree.
 * Delete always happens from the head position.
 */
struct Element deleteFromTree() {
    /** Check if heap is empty or not. **/
    if (maxHeap.head == maxHeap.tail && maxHeap.tail == 1) return anEmptyElement();

    /** Check if heap has single element only. **/
    if (maxHeap.tail == 2) return maxHeap.arrayTree[--maxHeap.tail];

    /** Delete item and make adjustments. */
    struct Element deletedItem = maxHeap.arrayTree[maxHeap.head];

    /* 1. Move last element to the head. */
    maxHeap.arrayTree[maxHeap.head] = maxHeap.arrayTree[--maxHeap.tail];

    /* 2. Make adjustment */
    downWardAdjustment();

    return deletedItem;
}

/**
 * Main Function.
 * @return 1 with successful output.
 */
int main() {
    /** Initialize and Display Data **/
    initializeHeap();
    displayData();

    /** Perform Insertion Operation **/
    for (int index = 0; index < MAX_DATA; index++)
        insertInTree(data[index]);
    displayTree();

    /** Perform Delete and Display */
    deleteFromTree();
    printf("\n\nDeleted 100, (the root element)");
    displayTree();
    printf("\n");
    return 1;
}