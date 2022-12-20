/**
 * Binary Search Tree Implementation and Traversal with Counts.
 *
 * By Santa Basnet.
 * Everest Engineering College.
 * Date: 2021-12-05
 * Example:
 *
 *                     110
 *                  /       \
 *                20        200
 *             /      \   /     \
 *           10      30  150    330
 *
 * Output:
 *  Inorder Traversal:			  10	  20	  30	 110	 150	 200	 330
 *  Preorder Traversal:			 110	  20	  10	  30	 200	 150	 330
 *  Postorder Traversal:		  10	  30	  20	 150	 330	 200	 110 
 */

#include <cstdio>
#include <cstdlib>

#define TRUE 1

/**
 * Binary Tree Representation.
 */
struct BinaryTreeNode {
    int data;
    struct BinaryTreeNode *leftChild, *rightChild;
};

/**
 * Perform a read operation of an integer data value from console.
 * @return dataValue
 */
static int readValue(const char *message) {
    int dataValue;
    fprintf(stdout, "%s", message);
    scanf("%d", &dataValue);
    return (dataValue);
}

/**
* Read choice value.
*/
static int readChoice() {
    return readValue("\n\tEnter Choice: ");
}

/**
 * Read a data value from console.
 */
static int readDataValue() {
    return readValue("\nEnter Data: ");
}

/**
 * Displays the choice options for the operations available in the binary tree..
 */
static int displayMenu() {
    printf("\n\n-------------BINARY TREE---------------");
    printf("\n(1) Insert Node");
    printf("\n(2) Delete Node");
    printf("\n(3) All Traversals");
    printf("\n(4) All Counts");
    printf("\n(5) Exit");
    printf("\n----------------------------------------");
    return readChoice();
}

/**
 * Creates a node in the memory and returns the address.
 */
static struct BinaryTreeNode *createNode(int data) {
    struct BinaryTreeNode *nodePointer = (struct BinaryTreeNode *) malloc(sizeof(BinaryTreeNode));
    nodePointer->data = data;
    nodePointer->leftChild = nullptr;
    nodePointer->rightChild = nullptr;
    return nodePointer;
}

/**
 * Perform insert operation in the given binary tree.
 * @param rootPointer
 */
static struct BinaryTreeNode *insertEntry(struct BinaryTreeNode *rootPointer, int data) {
    if (rootPointer == nullptr) return createNode(data);
    else if (data < rootPointer->data) rootPointer->leftChild = insertEntry(rootPointer->leftChild, data);
    else rootPointer->rightChild = insertEntry(rootPointer->rightChild, data);
    return rootPointer;
}

/**
 * Find minimum of two nodes.
 */
static struct BinaryTreeNode *minimumOf(struct BinaryTreeNode *givenNode) {
    struct BinaryTreeNode *currentNode = givenNode;
    while (currentNode && currentNode->leftChild != nullptr) currentNode = currentNode->leftChild;
    return currentNode;
}

/**
 * Perform delete operation of the given data.
 */
