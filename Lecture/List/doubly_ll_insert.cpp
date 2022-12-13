#include<stdlib.h>
#include<stdio.h>
struct DLinkedList {
    int data;
    struct DLinkedList *p;
    struct DLinkedList *n;
};

struct DLinkedList *start;

struct DLinkedList* createNew(int data){
    struct DLinkedList *newNode = (struct DLinkedList*) malloc(sizeof(struct DLinkedList));
    newNode -> data = data;
    newNode -> p = nullptr;
    newNode -> n = nullptr;
    return newNode;
}

struct DLinkedList* insert(int data){
    if(start == nullptr) return createNew(data);
    struct DLinkedList *t = start;
    while(t -> n != nullptr) t = t -> n;
    struct DLinkedList *newNode = createNew(data);
    t -> n = newNode;
    newNode -> p = t;
    return start;
}

void display(){
    struct DLinkedList *tStart = start;
    printf("Doubly Linked List Data: \n\t");
    while(tStart != nullptr){
        printf("[%X|%d|%X] --> \n\t", tStart->p, tStart->data, tStart->n);
        tStart = tStart -> n;
    }
}

int main() {
    start = nullptr;
    start = insert(13);
    start = insert(81);
    start = insert(92);
    start = insert(43);
    start = insert(65);
    start = insert(0);
    display();
    return 0;
}