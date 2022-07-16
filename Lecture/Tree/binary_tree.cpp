/**
 * Binary Tree Implementation with support of insertion and
 * deletion operation in a sequential form.
 * 1. One dimensional array to represent a tree.
 * 2. The root is in the first location i.e. root = Tree[1], the location
 *    in array would be 0.
 * 3. The children are stored in (2 × k + 1) and (2 × k + 2) locations.
 * 4. Max size of tree would be: 2^h+1, where h is the height of the tree.
 * 5. The empty tree or sub tree is given by NULL.
 *
 * By Santa Basnet.
 * Everest Engineering College.
 * Date: 2021-12-05
 */

#include <cstdio>

/**
 * Constants for Maximum elements, 5 level depths.
 */
const int MAX_TREE = 32;
int arrayTree[MAX_TREE];

/**
 * Demo Data.
 */
const int MAX_DATA = 13;
const int data[MAX_DATA] = {20, 15, 35, 12, 17, 21, 39, 16, 18, 36, 45, 100, 6};
//const int data[MAX_DATA] = {20, 40, 60, 1, 68};

/**
 * Function prototypes.
 */
void initialize();

void insertInTree(int);

void displayTree();

/**
 * Main Function.
 * @return 1 with successful output.
 */
int main() {
    initialize();
    for (int index = 0; index < MAX_DATA; index++) {
        insertInTree(data[index]);
    }
    displayTree();
    return 1;
}

/**
 * Initialize the items with 0 values.
 */
void initialize() {
    for (int index = 0; index < MAX_TREE; index++) {
        arrayTree[index] = NULL;
    }
}

/**
 * Finds the position to insert an item to the tree.
 * The children are stored in (2 × k + 1) and (2 × k + 2) locations.
 * @param dataItem
 * @return position
 */
int findPosition(int dataItem) {
    if (arrayTree[0] == NULL) return 0;
    else {
        int index = 0;
        int value = arrayTree[index];
        while (value != NULL) {
            if (dataItem < value) index = index + 1;
            else index = index + 2;
            value = arrayTree[index];
        }
        return index;
    }
}

/**
 * Perform insertion operation.
 * @param dataItem
 */
void insertInTree(int dataItem) {
    int position = findPosition(dataItem);
    arrayTree[position] = dataItem;
}

/**
 * Prints the items inserted in the tree.
 */
void displayTree() {
    for (int index = 0; index < MAX_TREE; index++)
        printf("| %d ", arrayTree[index]);
    printf("|");
}