static struct BinaryTreeNode *deleteEntry(struct BinaryTreeNode *rootPointer, int data) {
    if (rootPointer == nullptr) return rootPointer;
    if (data < rootPointer->data) rootPointer->leftChild = deleteEntry(rootPointer->leftChild, data);
    else if (data > rootPointer->data) rootPointer->rightChild = deleteEntry(rootPointer->rightChild, data);
    else {
        if (rootPointer->leftChild == nullptr) {
            struct BinaryTreeNode *tempNode = rootPointer->rightChild;
            free(rootPointer);
            return tempNode;
        } else if (rootPointer->rightChild == nullptr) {
            struct BinaryTreeNode *tempNode = rootPointer->leftChild;
            free(rootPointer);
            return tempNode;
        }
        struct BinaryTreeNode *tempNode = minimumOf(rootPointer->rightChild);
        rootPointer->data = tempNode->data;
        rootPointer->rightChild = deleteEntry(rootPointer->rightChild, tempNode->data);
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
static struct BinaryTreeNode *inOrderTraversal(struct BinaryTreeNode *rootPointer) {
    struct BinaryTreeNode *traverse = rootPointer;
    if (traverse != nullptr) {
        inOrderTraversal(traverse->leftChild);
        printf("\t%4d", traverse->data);
        inOrderTraversal(traverse->rightChild);
    }
    return rootPointer;
}

/**
 * Preorder Traversal.
 * 1. Display Data.
 * 2. Visit Left Child.
 * 3. Visit Right Child.
 */
static struct BinaryTreeNode *preOrderTraversal(struct BinaryTreeNode *rootPointer) {
    struct BinaryTreeNode *traverse = rootPointer;
    if (traverse != nullptr) {
        printf("\t%4d", traverse->data);
        preOrderTraversal(traverse->leftChild);
        preOrderTraversal(traverse->rightChild);
    }
    return rootPointer;
}

/**
 * Post order traversal.
 * 1. Visit Left Child.
 * 2. Visit Right Child.
 * 3. Display Data.
 */
static struct BinaryTreeNode *postOrderTraversal(struct BinaryTreeNode *rootPointer) {
    struct BinaryTreeNode *traverse = rootPointer;
    if (traverse != nullptr) {
        postOrderTraversal(traverse->leftChild);
        postOrderTraversal(traverse->rightChild);
        printf("\t%4d", traverse->data);
    }
    return rootPointer;
}

/**
 * Perform all the Traversal.
 */
static struct BinaryTreeNode *allTraversals(struct BinaryTreeNode *rootPointer) {
    struct BinaryTreeNode *traverse = rootPointer;
    printf("\nInorder Traversal:\t\t");
    struct BinaryTreeNode *inorderPointer = inOrderTraversal(traverse);
    printf("\nPreorder Traversal:\t\t");
    struct BinaryTreeNode *preorderPointer = preOrderTraversal(inorderPointer);
    printf("\nPostorder Traversal:\t");
    struct BinaryTreeNode *traversalPointer = postOrderTraversal(preorderPointer);
    return rootPointer;
}

/**
 * Counts all the nodes available in the tree.
 * @param rootPointer
 * @return countOfNodes
 */
static int countAllEntries(struct BinaryTreeNode *rootPointer) {
    struct BinaryTreeNode *traverse = rootPointer;
    if (traverse == nullptr) return 0;
    else return 1 + countAllEntries(traverse->leftChild) + countAllEntries(traverse->rightChild);
}

/**
 * Counts all the internal nodes.
 */
static int countInternalEntries(struct BinaryTreeNode *rootPointer) {
    struct BinaryTreeNode *traverse = rootPointer;
    if (traverse == nullptr) return 0;
    else if (traverse->leftChild != nullptr || traverse->rightChild != nullptr)
        return 1 + countInternalEntries(traverse->leftChild) + countInternalEntries(traverse->rightChild);
    else return 0;
}

/**
 * Counts all the internal nodes.
 */
static int countExternalEntries(struct BinaryTreeNode *rootPointer) {
    struct BinaryTreeNode *traverse = rootPointer;
    if (traverse == nullptr) return 0;
    else if (traverse->leftChild == nullptr && traverse->rightChild == nullptr) return 1;
    else return countExternalEntries(traverse->leftChild) + countExternalEntries(traverse->rightChild);
}

/**
 * Maximum between two numbers.
 */
static int maxOf(int x, int y) {
    return x > y ? x : y;
}

/**
 * Calculates the height of the binary tree.
 */
static int heightOfBinaryTree(struct BinaryTreeNode *rootPointer) {
    struct BinaryTreeNode *traverse = rootPointer;
    if (traverse == nullptr) return 0;
    else {
        int leftHeight = heightOfBinaryTree(traverse->leftChild);
        int rightHeight = heightOfBinaryTree(traverse->rightChild);
        return 1 + maxOf(leftHeight, rightHeight);
    }
}

/**
 * Count all the entries.
 */
static struct BinaryTreeNode *countEntries(struct BinaryTreeNode *rootPointer) {
    struct BinaryTreeNode *traverse = rootPointer;
    /**
     * All nodes count.
     */
    int nodesCount = countAllEntries(traverse);
    printf("\n1. All the available entries \t\t= %4d.", nodesCount);
    /**
     * Count internal nodes.
     */
    traverse = rootPointer;
    int internalNodes = countInternalEntries(traverse);
    printf("\n2. All the internal node entries \t= %4d.", internalNodes);
    /**
     * Count external nodes.
     */
    traverse = rootPointer;
    int externalNodes = countExternalEntries(traverse);
    printf("\n3. All the external node entries \t= %4d.", externalNodes);
    /**
     * Count height of the binary tree.
     */
    traverse = rootPointer;
    int height = heightOfBinaryTree(traverse);
    printf("\n4. Height of the binary tree \t\t= %4d.", height);
    return rootPointer;
}

/**
 * Main Function, program starts from here.
 * @return 1 with successful operation.
 */
int main() {
    struct BinaryTreeNode *root = nullptr;
    while (TRUE) {
        int choice = displayMenu();
        switch (choice) {
            case 1:
                root = insertEntry(root, readDataValue());
                break;
            case 2:
                root = deleteEntry(root, readDataValue());
                break;
            case 3:
                root = allTraversals(root);
                break;
            case 4:
                root = countEntries(root);
                break;
            case 5:
                printf("\nGood Bye !");
                exit(1);
        }
    }
}
