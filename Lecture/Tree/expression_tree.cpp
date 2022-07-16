/**
 * Expression tree generations for arithmetic expression.
 * 0. Operands are the lower case alphabets of the English.
 * 1. Convert infix to postfix expression, considering parenthesis and
 *    precedence of arithmetic operators.
 * 2. Build expression tree using evaluation algorithm.
 *
 * By: Santa Basnet
 * Everest Engineering College.
 * Date: 2021-12-05
 */

#include <cstring>
#include <cstdio>
#include <cstdlib>

/**
 * Boolean literals.
 */
#define TRUE 1
#define FALSE 0
#define TERMINATION '\0'

/**
 * Define operators.
 */
const char PLUS = '+';
const char MINUS = '-';
const char MULTIPLY = '*';
const char DIVIDE = '/';
const char EXPONENT = '^';
const char LEFT_PARENTHESIS = '(';
const char RIGHT_PARENTHESIS = ')';

/**
 * Definition of operator precedence.
 */
const int DEFAULT_PRECEDENCE = 0;
const int PLUS_PRECEDENCE = 1;
const int MINUS_PRECEDENCE = 1;
const int MULTIPLY_PRECEDENCE = 2;
const int DIVIDE_PRECEDENCE = 2;
const int EXPONENT_PRECEDENCE = 3;

/**
 * Returns the precedence value of the operator.
 */
int precedenceOf(char inputChar) {
    switch (inputChar) {
        case PLUS:
            return PLUS_PRECEDENCE;
        case MINUS:
            return MINUS_PRECEDENCE;
        case MULTIPLY:
            return MULTIPLY_PRECEDENCE;
        case DIVIDE:
            return DIVIDE_PRECEDENCE;
        case EXPONENT:
            return EXPONENT_PRECEDENCE;
        default :
            return DEFAULT_PRECEDENCE;
    }
}

/**
 * Expression representation.
 */
const int MAX_SIZE = 128;
struct ArithmeticExpression {
    int topOfStack;
    char operatorStack[MAX_SIZE];
    char postfixExpression[MAX_SIZE];
} expression;

/**
 * Intermediate Postfix expression.
 */
struct IntermediateExpression {
    int topOfStack;
    char stack[MAX_SIZE];
} evaluation;

/**
 * Representation of Expression Node.
 */
struct ExpressionTree {
    char placeValue;
    struct ExpressionTree *leftChild;
    struct ExpressionTree *rightChild;
};

/**
 * Creates a place value node for a expression entry.
 * @param placeValue
 * @return placeValueNode
 */
struct ExpressionTree *newPlaceValue(char placeValue) {
    struct ExpressionTree *newNode = (struct ExpressionTree *) malloc(sizeof(struct ExpressionTree));
    newNode->placeValue = placeValue;
    newNode->leftChild = nullptr;
    newNode->rightChild = nullptr;
    return (newNode);
}

/**
 * Error: Invalid expression and exit from the program with error code 0.
 */
void invalidExpression() {
    printf("\nThe input expression is not valid.");
    exit(0);
}

/**
 * Stack Full Error.
 */
void stackFullError() {
    printf("\nStack full, unable to compute further.");
    exit(0);
}

/**
 * Stack Empty Error.
 */
void stackEmptyError() {
    printf("\nStack empty, unable to compute further.");
    exit(0);
}

/**
 * Checks if the input character is of operator type or not.
 */
int isOperator(char inputChar) {
    switch (inputChar) {
        case PLUS:
        case MINUS:
        case MULTIPLY:
        case DIVIDE:
        case EXPONENT:
            return TRUE;
        default :
            return FALSE;
    }
}

/**
 * Declare Input Expression.
 */
char *inputExpression;

/**
 * Read input expression from console.
 */
void readInputExpression() {
    size_t buffer = 128;
    printf("\nInput Expression: \n");
    getline(&inputExpression, &buffer, stdin);
}

/**
 * Scan index for input character array.
 */
int scannedIndex = 0;

/**
 * Returns an input character.
 */
char scanInput() {
    if (scannedIndex < strlen(inputExpression)) return inputExpression[scannedIndex++];
    else return TERMINATION;
}

/**
 * Postfix index to scan from left to right.
 */
int postfixIndex = 0;

/**
 * Scan from postfix expression.
 */
char scanPostfix() {
    if (postfixIndex >= strlen(expression.postfixExpression)) return TERMINATION;
    else return expression.postfixExpression[postfixIndex++];
}

