/**
 * Doubly Linked List Simulation.
 *
 * By Santa Basnet.
 * Everest Engineering College.
 */

#include <malloc.h>
#include <cstdlib>

#define TRUE 1

struct Node {
    int data;
    struct Node *previous;
    struct Node *next;
};

/**
 * Function prototypes.
 */
int displayMenu();

int readValue(const char *);

int readChoice();

int readDataValue();

int readPosition();

struct Node *createNode();

int count(struct Node *);

int isLastNode(int, int);

struct Node *appendData(struct Node *);

struct Node *insertNode(struct Node *);

struct Node *deleteNode(struct Node *);

struct Node *createFirstNode(struct Node *);

struct Node *deleteLastNode(struct Node *);

struct Node *displayItems(struct Node *);

struct Node *displayCount(struct Node *);

struct Node *stopProgram(struct Node *);

/**
 * Main Function Starts here.
 * @return 1 with successful exit.
 */
int main() {
    struct Node *start = nullptr;

    while (TRUE) {
        int choice = displayMenu();
        switch (choice) {
            case 1:
                start = appendData(start);
                break;
            case 2:
                start = insertNode(start);
                break;
            case 3:
                start = deleteNode(start);
                break;
            case 4:
                start = deleteLastNode(start);
                break;
            case 5:
                start = displayCount(start);
                break;
            case 6:
                start = displayItems(start);
                break;
            case 7:
                start = stopProgram(start);
                break;
        }
    }

    return 1;
}

/**
* Display Menu Options.
*/
int displayMenu() {
    printf("\n\n***DOUBLY LINKED LIST OPERATIONS***");
    printf("\n1. Append Node");
    printf("\n2. Insert at Nth Node");
    printf("\n3. Delete from Nth Node");
    printf("\n4. Delete From Last Node");
    printf("\n5. Count Nodes");
    printf("\n6. Display All Item Nodes");
    printf("\n7. Exit");
    printf("\n--------------------------------------");
    return readChoice();
}

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
* Read choice value.
*/
int readChoice() {
    return readValue("\n\tChoice: ");
}

/**
 * Read a data value from console.
 */
int readDataValue() {
    return readValue("\nEnter Data: ");
}

/**
 * Read a position value to insert/delete from.
 * @return positionValue
 */
int readPosition() {
    return readValue("\nEnter Nth Position: ");
}

/**
 * Validates if the given position data falls under the data range or not.
 * @param position
 * @param items
 * @return 1 for valid position.
 */
int isValidPosition(int position, int items) {
    return position > items || position < 0;
}

/**
 * Checks if the position is in the last node.
 * @param position
 * @param items
 * @return TRUE for the position in the last position.
 */
int isLastNode(int position, int items) {
    return position == items - 1;
}

/**
 * Create a new node and return its pointer.
 * @return newNodePointer
 */
struct Node *createNode() {
    struct Node *newNode;
    newNode = (struct Node *) malloc(sizeof(struct Node));
    newNode->previous = nullptr;
    newNode->data = readDataValue();
    newNode->next = nullptr;
}

/**
 * Create first node of the Doubly Linked List.
 * @param startPointer
 * @return nodePointer
 */
struct Node *createFirstNode(struct Node *startPointer) {
    if (startPointer != nullptr) printf("Node has already been created.");
    else {
        startPointer = createNode();
        printf("Node Created Successfully.");
    }
    return startPointer;
}

/**
 * Appends the data by reading from console to the doubly linked list.
 * @param startPointer
 */
struct Node *appendData(struct Node *startPointer) {
    if (startPointer == nullptr) return createFirstNode(startPointer);
    else {
        struct Node *traverse;
        traverse = startPointer;
        while (traverse->next != nullptr) {
            traverse = traverse->next;
        }
        struct Node *newNode;
        newNode = createNode();
        traverse->next = newNode;
        traverse->previous = traverse;
        printf("Data has been appended successfully.");
        return startPointer;
    }
}

/**
 * Insert a node in the nth position of doubly linked list.
 * @param startPointer
 * @return currentPointer
 */
