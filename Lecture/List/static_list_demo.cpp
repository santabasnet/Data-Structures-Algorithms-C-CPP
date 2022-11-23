/**
 * Chapter - 4.
 * Static list using Array implementation demo.
 * Date: 2022-11-23
 * Everest Engineering College.
 * Sanepa, Lalitpur
 * https://integratedict.com.np
 * https://semantro.com
 */

#include <stdio.h>

/**
 * Max item that can be inserted to the defined list.
 */
#define MAX 10

/**
 * A list definition.
 */
struct List {
    int items[MAX];
    int noOfItems;
};

/**
 * A global variable declared for the list.
 */
struct List ageList;

/**
 * Initialize the list with -1 index. We use -1 convention
 * and will be using pre-increment during insertion.
 */
void initialize() {
    ageList.noOfItems = -1;
}

int isFull() {
    return ageList.noOfItems >= MAX - 1;
}

void append(int value) {
    if (isFull()) {
        printf("Full !");
        return;
    }
    ageList.items[++ageList.noOfItems] = value;
}

void display(struct List list) {
    printf("\nList items: ");
    for (int i = 0; i <= list.noOfItems; i++) {
        printf("\nAge[%d] = %d", i, list.items[i]);
    }
}

struct List emptyList() {
    struct List r;
    r.noOfItems = -1;
    return r;
}


struct List concat(struct List l1, struct List l2) {

    /**
     * Check if we can concat or not.
     */
    if (l1.noOfItems + l2.noOfItems >= MAX) {
        return emptyList();
    }

    struct List result = emptyList();
    for (int i = 0; i <= l1.noOfItems; i++) {
        result.items[++result.noOfItems] = l1.items[i];
    }
    for (int i = 0; i <= l2.noOfItems; i++) {
        result.items[++result.noOfItems] = l2.items[i];
    }
    return result;
}

int isEmpty(struct List list) {
    return list.noOfItems < 0;
}

int nonEmpty(struct List list) {
    return !isEmpty(list);
}

int main() {
    initialize();
    append(100);
    append(67);
    append(90);

    struct List r = concat(ageList, ageList);
    struct List x = concat(r, r);

    //fix it ??? What's wrong with it.
    if (isEmpty(x) && nonEmpty(r)) {
        printf("Unable concat.");
    }

    display(ageList);
    printf("\n");
    display(r);

    return 0;
}