/**
 * Checks if the stack is full.
 */
int isStackFull() {
    return expression.topOfStack >= MAX_SIZE ? TRUE : FALSE;
}

/**
 * Checks if the stack is empty or not.
 */
int isStackEmpty() {
    return expression.topOfStack == 0 ? TRUE : FALSE;
}

/**
 * Checks if the input character is of operand or not.
 * We consider all the single lower case English alphabets are the operands.
 */
int isOperand(char inputChar) {
    if (inputChar >= 'a' && inputChar <= 'z') return TRUE;
    else return FALSE;
}

/**
 * Perform push operation on operator stack.
 */
void push(char inputChar) {
    if (isStackFull()) stackFullError();
    expression.operatorStack[expression.topOfStack++] = inputChar;
    expression.operatorStack[expression.topOfStack] = TERMINATION;
}

/**
 * Perform the pop operation on operator stack.
 * @return character popped from the stack.
 */
char pop() {
    if (isStackEmpty()) stackEmptyError();
    char charOutput = expression.operatorStack[--expression.topOfStack];
    expression.operatorStack[expression.topOfStack] = TERMINATION;
    return charOutput;
}

/**
 * Output to postfix expression.
 */
void outputToExpression(char outputChar) {
    size_t index = strlen(expression.postfixExpression);
    expression.postfixExpression[index] = outputChar;
    expression.postfixExpression[index + 1] = TERMINATION;
}

/**
 * Perform the pop operation and update the output expression.
 */
void popAndUpdateOutput() {
    char poppedChar = pop();
    while (poppedChar != LEFT_PARENTHESIS) {
        outputToExpression(poppedChar);
        poppedChar = pop();
    }
}

/**
 * Perform pop and push operation using operator precedence.
 */
void popAndPushOutput(char inputOperator) {
    char topOperator = pop();
    while (precedenceOf(topOperator) >= precedenceOf(inputOperator)) {
        outputToExpression(topOperator);
        topOperator = pop();
    }
    push(topOperator); // One more operator has been taken out.
    push(inputOperator);
}

/**
 * Initialize the expression representation. The input expression always have
 * new line character at the end of it. (This is from the use of getline function.)
 * So, it needs to be handled in initialize function.
 */
void initializeExpressionStack() {
    expression.topOfStack = 0;
    push(LEFT_PARENTHESIS);
    expression.postfixExpression[0] = TERMINATION;
    inputExpression[strlen(inputExpression) - 1] = RIGHT_PARENTHESIS;
    inputExpression[strlen(inputExpression)] = TERMINATION;
}

/**
 * Convert Infix expression to Postfix expression.
 */
void convertToPostfix() {
    char inputChar = scanInput();
    while (inputChar != TERMINATION) {
        if (inputChar == LEFT_PARENTHESIS) push(inputChar);
        else if (isOperand(inputChar)) outputToExpression(inputChar);
        else if (isOperator(inputChar)) popAndPushOutput(inputChar);
        else if (inputChar == RIGHT_PARENTHESIS) popAndUpdateOutput();
        else invalidExpression();
        inputChar = scanInput();
    }
}

/**
 * Operation for infix to postfix conversion.
 */
void operationOfInfixToPostfix() {
    readInputExpression();
    initializeExpressionStack();
    convertToPostfix();
}

/**
 * Initialize evaluation stack.
 */
void initializeEvaluationStack() {
    evaluation.topOfStack = -1;
}

/**
 * Pop operand for evaluation.
 */
char popOperand() {
    return evaluation.stack[evaluation.topOfStack--];
}

/**
 * Push operand to evaluation stack.
 */
void pushOperand(char operand) {
    evaluation.stack[++evaluation.topOfStack] = operand;
}

/**
 * Creates a node in the memory and returns the address.
 */
struct ExpressionTree *createNode(char operatorChar) {
    struct ExpressionTree *nodePointer = (struct ExpressionTree *) malloc(sizeof(ExpressionTree));
    nodePointer->placeValue = operatorChar;
    nodePointer->leftChild = nullptr;
    nodePointer->rightChild = nullptr;
    return nodePointer;
}


/**
 * Pop two operands and Build Tree Here.
 */
struct ExpressionTree *popAndBuildTree(struct ExpressionTree *rootPointer, char operatorChar) {
    char operandTwo = popOperand();
    if (rootPointer == nullptr) {
        char operandOne = popOperand();
        struct ExpressionTree *newNode = createNode(operatorChar);
        newNode->leftChild = createNode(operandOne);
        newNode->rightChild = createNode(operandTwo);
        rootPointer = newNode;
    } else {
        struct ExpressionTree *newNode = createNode(operatorChar);
        newNode->leftChild = rootPointer;
        newNode->rightChild = createNode(operandTwo);
        rootPointer = newNode;
    }
    return rootPointer;
}

