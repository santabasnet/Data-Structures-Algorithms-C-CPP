/**
 * ArrayList simulation example.
 *
 * By: Santa Basnet
 * Everest Engineering College.
 * Date: 2021-11-28
 */

#include <malloc.h>
#include <cstdlib>

#define TRUE 1

/**
 * Item Representation.
 */
const int MAX_SIZE = 100;
struct List {
    int *dataItems;
    int index;
};

/**
 * Perform a read operation of an integer data value from console.
 * @return dataValue
 */
int readValue(const char *message) {
    int dataValue;
    fprintf(stdout, "%s", message);
    scanf("%d", &dataValue);
    return (dataValue);
}

/**
 * Get an input value from the console.
 * @return inputValue
 */
int readItem() {
    return readValue("\nEnter a data value: ");
}

/**
 * Get input a position value from console.
 * @return positionIndex
 */
int readPosition() {
    return readValue("\nPosition at: ");
}

/**
 * Read choice value.
 */
int readChoice() {
    readValue("\nChoice : ");
}

/**
 * Allocate memory for data items and set index zero at the initial
 * stage.
 * (We can do it through array as well, Just to realize dynamic array
 * and passing pointer for data operations.)
 * @param items
 */
void initialise(struct List *items) {
    items->index = -1;
    items->dataItems = (int *) malloc(sizeof(int) * MAX_SIZE);
}

/**
 * Insert a data item in the List.
 * @param items, a list pointer.
 * @param dataItem, a value to insert in the List.
 */
void insertDataItem(struct List *items) {
    int dataItem = readItem();
    if (items->index == MAX_SIZE - 1) {
        printf("\nList becomes full. No places to insert the data item %d.", dataItem);
    } else {
        items->index++;
        *(items->dataItems + items->index) = dataItem;
        printf("%d is appended successfully.", dataItem);
    }
}

/**
 * Delete a data item from the last index of the point.
 * @param items
 */
void deleteLastItem(struct List *items) {
    if (items->index < 0) printf("\nThe List is Empty.");
    else {
        int value = *(items->dataItems + items->index);
        printf("%d data is deleted.", value);
        items->index--;
    }
}

/**
 * Insert item in Nth position.
 * @param items
 */
void insertNthItem(struct List *items) {
    int position = readPosition();
    if (items->index >= MAX_SIZE) printf("\nCannot Insort! List is full now.");
    else if (position > items->index + 1 || position < 0) printf("\nOut of bound Insertion!");
    else {
        items->index++;
        for (int index = items->index; index >= position; index--)
            *(items->dataItems + index) = *(items->dataItems + index - 1);
        int dataItem = readItem();
        *(items->dataItems + position) = dataItem;
        printf("%d data is inserted.", dataItem);
    }

}

/**
 * Delete a data item the the nth position of the items list.
 * @param items
 */
void deleteNthItem(struct List *items) {
    int deletionIndex = readPosition();
    if (deletionIndex < 0 || deletionIndex > items->index) printf("Out of bound position.");
    else {
        int dataItem = *(items->dataItems + deletionIndex);
        for (int index = deletionIndex; index <= items->index; index++)
            *(items->dataItems + index) = *(items->dataItems + index + 1);
        items->index--;
        printf("%d item is deleted.", dataItem);
    }
}

/**
 * Stop the program.
 */
void stopProgram(struct List *items) {
    printf("\nGood Bye !");
    exit(0);
}

/**
 * Error Choice.
 */
void errorChoice(struct List *items) {
    printf("\nError Choice! Try again.");
}

/**
 * Display data items.
 */
void displayItems(struct List *items) {
    printf("No of data available: %d", items->index + 1);
    printf("\nAvailable Data: [");
    int index;
    for (index = 0; index <= items->index - 1; index++)
        printf("\t%d, ", *(items->dataItems + index));
    if (index <= items->index)
        printf("\t%d\t", *(items->dataItems + index));
    printf("]");
}

/**
 * Display choice menu and read its index.
 * @return indexValue
 */
int printMenu() {
    int index;
    printf("\n\n----------------------------");
    printf("\nMenu Options");
    printf("\n----------------------------");
    printf("\n1. Append Node");
    printf("\n2. Delete Last Node");
    printf("\n3. Insert in Nth position");
    printf("\n4. Delete Nth Node");
    printf("\n5. Display List Items");
    printf("\n6. Exit");
    printf("\n----------------------------");
    return readChoice();
}

/**
 * Main function implementation.
 */
int main() {
    struct List itemsList;
    initialise(&itemsList);
    int index = 6;

    /**
     * Assign all the function pointers.
     */
    void (*operations[7])(struct List *) = {
            &insertDataItem, &deleteLastItem, &insertNthItem, &deleteNthItem, &displayItems, &stopProgram, &errorChoice
    };
    while (TRUE) {
        index = printMenu();
        index = index > 7 || index < 1 ? 7 : index;
        operations[index - 1](&itemsList);
    }
    return 1;
}