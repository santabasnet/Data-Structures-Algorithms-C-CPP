/**
 * AVL Tree Implementation and Traversal.
 *
 * 1. Binary search tree.
 * 2. Balance the binary search tree.
 * 3. Balance factor: Height of Left sub-tree - Height of right sub-tree.
 * 4. Height of the sub-tree.
 *
 * By Santa Basnet.
 * Everest Engineering College.
 * Date: 2021-12-07
 */

#include <malloc.h>
#include <stdio.h>

/**
 * AVL Node Representation.
 */
struct AVLNode {
    int data, height;
    struct AVLNode *leftChild, *rightChild;
};

/**
 * Tree Representation.
 */
struct AVLTree {
    struct AVLNode *rootNode;
};

/**
 * Creates a node in the memory and returns the address.
 */
static struct AVLNode *createNewNode(int data) {
    struct AVLNode *nodePointer = (struct AVLNode *) malloc(sizeof(AVLNode));
    nodePointer->data = data;
    nodePointer->height = 1;
    nodePointer->leftChild = nullptr;
    nodePointer->rightChild = nullptr;
    return nodePointer;
}

/**
 * Get max value between a and b.
 * @param a
 * @param b
 * @return maxValue
 */
static int maxOf(int a, int b) {
    return (a > b) ? a : b;
}


/**
 * Calculates the node height in the given table.
 */
static int nodeHeight(struct AVLNode *node) {
    if (node == nullptr) return 0;
    else return node->height;
}

/**
 * Calculate balance factor.
 */
static int balanceFactorOf(struct AVLNode *node) {
    if (node == nullptr) return 0;
    else return nodeHeight(node->leftChild) - nodeHeight(node->rightChild);
}

/**
* Calculate height.
*/
static int heightOf(struct AVLNode *rootPointer) {
    return 1 + maxOf(nodeHeight(rootPointer->leftChild), nodeHeight(rootPointer->rightChild));
}

/**
 * Returns the minimum valued child node.
 * @param rootPointer
 * @return minimumValuedChildNode
 */
static struct AVLNode *minimumOf(struct AVLNode *rootPointer) {
    struct AVLNode *current = rootPointer;
    while (current->leftChild != nullptr)
        current = current->leftChild;
    return current;
}

/**
 * Perform left and left rotations.
 * @param rootNode
 * @return rotatedRootNode
 */
static struct AVLNode *rotateLeft(struct AVLNode *rootNode) {
    struct AVLNode *rightNode = rootNode->rightChild;
    struct AVLNode *leftNode = rightNode->leftChild;
    rightNode->leftChild = rootNode;
    rootNode->rightChild = leftNode;
    rootNode->height = heightOf(rootNode);
    rightNode->height = heightOf(rightNode);
    return rightNode;
}

/**
 * Perform rotation of Left and Right.
 * @param rootNode
 * @return rotatedNode.
 */
static struct AVLNode *rotateRight(struct AVLNode *rootNode) {
    struct AVLNode *leftNode = rootNode->leftChild;
    struct AVLNode *rightNode = leftNode->rightChild;
    leftNode->rightChild = rootNode;
    rootNode->leftChild = rightNode;
    rootNode->height = heightOf(rootNode);
    leftNode->height = heightOf(leftNode);
    return leftNode;
}

