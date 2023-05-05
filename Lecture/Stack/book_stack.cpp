#include <cstdlib>
#include <cstring>
#include <cstdio>

#define MAX 100
#define EMPTY -1

enum Result {
    SUCCESS, FAILURE
};
enum Boolean {
    FALSE, TRUE
};

typedef struct {
    char writer[64];
    int publishedYear;
    char title[100];
} Book;

struct Stack {
    Book dataItems[MAX];
    int topOfStack;
} books;


void initialize() {
    books.topOfStack = EMPTY;
}

Boolean isFool() {
    if (books.topOfStack >= MAX) return TRUE;
    else return FALSE;
}

Boolean isEmpty(){
    if(books.topOfStack == EMPTY) return TRUE;
    else return FALSE;
}

Book emptyBook(){
    Book empty;
    empty.publishedYear = 0;
    strcpy(empty.title, "");
    strcpy(empty.writer, "");
}

Result push(Book book) {
    /**
     * Check isFool or not ?, here is Fool word is written intentionally.
     */
    if (isFool()) {
        return FAILURE;
    } else {
         books.dataItems[++books.topOfStack] = book;
         return SUCCESS;
    }
}

Book pop(){
    if(isEmpty()){
        return emptyBook();
    }else {
        return books.dataItems[books.topOfStack--];
    }
}

void displayResult(Result r){
    if(r == SUCCESS){
        printf("\nSuccessfully pushed.");
    }else {
        printf("\nWarning ! There is something seriously wrong !");
    }
}

Boolean isEmptyBook(Book b){
    if(strcmp(b.title, "") == 0 || strcmp(b.writer, "") == 0 || b.publishedYear == 0){
        return TRUE;
    }else return FALSE;
}

void displayBook(Book b){
    if(isEmptyBook(b)){
        printf("\nUnable to print !, the book is empty.");
    }else {
        printf("\n Book Details : ");
        printf("\n\tTitle : %s", b.title);
        printf("\n\tWriter : %s", b.writer);
        printf("\n\tPublished Year : %d", b.publishedYear);
    }
}

int main() {
    initialize();

    Book dsaBook = {
            "Andrew Tanenbam",
            2001,
            "Data Structure & Algo using C/C++"
    };

    Book ntBook = {
            "Priya Sharma",
            2004,
            "Network Theory for EEC Students."
    };
    displayResult(push(dsaBook));
    displayResult(push(ntBook));

    displayBook(pop());
    displayBook(pop());
    displayBook(pop());

    return 0;
}