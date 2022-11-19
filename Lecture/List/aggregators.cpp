/**
 * Aggregator Function Implementation in Linked List.
 *
 * By Santa Basnet.
 * Everest Engineering College.
 * Date: 2021-11-30
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>

/**
 * Delimiter.
 */
const char *DELIMITER = ", ;";

/**
 * Node : data and next pointer representation.
 */
struct Node {
    int data;
    struct Node *next;
};

/**
 * Stores result value during operations.
 */
struct Result {
    int data;
    int counter;
};


char *readInputData();

struct Node *prepareData();

struct Result *initializeResult();

void displayItems(struct Node *);

struct Result *createNode(int, int);

struct Result *sum(struct Node *);

struct Result *average(struct Node *);

struct Result *min(struct Node *);

struct Result *max(struct Node *);

struct Result *count(struct Node *);

/**
 * Main Function. Program starts here.
 * @return 1 with successful operations.
 */
int main() {
    struct Node *start = prepareData();
    displayItems(start);

    struct Result *resultCount = count(start);
    printf("\nCount Result: %d", resultCount->data);

    struct Result *resultMax = max(start);
    printf("\nMax Result: %d", resultMax->data);

    struct Result *resultMin = min(start);
    printf("\nMin Result: %d", resultMin->data);

    struct Result *resultSum = sum(start);
    printf("\nSum Result: %d", resultSum->data);

    struct Result *resultAverage = average(start);
    printf("\nAverage Result: %.3lf", (double) resultAverage->data / (double) resultAverage->counter);
    printf("\n");

    return 1;
}

/**
 * Create a node by reading a data value.
 */
struct Node *createNode(int data) {
    struct Node *tempNode = (struct Node *) malloc(sizeof(struct Node));
    tempNode->data = data;
    tempNode->next = nullptr;
    return tempNode;
}

/**
 * Prepare data, and returns the start pointer.
 */
struct Node *prepareData() {
    struct Node *startPointer = nullptr;
    struct Node *traverse = nullptr;
    char *input;
    input = readInputData();
    char *token = strtok(input, DELIMITER);
    while (token != nullptr) {
        int value = atoi(token);
        if (startPointer == nullptr) startPointer = traverse = createNode(value);
        else {
            struct Node *newNode = createNode(value);
            traverse->next = newNode;
            traverse = traverse->next;
        }
        token = strtok(NULL, DELIMITER);
    }
    return startPointer;
}

/**
 * Input and Initialize the data.
 */
char *readInputData() {
    size_t buffer = 256;
    char *inputData = (char *) malloc(sizeof(char) * buffer);
    printf("\nInput Data: \n");
    getline(&inputData, &buffer, stdin);
    return inputData;
}

/**
 * Creates a new node with default values.
 * @return defaultValuedNode
 */
struct Result *initializeResult() {
    return createNode(0, 0);
}

/**
 * Creates a new node with given data and the counter.
 * @param data
 * @param counter
 * @return createdNode
 */
struct Result *createNode(int data, int counter) {
    struct Result *result = (struct Result *) malloc(sizeof(struct Result));
    result->data = data;
    result->counter = counter;
    return result;
}

/**
 * Given Average Function.
 * @return averageResult
 */
struct Result *average(struct Node *startPointer) {
    struct Result *result = createNode(0, 0);
    if (startPointer == nullptr) return result;
    else {
        while (startPointer != nullptr) {
            struct Result *newNode = createNode(startPointer->data + result->data, result->counter + 1);
            result = newNode;
            startPointer = startPointer->next;
        }
        return result;
    }
}

/**
 * Counts all the available nodes.
 * @param startPointer
 */
struct Result *sum(struct Node *startPointer) {
    struct Result *result = createNode(0, 0);
    if (startPointer == nullptr) return result;
    else {
        while (startPointer != nullptr) {
            struct Result *newNode = createNode(startPointer->data + result->data, 0);
            result = newNode;
            startPointer = startPointer->next;
        }
        return result;
    }
}

/**
 * Counts all the available nodes.
 * @param startPointer
 */
struct Result *min(struct Node *startPointer) {
    struct Result *result = createNode(999999999, 0);
    if (startPointer == nullptr) return result;
    else {
        while (startPointer != nullptr) {
            struct Result *newNode = createNode(startPointer->data < result->data ? startPointer->data : result->data, 0);
            result = newNode;
            startPointer = startPointer->next;
        }
        return result;
    }
}


/**
 * Counts all the available nodes.
 * @param startPointer
 */
struct Result *max(struct Node *startPointer) {
    struct Result *result = createNode(-999999999, 0);
    if (startPointer == nullptr) return result;
    else {
        while (startPointer != nullptr) {
            struct Result *newNode = createNode(startPointer->data > result->data ? startPointer->data : result->data, 0);
            result = newNode;
            startPointer = startPointer->next;
        }
        return result;
    }
}


/**
 * Cleanup Result.
 */
void cleanUpResult(struct Result *result) {
    struct Result *newTemp = result;
    free(newTemp);
}

/**
 * Counts all the available nodes.
 * @param startPointer
 */
struct Result *count(struct Node *startPointer) {
    if (startPointer == nullptr) return initializeResult();
    else {
        struct Result *result = createNode(0, 0);
        while (startPointer != nullptr) {
            struct Result *newNode = createNode(result->data + 1, 0);
            result = newNode;
            startPointer = startPointer->next;
        }
        return result;
    }
}

/**
 * Display all the created nodes.
 * @param startPointer
 */
void displayItems(struct Node *startPointer) {
    if (startPointer == nullptr) {
        printf("Linked List is Empty.");
    } else {
        printf("Available Data: \n\t");
        while (startPointer != nullptr) {
            printf("\t%d", startPointer->data);
            startPointer = startPointer->next;
        }
    }
}