/**
 * Make balance tree: requires 4 rotations.
 * 1. RR rotation:
 *  (A)
 *      \     <--┐
 *       (B)     |
 *         \
 *          (C)
 *  Output:
 *
 *      (B)
 *     /   \
 *   (A)   (C)
 *
 * 2. LL Rotation
 *          (A)
 *  ┌-->   /
 *  |   (B)
 *      /
 *    (C)
 *  Output:
 *        (B)
 *       /   \
 *     (C)   (A)
 *
 * 3. LR Rotation:
 *           (A)
 *         /
 *       (B)
 *         \
 *          (C)
 *
 *    Output:
 *
 *      (a) Rotate C - B, counter clockwise.
 *            (A)
 *            /
 *          (C)
 *          /
 *        (B)
 *
 *      (b) Rotate B - C - A, clockwise.
 *
 *             (C)
 *            /   \
 *          (B)    (A)
 *
 * 4. RL Rotation:
 *         (A)
 *            \
 *             (B)
 *            /
 *          (C)
 *
 *    Output:
 *
 *      (a) Rotate C - B Clock wise.
 *            (A)
 *               \
 *               (B)
 *                  \
 *                  (C)
 *
 *      (b) Rotate C - B - A, counter clockwise.
 *
 *             (B)
 *            /   \
 *          (A)    (C)
 *
 * Example:
 *                (H)-2
 *             /       \
 *           (B)-2     (I)
 *         /     \        \
 *       (A)     (E)      (J)
 *              /   \
 *            (C)   (F)
 *               \
 *                (D)
 *
 *
 *               (H)-2
 *              /      \
 *           (B)-2     (I)
 *         /     \        \
 *       (A)     (C)      (J)
 *                 \
 *                 (E)
 *                /   \
 *              (D)   (F)
 *
 *              (H)
 *             /    \
 *           (C)     (I)
 *         /     \      \
 *       (B)     (E)      (J)
 *      /       /   \
 *     (A)    (D)   (F)
 */
static struct AVLNode *makeBalance(struct AVLNode *rootPointer, int data) {
    int balance = balanceFactorOf(rootPointer);
    struct AVLNode *currentNode = rootPointer;
    if (balance >= 2 && data < rootPointer->leftChild->data) currentNode = rotateRight(rootPointer);
    else if (balance <= -2 && data > rootPointer->rightChild->data) currentNode = rotateLeft(rootPointer);
    else if (balance >= 2 && data > rootPointer->leftChild->data) {
        rootPointer->leftChild = rotateLeft(rootPointer->leftChild);
        currentNode = rotateRight(rootPointer);
    } else if (balance <= -2 && data < rootPointer->rightChild->data) {
        rootPointer->rightChild = rotateRight(rootPointer->rightChild);
        currentNode = rotateLeft(rootPointer);
    }
    return currentNode;
}

/**
 * Perform insert operation in the given binary tree.
 * @param rootPointer
 */
static struct AVLNode *avlInsert(struct AVLNode *rootPointer, int data) {
    if (rootPointer == nullptr) return createNewNode(data);
    else if (data < rootPointer->data) rootPointer->leftChild = avlInsert(rootPointer->leftChild, data);
    else if (data > rootPointer->data) rootPointer->rightChild = avlInsert(rootPointer->rightChild, data);
    else return rootPointer;
    rootPointer->height = heightOf(rootPointer);
    return makeBalance(rootPointer, data);
}

/**
 * Perform delete operation of the given data.
 */
static struct AVLNode *deleteEntry(struct AVLNode *rootPointer, int data) {
    if (rootPointer == nullptr) return rootPointer;
    if (data < rootPointer->data) rootPointer->leftChild = deleteEntry(rootPointer->leftChild, data);
    else if (data > rootPointer->data) rootPointer->rightChild = deleteEntry(rootPointer->rightChild, data);
    else {
        if (rootPointer->leftChild == nullptr) {
            struct AVLNode *tempNode = rootPointer->rightChild;
            free(rootPointer);
            rootPointer = tempNode;
        } else if (rootPointer->rightChild == nullptr) {
            struct AVLNode *tempNode = rootPointer->leftChild;
            free(rootPointer);
            rootPointer = tempNode;
        } else {
            struct AVLNode *tempNode = minimumOf(rootPointer->rightChild);
            rootPointer->data = tempNode->data;
            rootPointer->rightChild = deleteEntry(rootPointer->rightChild, tempNode->data);
        }
    }

    return makeBalance(rootPointer, data);
}

/**
 * Inorder Traversal.
 * 1. Visit Left Child.
 * 2. Display Data.
 * 3. visit Right Child.
 * @param rootPointer
 */
