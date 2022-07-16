/**
 * Sequential Search Implementation.
 * Starts looking up data elements from 0th index to the specified maximum
 * size.
 *
 * By: Santa Basnet
 * Everest Engineering College.
 *
 * Date: 2021-12-14
 */

#include <cstdio>

const int NOT_FOUND = -1;

const int MAX_SIZE = 100;

struct Collection {
    int items[MAX_SIZE];
};

/**
 * Perform search operation: recursively.
 * @param data , collection of data items.
 * @param left , left part of the value index.
 * @param right , right part of the value index.
 * @param dataItem , an item to be searched.
 * @return foundIndex, index of the data position if found, -1 in else case.
 */
int search(struct Collection data, int maxSize, int dataItem) {
    for (int index = 0; index < maxSize; index++) {
        if (data.items[index] == dataItem) return index;
    }
    return NOT_FOUND;
}

/**
 * Initialize Collection.
 */
struct Collection initializeCollection() {
    struct Collection collection = {
            {10, 15, 25, 65, 70, 99, 101, 105, 116, 900}
    };
    return collection;
}


/**
 * Main function starts here.
 * @return 1 for successful operation.
 */
int main() {
    struct Collection dataCollection = initializeCollection();
    int dataItem = 105;

    int result = search(dataCollection, 10, dataItem);
    if (result >= 0) printf("Fount at : %d\n", result);
    else printf("Data not found.");

    return 1;
}