struct Node *insertNode(struct Node *startPointer) {
    struct Node *currentStart;
    currentStart = startPointer;
    int position = readPosition();
    if (isValidPosition(position, count(startPointer))) {
        printf("Invalid Position.");
        return (currentStart);
    }
    if (position == 0) {
        struct Node *tempNode;
        tempNode = createNode();
        tempNode->next = startPointer;
        tempNode->previous = nullptr;
        currentStart = tempNode;
        printf("Node has been inserted successfully.");
    } else {
        for (int index = 0; index < position - 1; index++)
            startPointer = startPointer->next;
        struct Node *tempNode, *tempNode1, *tempNode2;
        tempNode1 = startPointer;
        tempNode2 = startPointer->next;
        tempNode = createNode();
        tempNode->next = tempNode2;
        tempNode->previous = tempNode1;
        tempNode1->next = tempNode;
        printf("Node has been inserted successfully.");
    }
    return (currentStart);
}

/**
 * Deletes a node by taking the position input from console.
 * @param startPointer
 * @return currentStartPointer
 */
struct Node *deleteNode(struct Node *startPointer) {
    if (startPointer == nullptr) {
        printf("Doubly Linked List is empty, unable to delete.");
        return startPointer;
    }
    int position = readPosition();
    int items = count(startPointer);
    if (position > count(startPointer) || position < 0) {
        printf("Invalid Position.");
        return (startPointer);
    }

    if (startPointer->next == nullptr) {
        struct Node *tempNode = startPointer;
        startPointer = nullptr;
        free(tempNode);
        printf("Last Node has been deleted from the Doubly Linked List.");
    } else if (isLastNode(position, items)) {
        deleteLastNode(startPointer);
    } else {

    }
    return startPointer;
}

/**
 * Display all the available nodes of the Doubly Linked List.
 * @param startPointer
 */
struct Node *displayItems(struct Node *startPointer) {
    struct Node *currentNode;
    currentNode = startPointer;
    if (startPointer == nullptr) {
        printf("\nDoubly Linked List is Empty.");
    } else {
        printf("\n\nAvailable Data: \n\t");
        while (startPointer != nullptr) {
            printf("\t%d", startPointer->data);
            startPointer = startPointer->next;
        }
    }
    return currentNode;
}

/**
 * Counts all the available nodes.
 * @param startPointer
 */
int count(struct Node *startPointer) {
    int counter = 1;
    if (startPointer == nullptr) counter = 0;
    else {
        while (startPointer->next != nullptr) {
            startPointer = startPointer->next;
            counter++;
        }
    }
    return counter;
}

/**
 * Deletes a node by taking the position input from console.
 * @param startPointer
 * @return currentStartPointer
 */
struct Node *deleteLastNode(struct Node *startPointer) {
    if (startPointer == nullptr) printf("Doubly Linked List is empty, unable to delete.");
    else if (startPointer->next == nullptr) {
        struct Node *tempNode;
        tempNode = startPointer;
        startPointer = nullptr;
        free(tempNode);
        printf("Last Node has been deleted from the Doubly Linked List.");
    } else {
        struct Node *currentStart;
        currentStart = startPointer;
        while (currentStart->next->next != nullptr)
            currentStart = currentStart->next;
        struct Node *tempNode;
        tempNode = currentStart->next;
        currentStart->next = nullptr;
        free(tempNode);
        printf("Last Node has been deleted from the Doubly Linked List.");
    }
    return startPointer;
}

/**
 * Prints the total items in the linked list.
 * @param startPointer
 */
struct Node *displayCount(struct Node *startPointer) {
    struct Node *traverse;
    traverse = startPointer;
    int totalItems = count(traverse);
    printf("Number of Nodes : %d", totalItems);
    return startPointer;
}

/**
 * Stops the program.
 * @param startPointer
 * @return startPointer
 */
struct Node *stopProgram(struct Node *startPointer) {
    printf("\nGood Bye !");
    exit(1);
    return startPointer;
}

