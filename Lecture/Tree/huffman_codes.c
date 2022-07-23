/**
 * Huffman Tree Implementation and Code Generation.
 * The idea: highest frequent item gets the shortest code.
 *
 * 1. Read a text string from a function.
 * 2. Split them into characters and count the frequency.
 * 3. Sort the frequency table in the ascending orders of frequencies.
 * 4. Build the Huffman tree starting from lowest frequent character.
 * 5. Finally display the generated code with pre-order traversal:
 *    a. In left traversal, add "0" in the code.
 *    b. In right traversal, add "1" in the code.
 *
 * By Santa Basnet.
 * Everest Engineering College.
 * Date: 2021-12-07
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_FREQUENCY 1
#define MAX_ENTRY 26
#define LEFT_PATH "0"
#define RIGHT_PATH "1"

/** Define the Boolean Type **/
typedef enum {
    FALSE, TRUE
} Boolean;

/** Enum for Search Result. **/
typedef enum {
    NOT_FOUND = -1, FOUND = 1
} SearchResult;

/** Represent the character and its frequency. **/
typedef struct CharacterNode {
    int chEntry;
    int frequency;
} CharacterInfo;

/** Huffman Node Representation **/
typedef struct HuffmanNode {
    CharacterInfo data;
    struct HuffmanNode *left;
    struct HuffmanNode *right;
} HuffmanTree;

/**
 * Represent the Huffman tree status.
 */
struct HuffmanTreeStatus{
    /** All Nodes **/
    CharacterInfo allNodes[MAX_ENTRY];
    int entryCount;
    int entryIteratorCount;
    HuffmanTree *root;
} treeStatus;

/** Initialize tree status **/
void initHuffmanTreeStatus(){
    treeStatus.entryCount = 0;
    treeStatus.entryIteratorCount = 0;
    treeStatus.root = NULL;
}

/** Display the node entry **/
void displayCharacterInfo(CharacterInfo node) {
    printf("[%c -> %d] -> ", node.chEntry, node.frequency);
}

/**
 * Display Linked List of characters and their frequency.
 */
void displayList(const char *message) {
    printf("\n%s: ", message);
    for (int i = 0; i < treeStatus.entryCount; i++)
        displayCharacterInfo(treeStatus.allNodes[i]);
}

/** Take input as constant character pointer **/
const char *inputText() {
    return "ABBBBBBAAAACDEFGGGGH";
}

/**
 * Insert operation of the character list.
 */
void insertCharacter(char ch) {
    int search = NOT_FOUND;
    for (int i = 0; i < treeStatus.entryCount; i++) {
        if (ch == treeStatus.allNodes[i].chEntry) {
            search = i;
            break;
        }
    }
    if (search == NOT_FOUND) {
        treeStatus.allNodes[treeStatus.entryCount].chEntry = (int) ch;
        treeStatus.allNodes[treeStatus.entryCount++].frequency = DEFAULT_FREQUENCY;
    } else treeStatus.allNodes[search].frequency++;
}

/** Build Frequency Table **/
void buildFrequencyTable() {
    const char *text = inputText();
    while (*text != '\0') {
        insertCharacter(*text);
        text++;
    }
}

/** Sort Frequency Table, uses simple bubble sort algorithm. **/
void sortFrequencyTable() {
    for (int i = 0; i < treeStatus.entryCount - 1; i++) {
        for (int j = i + 1; j < treeStatus.entryCount; j++) {
            if (treeStatus.allNodes[i].frequency > treeStatus.allNodes[j].frequency) {
                CharacterInfo tNode;
                tNode.chEntry = treeStatus.allNodes[i].chEntry;
                tNode.frequency = treeStatus.allNodes[i].frequency;
                treeStatus.allNodes[i].chEntry = treeStatus.allNodes[j].chEntry;
                treeStatus.allNodes[i].frequency = treeStatus.allNodes[j].frequency;
                treeStatus.allNodes[j].chEntry = tNode.chEntry;
                treeStatus.allNodes[j].frequency = tNode.frequency;
            }
        }
    }
}

/** Empty Character Info. **/
CharacterInfo emptyCharInfo() {
    CharacterInfo emptyInfo;
    emptyInfo.chEntry = '\0';
    emptyInfo.frequency = 0;
    return emptyInfo;
}

/** Checks if the character info is empty valued or not. **/
Boolean isEmptyCharInfo(CharacterInfo characterInfo) {
    return characterInfo.frequency <= 0 || characterInfo.chEntry == '\0';
}

/**
 * Returns the character info from input data.
 */
CharacterInfo getCharInfo() {
    CharacterInfo result;
    if (treeStatus.entryIteratorCount > treeStatus.entryCount) result = emptyCharInfo();
    else result = treeStatus.allNodes[treeStatus.entryIteratorCount];
    treeStatus.entryIteratorCount++;
    return result;
}