/**
 * Evaluate Postfix Expression.
 */
struct ExpressionTree *buildExpressionTree() {
    struct ExpressionTree *startPointer = nullptr;
    char inputChar = scanPostfix();
    while (inputChar != TERMINATION) {
        if (isOperand(inputChar)) pushOperand(inputChar);
        else if (isOperator(inputChar)) startPointer = popAndBuildTree(startPointer, inputChar);
        else invalidExpression();
        inputChar = scanPostfix();
    }
    return startPointer;
}

/**
 * Post order traversal.
 * 1. Visit Left Child.
 * 2. Visit Right Child.
 * 3. Display Data.
 */
struct ExpressionTree *postOrderTraversal(struct ExpressionTree *rootPointer) {
    struct ExpressionTree *traverse = rootPointer;
    if (traverse != nullptr) {
        postOrderTraversal(traverse->leftChild);
        postOrderTraversal(traverse->rightChild);
        printf("\t%4c", traverse->placeValue);
    }
    return rootPointer;
}

/**
 * Preorder Traversal.
 * 1. Display Data.
 * 2. Visit Left Child.
 * 3. Visit Right Child.
 */
struct ExpressionTree *preOrderTraversal(struct ExpressionTree *rootPointer) {
    struct ExpressionTree *traverse = rootPointer;
    if (traverse != nullptr) {
        printf("\t%4c", traverse->placeValue);
        preOrderTraversal(traverse->leftChild);
        preOrderTraversal(traverse->rightChild);
    }
    return rootPointer;
}

/**
 * Inorder Traversal.
 * 1. Visit Left Child.
 * 2. Display Data.
 * 3. visit Right Child.
 * @param rootPointer
 */
struct ExpressionTree *inOrderTraversal(struct ExpressionTree *rootPointer) {
    struct ExpressionTree *traverse = rootPointer;
    if (traverse != nullptr) {
        printf("(");
        inOrderTraversal(traverse->leftChild);
        printf("%c", traverse->placeValue);
        inOrderTraversal(traverse->rightChild);
        printf(")");
    }
    return rootPointer;
}

//------------------------------------------------------------------------------
struct SubTree {
    SubTree *previous;
    char *strData;
};

struct SubTree *createSubTree(struct SubTree *subTree, char *strData) {
    struct SubTree *nodePointer = (struct SubTree *) malloc(sizeof(SubTree));
    nodePointer->previous = subTree;
    nodePointer->strData = strData;
    return nodePointer;
}

void printSubTree(SubTree *node) {
    if (node == nullptr) return;
    printSubTree(node->previous);
    printf("%s", node->strData);
}

void printBinaryTree(ExpressionTree *root, SubTree *prev, bool isLeft) {
    if (root == nullptr) return;
    char *previousString = "    ";
    SubTree *trunk = createSubTree(prev, previousString);
    printBinaryTree(root->rightChild, trunk, true);

    if (!prev) trunk->strData = "———";
    else if (isLeft) {
        trunk->strData = ".———";
        previousString = "   |";
    } else {
        trunk->strData = "`———";
        prev->strData = previousString;
    }

    printSubTree(trunk);
    printf(" ");
    printf("'%c'\n", root->placeValue);

    if (prev) prev->strData = previousString;
    trunk->strData = "   |";

    printBinaryTree(root->leftChild, trunk, false);
}
//------------------------------------------------------------------------------

/**
 * Expression Tree.
 */
void operationOfExpressionTree() {
    initializeEvaluationStack();
    printf("Output: %s", expression.postfixExpression);
    struct ExpressionTree *startPointer = buildExpressionTree();
    printf("\n\t\t");
    startPointer = inOrderTraversal(startPointer);
    printf("\n\t");
    startPointer = preOrderTraversal(startPointer);
    printf("\n\t");
    startPointer = postOrderTraversal(startPointer);
    /**
     * Print Tree.
     */
    printf("\n\nExpression Tree: \n");
    printBinaryTree(startPointer, nullptr, false);
}

/**
 * Main function starts here.
 * @return 1 for successful operation.
 */
int main() {
    operationOfInfixToPostfix();
    operationOfExpressionTree();
    return 1;
}