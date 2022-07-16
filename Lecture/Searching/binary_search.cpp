#include <cstdio>

/**
 * Binary Search implementation.
 * Initial assumption is the collection to be searched should
 * follow the sorting order, either in ascending or in descending
 * order.
 *
 * By: Santa Basnet
 * Everest Engineering College.
 *
 * Date: 2021-12-14
 */
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
int search(struct Collection data, int leftPosition, int rightPosition, int dataItem) {
    if (leftPosition > rightPosition) return NOT_FOUND;
    int midPosition = leftPosition + (rightPosition - leftPosition) / 2;
    if (data.items[midPosition] == dataItem) {
        return midPosition;
    } else if (data.items[midPosition] > dataItem)
        return search(data, leftPosition, midPosition - 1, dataItem);
    else return search(data, midPosition + 1, rightPosition, dataItem);

}

/**
 * Binary search without recursion.
 * @param data , collection of data items.
 * @param left , left part of the value index.
 * @param right , right part of the value index.
 * @param dataItem , an item to be searched.
 * @return foundIndex, index of the data position if found, -1 in else case.
 */
int searchWithOutRecursion(struct Collection data, int leftPosition, int rightPosition, int dataItem) {
    int foundIndex = -1;
    while (leftPosition < rightPosition) {
        int midPosition = (rightPosition + leftPosition) / 2;
        if (data.items[midPosition] > dataItem) rightPosition = midPosition;
        else if (data.items[midPosition] == dataItem) {
            foundIndex = midPosition;
            break;
        } else leftPosition = midPosition + 1;
    }
    return foundIndex;
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

    int result = searchWithOutRecursion(dataCollection, 0, 10, dataItem);
    if (result >= 0) printf("Fount at : %d\n", result);
    else printf("Data not found.");

    return 1;
}