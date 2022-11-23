/**
 * A circular queue implementation.
 *
 *  by: Santa Basnet, DSA
 *  Everest Engineering College.
 *
 * A linear data structure that is designed to fulfill all the places, all the usable spaces
 * in the static representation. It is done by using modulus (%) operator.
 *
 * Queue full case:
 *  1. head = 0 && tail == MAX_SIZE - 1
 *  2. head = tail + 1
 *
 * Queue empty case:
 *  1. head = -1.
 */

#include <cstdio>

#define MAX_SIZE 10

/**
 * A boolean type representation.
 */
enum boolean {
    FALSE, TRUE
};

/**
 * Define the structural representation.
 */
typedef struct {
    int head, tail;
    int items[MAX_SIZE];
} CircularQueue;

/**
 * An empty queue.
 */
CircularQueue emptyQueue() {
    CircularQueue queue;
    queue.head = -1;
    queue.tail = -1;
    return queue;
}

CircularQueue circularQueue;

/**
 * Initialize Queue here.
 */
void initQueue() {
    circularQueue = emptyQueue();
}

/**
 * Identify the given circular queue is empty or not.
 */
boolean isEmpty() {
    if (circularQueue.head == -1) return TRUE;
    else return FALSE;
}

/**
 * Identify the given circular queue is full or not.
 */
boolean isFull() {
    if ((circularQueue.head == circularQueue.tail + 1) ||
        (circularQueue.head == 0 && circularQueue.tail == MAX_SIZE - 1))
        return TRUE;
    else
        return FALSE;
}

/**
 * Enqueue operation, adds an element to the queue.
 */
void enQueueOperation(int item) {
    if (isFull()) {
        printf("\nGiven Queue is full !");
    } else {
        if (circularQueue.head == -1) circularQueue.head++;
        circularQueue.tail = (circularQueue.tail + 1) % MAX_SIZE;
        circularQueue.items[circularQueue.tail] = item;
    }
}

/**
 * Dequeue operation, removes an item element from the queue.
 */
int deQueueOperation() {
    if (isEmpty()) {
        printf("\nQueue is empty, unable to remove item!");
        return -1;
    } else {
        int item = circularQueue.items[circularQueue.head];
        if (circularQueue.head == circularQueue.tail) {
            circularQueue.head = -1;
            circularQueue.tail = -1;
        } else {
            circularQueue.head = (circularQueue.head + 1) % MAX_SIZE;
        }
        return item;
    }
}

/**
 * Display Items from the queue.
 */
void displayQueue() {
    if (isEmpty()) {
        printf("\nQueue is empty !");
        return;
    }
    printf("\n-------------------------------------------------------------------------");
    printf("\nQueue Summary: head = %d, tail = %d.", circularQueue.head, circularQueue.tail);
    printf("\n-------------------------------------------------------------------------");
    int i;
    for (i = circularQueue.head; i != circularQueue.tail; i = (i + 1) % MAX_SIZE) {
        printf("\n\tItem[%d] = %d", i, circularQueue.items[i]);
    }
    printf("\n\tItem[%d] = %d", i, circularQueue.items[i]);
    printf("\n-------------------------------------------------------------------------");
}

/**
 * Program Starts here.
 * @return
 */
int main() {
    initQueue();
    /**
     * Enqueue Operation.
     */
    enQueueOperation(100);
    enQueueOperation(200);
    enQueueOperation(300);
    enQueueOperation(700);
    enQueueOperation(900);

    /**
     * Display Items.
     */
    displayQueue();

    /**
     * Perform Dequeue Operation.
     */
    deQueueOperation();
    deQueueOperation();

    /**
     * Display Items after deletion.
     */
     displayQueue();

    return 0;
}