/**
 * Linked List Simulation.
 *
 * Everest Engineering College.
 * By: Santa Basnet
 * Date: 2021-11-30
 */

#include <malloc.h>
#include <cstdlib>

#define TRUE 1

/**
 * Node : data and next pointer representation.
 */
struct Node {
    int data;
    struct Node *next;
};

/**
 * Function prototypes.
 */
int displayMenu();

int readChoice();

int count(struct Node *);

struct Node *errorChoice(struct Node *);

struct Node *stopProgram(struct Node *);

struct Node *displayItems(struct Node *);

struct Node *displayCount(struct Node *);

struct Node *createNode();

struct Node *appendData(struct Node *);

struct Node *deleteLastNode(struct Node *);

struct Node *insertNode(struct Node *);

struct Node *createFirstNode(struct Node *);

/**
 * Main Function starts here.
 * @return 1 with successful operation.
 */
int main() {
    struct Node *start = nullptr;
    struct Node *(*operations[7])(struct Node *) = {
            &appendData, &insertNode, &displayCount, &deleteLastNode, &displayItems, &stopProgram, &errorChoice
    };
    while (TRUE) {
        int index = displayMenu();
        index = index > 7 || index < 1 ? 7 : index;
        start = operations[index - 1](start);
    }
    return 1;
}

/**
* Display Menu Options.
*/
int displayMenu() {
    printf("\n\n************MENU************");
    printf("\n1. Append Node");
    printf("\n2. Insert at Nth Node");
    printf("\n3. Count Number of Nodes");
    printf("\n4. Delete from Last Node");
    printf("\n5. Display All Item Nodes");
    printf("\n6. Exit");
    printf("\n----------------------------");
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
 * Create a node by reading a data value.
 */
struct Node *createNode() {
    struct Node *tempNode;
    tempNode = (struct Node *) malloc(sizeof(struct Node));
    tempNode->data = readDataValue();
    tempNode->next = nullptr;
    return tempNode;
}

/**
 * Creates the first node by reading a value from console.
 * @return nodePointer, a pointer to the newly crated node.
 */
struct Node *createFirstNode(struct Node *start) {
    if (start != nullptr) printf("First node has already been created.");
    else {
        start = createNode();
        printf("Data has been appended successfully.");
    }
    return (start);
}

/**
 * Appends the data by reading from console to the linked list.
 * @param startPointer
 */
struct Node *appendData(struct Node *startPointer) {
    if (startPointer == nullptr) return createFirstNode(startPointer);
    else {
        struct Node *traverse = startPointer;
        while (traverse->next != nullptr) {
            traverse = traverse->next;
        }
        struct Node *newNode = createNode();
        traverse->next = newNode;
        printf("Data has been appended successfully.");
        return startPointer;
    }
}

/**
 * Insert a node in the nth position.
 * @param startPointer
 * @return currentPointer
 */
struct Node *insertNode(struct Node *startPointer) {
    struct Node *currentStart = startPointer;
    int position = readPosition();
    if (position > count(startPointer) || position < 0) {
        printf("Invalid Position.");
        return (currentStart);
    }
    if (position == 0) {
        struct Node *tempNode = createNode();
        tempNode->next = startPointer;
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
        tempNode1->next = tempNode;
        printf("Node has been inserted successfully.");
    }
    return (currentStart);
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
 * Prints the total items in the linked list.
 * @param startPointer
 */
struct Node *displayCount(struct Node *startPointer) {
    struct Node *traverse = startPointer;
    int totalItems = count(traverse);
    printf("Number of Nodes : %d", totalItems);
    return startPointer;
}

/**
 * Deletes a node by taking the position input from console.
 * @param startPointer
 * @return currentStartPointer
 */
struct Node *deleteLastNode(struct Node *startPointer) {
    if (startPointer == nullptr) printf("List is empty, unable to delete.");
    else if (startPointer->next == nullptr) {
        struct Node *tempNode = startPointer;
        startPointer = nullptr;
        free(tempNode);
        printf("Last Node has been deleted.");
    } else {
        struct Node *currentStart = startPointer;
        while (currentStart->next->next != nullptr)
            currentStart = currentStart->next;
        struct Node *tempNode;
        tempNode = currentStart->next;
        currentStart->next = nullptr;
        free(tempNode);
        printf("Last Node has been deleted.");
    }
    return startPointer;
}

/**
 * Display all the created nodes.
 * @param startPointer
 */
struct Node *displayItems(struct Node *startPointer) {
    struct Node *currentNode = startPointer;
    if (startPointer == nullptr) {
        printf("\nLinked List is Empty.");
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
 * Stops program.
 * @param startPointer
 * @return startPointer
 */
struct Node *stopProgram(struct Node *startPointer) {
    printf("\nGood Bye !");
    exit(1);
    /** Not necessary but to fullfill the generic function signature. **/
    return startPointer;
}

/**
* Displays a message of error choice.
* @param startPointer
* @return startPointer
*/
struct Node *errorChoice(struct Node *startPointer) {
    printf("Error Choice ! Please select again.");
    return startPointer;
}