/** Display Huffman Node **/
void displayNode(HuffmanTree *newRoot, char *code) {
    printf("\t{[%d(%c) -> %d] %s}\n", newRoot->data.chEntry, newRoot->data.chEntry, newRoot->data.frequency, code);
}

/** Build Huffman Node from the character info. **/
struct HuffmanNode *buildHuffmanNode(CharacterInfo characterInfo) {
    struct HuffmanNode *node = (struct HuffmanNode *) malloc(sizeof(struct HuffmanNode));
    node->data = characterInfo;
    node->left = NULL;
    node->right = NULL;
    return node;
}

/** Build accumulated node with root and the given character info. **/
struct HuffmanNode *accumulatedNode(HuffmanTree *root, CharacterInfo characterInfo) {
    CharacterInfo newInfo;
    newInfo.frequency = root->data.frequency + characterInfo.frequency;
    newInfo.chEntry = root->data.chEntry + characterInfo.chEntry;
    HuffmanTree *newNode = buildHuffmanNode(newInfo);
    return newNode;
}

/** Insert Character Info to Huffman Tree **/
void insertCharacterInfo(CharacterInfo characterInfo) {
    if (treeStatus.root == NULL) {
        treeStatus.root = buildHuffmanNode(characterInfo);
        treeStatus.root->left = buildHuffmanNode(characterInfo);
    } else if (treeStatus.root->right == NULL) {
        treeStatus.root->right = buildHuffmanNode(characterInfo);
        treeStatus.root->data.frequency += treeStatus.root->right->data.frequency;
        treeStatus.root->data.chEntry += treeStatus.root->right->data.chEntry;
    } else {
        HuffmanTree *newRoot = accumulatedNode(treeStatus.root, characterInfo);
        newRoot->left = buildHuffmanNode(characterInfo);
        newRoot->right = treeStatus.root;
        treeStatus.root = newRoot;
    }
}

/** Build Huffman Tree **/
void buildHuffmanTree() {
    treeStatus.entryIteratorCount = 0;
    CharacterInfo characterInfo = getCharInfo();
    while (!isEmptyCharInfo(characterInfo)) {
        insertCharacterInfo(characterInfo);
        characterInfo = getCharInfo();
    }
}

/** Checks if the character entry is the coded candidate or not **/
Boolean isPresent(int ch) {
    for (int count = 0; count < treeStatus.entryCount; count++) {
        if (treeStatus.allNodes[count].chEntry == ch) return TRUE;
    }
    return FALSE;
}

/** Display Build Huffman Tree **/
void displayHuffmanCodes(HuffmanTree *givenRoot, char *code) {
    HuffmanTree *tRoot = givenRoot;
    if (tRoot != NULL) {
        if (isPresent(tRoot->data.chEntry)) displayNode(tRoot, code);

        char *newLCode = (char *) malloc((sizeof(char) * strlen(code)) + 1);
        strcpy(newLCode, code);
        strcat(newLCode, LEFT_PATH);
        displayHuffmanCodes(tRoot->left, newLCode);

        char *newRCode = (char *) malloc((sizeof(char) * strlen(code)) + 1);
        strcpy(newRCode, code);
        strcat(newRCode, RIGHT_PATH);
        displayHuffmanCodes(tRoot->right, newRCode);
    }
}

int main() {
    /** Input Text **/
    printf("Input Text : %s", inputText());

    /** Build Frequency Table **/
    buildFrequencyTable();
    displayList("1. Frequency Table");
    sortFrequencyTable();
    displayList("2. Sorted Frequency Table");
    printf("\n");

    /** Build Huffman Tree **/
    buildHuffmanTree();

    /** Display Build Huffman Tree **/
    printf("\nCoded Output : \n");
    char code[] = "";
    displayHuffmanCodes(treeStatus.root, code);

    return 0;
}

/**
 * Output:
 * Input Text : ABBBBBBAAAACDEFGGGGH
 * 1. Frequency Table: [A -> 5] -> [B -> 6] -> [C -> 1] -> [D -> 1] -> [E -> 1] -> [F -> 1] -> [G -> 4] -> [H -> 1] ->
 * 2. Sorted Frequency Table: [C -> 1] -> [D -> 1] -> [E -> 1] -> [F -> 1] -> [H -> 1] -> [G -> 4] -> [A -> 5] -> [B -> 6] ->

 * Coded Output :
 *	{[66(B) -> 6] 0}
 *	{[65(A) -> 5] 10}
 *	{[71(G) -> 4] 110}
 *	{[72(H) -> 1] 1110}
 *	{[70(F) -> 1] 11110}
 *	{[69(E) -> 1] 111110}
 *	{[67(C) -> 1] 1111110}
 *	{[68(D) -> 1] 1111111}
 *
*/