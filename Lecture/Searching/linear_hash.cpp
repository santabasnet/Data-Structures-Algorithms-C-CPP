/**
 * Hashing_Linear_Probing and Search Implementation.
 * Starts looking up data elements from 0th index to the specified maximum
 * size.
 *
 * For Hash Constant
 * https://github.com/h2database/h2database/blob/master/h2/src/test/org/h2/test/store/CalculateHashConstant.java
 *
 * Knuth Multiplicative method
 * hash(i)=i*2654435761 mod 2^32
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
 * Hash function implementation.
 */
unsigned int hashFunction(unsigned int dataItem) {
    dataItem = ((dataItem >> 16) ^ dataItem) * 0x45d9f3b;
    dataItem = ((dataItem >> 16) ^ dataItem) * 0x45d9f3b;
    dataItem = (dataItem >> 16) ^ dataItem;
    return dataItem;
}

unsigned int unHashFunction(unsigned int dataItem) {
    dataItem = ((dataItem >> 16) ^ dataItem) * 0x119de1f3;
    dataItem = ((dataItem >> 16) ^ dataItem) * 0x119de1f3;
    dataItem = (dataItem >> 16) ^ dataItem;
    return dataItem;
}

/**
 * Perform search operation: recursively.
 * @param data , collection of data items.
 * @param left , left part of the value index.
 * @param right , right part of the value index.
 * @param dataItem , an item to be searched.
 * @return foundIndex, index of the data position if found, -1 in else case.
 */
int search(struct Collection data, int dataItem) {

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

    int result = search(dataCollection, dataItem);
    if (result >= 0) printf("Fount at : %d\n", result);
    else printf("Data not found.");

    unsigned int hash = hashFunction(100);
    printf("\n%d", hashFunction(100));
    printf("\n%d", unHashFunction(hashFunction(100)));

    return 1;
}