static struct AVLNode *displayAVLTree(struct AVLNode *rootPointer) {
    struct AVLNode *traverse = rootPointer;
    if (traverse != nullptr) {
        displayAVLTree(traverse->leftChild);
        printf("\t%c", traverse->data);
        displayAVLTree(traverse->rightChild);
    }
    return rootPointer;
}

/**
 * Perform search operation in the tree through root pointer.
 * @param rootPointer
 * @param data
 * @return nonZero value for found, zero for otherwise.
 */
static int avlSearch(AVLNode *rootPointer, int data) {
    if (rootPointer == nullptr) return 0;
    else if (rootPointer->data == data) return 1;
    else if (rootPointer->data > data) return avlSearch(rootPointer->leftChild, data);
    else return avlSearch(rootPointer->rightChild, data);
}

/**
 * Remove all the nodes, clean up memory.
 */
/* free a tree */
static void avlCleanUp(struct AVLNode *rootNode) {
    if (rootNode != nullptr) {
        avlCleanUp(rootNode->leftChild);
        avlCleanUp(rootNode->rightChild);
        free(rootNode);
    }
}

////////////////////////////////////////////////////////////////////////////////////
///Printing section for the binary tree. (Thanks someone in the internet.)
struct SubTree {
    SubTree *previous;
    char *strData;
};

static struct SubTree *createSubTree(struct SubTree *subTree, char *strData) {
    struct SubTree *nodePointer = (struct SubTree *) malloc(sizeof(SubTree));
    nodePointer->previous = subTree;
    nodePointer->strData = strData;
    return nodePointer;
}

static void printSubTree(SubTree *node) {
    if (node == nullptr) return;
    printSubTree(node->previous);
    printf("%s", node->strData);
}

static void printAVLTree(AVLNode *root, SubTree *prev, bool isLeft) {
    if (root == nullptr) return;
    char *previousString = "    ";
    SubTree *trunk = createSubTree(prev, previousString);
    printAVLTree(root->rightChild, trunk, true);

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
    printf("'%c'\n", root->data);

    if (prev) prev->strData = previousString;
    trunk->strData = "   |";

    printAVLTree(root->leftChild, trunk, false);
}
////////////////////////////////////////////////////////////////////////////////////

/**
 * Initialize Tree.
 */
static struct AVLTree *initializeTree() {
    struct AVLTree *avlTree = (struct AVLTree *) malloc(sizeof(struct AVLTree));
    avlTree->rootNode = nullptr;
    return avlTree;
}

/**
 * Initialize Data, the characters for capital letters of English Alphabets.
 */
const int MAX = 8;

static int *initializeData() {
    int *initialData = (int *) malloc(sizeof(int) * MAX);
    for (int index = 0; index < MAX; index++) initialData[index] = 65 + index;
    return initialData;
}

/**
 * Main Function starts here.
 * @return 1 for successful operations.
 */
int main() {
    int *initialData = initializeData();
    struct AVLTree *avlTree = initializeTree();

    for (int index = 0; index < MAX; index++)
        avlTree->rootNode = avlInsert(avlTree->rootNode, *(initialData + index));

    printf("\nAVL Tree Data: \n");
    avlTree->rootNode = displayAVLTree(avlTree->rootNode);

    printf("\n\nAll the tree data: \n\n");
    printAVLTree(avlTree->rootNode, nullptr, false);

    /* Demo Delete Entry 'F' */
    avlTree->rootNode = deleteEntry(avlTree->rootNode, 70);
    printf("\nAfter Deleting 'F': \n\n");
    printAVLTree(avlTree->rootNode, nullptr, false);

    printf("\n");
    printf("Result of Search: %d.\n", avlSearch(avlTree->rootNode, 80));

    /**
     * Clean up the tree.
     */
    avlCleanUp(avlTree->rootNode);
    free(avlTree);
    return 0;
}
