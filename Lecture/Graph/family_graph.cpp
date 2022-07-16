/**
 * Family Graph Representation.
 *
 * ---------------------------------------------------------------
 * Textual Description.
 * ---------------------------------------------------------------
 * 1. [Ram] hasFriend [Shyam].
 * 2. [Ram] hasFriend [Hari].
 * 3. [Ram] hasBrother [Laxman].
 * 4. [Laxman] hasBrother [Ram].
 * 5. [Dasharath] hasSonInLaw [Shyam].
 * 6. [Ram] isSonOf [Dasharath].
 * 7. [Laxman] isSonOf [Dasharath].
 * 8. [Dasharath] isFatherOf [Ram].
 * 9. [Dasharath] isFatherOf [Laxman]
 *----------------------------------------------------------------
 *
 * Idea:
 * v1 -> v2 -> v3 -> v4... [A linked list of vertices.]
 * v1 has: sonOf(v3) -> brotherOf(v5)
 *
 * Author: Santa
 * Date: 2021
 */

#include <malloc.h>
#include <cstring>

const int DEFAULT_COST = 1;
const int TRUE = 1;
const int FALSE = 0;

struct Relation {
    char label[16];
    int cost;
    struct Person *to;
    struct Relation *next;
};

struct Person {
    char name[16];
    struct Relation *adjacencyList;
    struct Person *next;
};

struct Family {
    struct Person *root;
    int vertexCount;
};

struct Family *family = nullptr;

void printPerson(struct Person *person) {
    printf(" [%s]-> ", person->name);
}

void printPersons() {
    if (family == nullptr) return;
    printf("\n");
    struct Person *traverse = family->root;
    while (traverse != nullptr) {
        printPerson(traverse);
        traverse = traverse->next;
    }
}

void printRelation(struct Relation *relation) {
    printf(" --|%s|-->[%s], ", relation->label, relation->to->name);
}

void printAdjacencyList(struct Person *pTraverse) {
    printPerson(pTraverse);
    struct Relation *relation = pTraverse->adjacencyList;
    while (relation != nullptr) {
        printRelation(relation);
        relation = relation->next;
    }
}

void displayGraph() {
    /**
     * Initialized Family Graph:
     */

    printf("\n1.Given Family Graph:\n");
    if (family == nullptr || family->root == nullptr) {
        printf("\nEmpty Family.");
        return;
    }

    struct Person *pTraverse = family->root;
    while (pTraverse != nullptr) {
        printAdjacencyList(pTraverse);
        printf("\n");
        pTraverse = pTraverse->next;
    }
}

/**
 * Checks if the person with the name is present or not.
 * The Core code implementation.
 */
struct Person *personByName(char *personName) {
    if (family == nullptr) return nullptr;
    struct Person *traverse = family->root;
    while (traverse != nullptr) {
        if (strcmp(traverse->name, personName) == 0) return traverse;
        traverse = traverse->next;
    }
    return nullptr;
}

/**
 * Checks if the person with the given is present or not.
 */
int isPersonPresent(char *personName) {
    return personByName(personName) == nullptr ? FALSE : TRUE;
}

/**
 * Checks if the person with the object is present or not.
 */
int isPersonPresent(struct Person *person) {
    return isPersonPresent(person->name);
}

/**
 * Checks if the relation name given between two members is
 * exists or not.
 */
int isRelationPresent(char *p1Name, char *relation, char *p2Name) {
    struct Person *person1 = personByName(p1Name);
    if (person1 == nullptr) return FALSE;
    struct Relation *tRelation = person1->adjacencyList;
    while (tRelation != nullptr) {
        if (strcmp(tRelation->label, relation) == 0 && strcmp(tRelation->to->name, p2Name) == 0) {
            return TRUE;
        }
        tRelation = tRelation->next;
    }
    return FALSE;
}

/**
 * Returns the index of the given member name to using in DFS.
 */
int memberIndex(char *memberName) {
    int index = 0;
    struct Person *traverse = family->root;
    while (traverse != nullptr) {
        if (strcmp(traverse->name, memberName) == 0) {
            return index;
        }
        index++;
        traverse = traverse->next;
    }
    return -1;
}

/**
 * Creates a vertex with given label and returns its pointer.
 */
struct Person *createVertex(char *name) {
    struct Person *newPerson = (struct Person *) malloc(sizeof(struct Person));
    strcpy(newPerson->name, name);
    newPerson->adjacencyList = nullptr;
    newPerson->next = nullptr;
    return newPerson;
}

/**
 * Creates a edge with given label, vertex and the cost,
 * finally it returns the relation pointer.
 */
struct Relation *createRelation(char *label, int cost, struct Person *shyam) {
    struct Relation *newRelation = (struct Relation *) malloc(sizeof(struct Relation));
    strcpy(newRelation->label, label);
    newRelation->cost = cost;
    newRelation->to = shyam;
    newRelation->next = nullptr;
    return newRelation;
}

/**
 * Adds a person to the family graph.
 * 1. If empty family, create and add to the root.
 * 2. If already exist, do not add.
 * 3. If not, traverse to the last vertex and add to family graph.
 */
void addPerson(struct Person *person) {
    if (family == nullptr) {
        family = (struct Family *) malloc(sizeof(struct Family));
        family->root = person;
        family->vertexCount = 1;
    } else if (!isPersonPresent(person)) {
        struct Person *traverse = family->root;
        while (traverse->next != nullptr) traverse = traverse->next;
        traverse->next = person;
        family->vertexCount++;
    }
}

/**
 * It adds a new relation to the graph.
 * @param relation
 */
void addRelation(struct Person *source, struct Relation *relation) {
    if (source->adjacencyList == nullptr) source->adjacencyList = relation;
    else {
        struct Relation *traverse = source->adjacencyList;
        while (traverse->next != nullptr) traverse = traverse->next;
        traverse->next = relation;
    }
}

void initFamilyGraph() {
    struct Person *ram = createVertex("Ram");
    struct Person *shyam = createVertex("Shyam");
    struct Person *laxman = createVertex("Laxman");
    struct Person *hari = createVertex("Hari");
    struct Person *dasharath = createVertex("Dasharath");
    //printPerson(dasharath);

    struct Relation *hasFriendShyam = createRelation("hasFriend", DEFAULT_COST, shyam);
    struct Relation *hasFriendHari = createRelation("hasFriend", DEFAULT_COST, hari);
    struct Relation *hasBrotherLaxman = createRelation("hasBrother", DEFAULT_COST, laxman);
    struct Relation *hasBrotherRam = createRelation("hasBrother", DEFAULT_COST, ram);
    struct Relation *hasSonInLawShyam = createRelation("sonInLaw", DEFAULT_COST, shyam);
    struct Relation *isSonOfDasharath = createRelation("sonOfDasharath", DEFAULT_COST, dasharath);
    struct Relation *isFatherOfRam = createRelation("fatherOf", DEFAULT_COST, ram);
    struct Relation *isFatherOfLaxman = createRelation("fatherOf", DEFAULT_COST, laxman);
    //printRelation(hasFriendHari);

    addPerson(ram);
    addPerson(shyam);
    addPerson(laxman);
    addPerson(hari);
    addPerson(dasharath);
    //printPersons();

    addRelation(ram, hasFriendShyam);
    addRelation(ram, hasFriendHari);
    addRelation(ram, hasBrotherLaxman);
    addRelation(laxman, hasBrotherRam);
    addRelation(dasharath, hasSonInLawShyam);
    addRelation(ram, isSonOfDasharath);
    addRelation(laxman, isSonOfDasharath);
    addRelation(dasharath, isFatherOfRam);
    addRelation(dasharath, isFatherOfLaxman);

}

/**
 * 2. Displays if the given vertex with name is present
 * in the Graph or not. (Family Member)
 */
void displayPersonCheck() {
    char memberName[16] = "Dasharath";
    int result = isPersonPresent(memberName);
    if (result) printf("\n2. Yes, the member %s is available.", memberName);
    else printf("\n2. No, the member %s is not available.", memberName);
}

/**
* 3. Check if the given relation is present with source
* and destination name.
*/
void displayRelationCheck() {
    char p1Name[16] = "Ram";
    char p2Name[16] = "Dasharath";
    char relation[16] = "sonOfDasharath";
    int result = isRelationPresent(p1Name, relation, p2Name);
    if (result) printf("\n3. Yes, the relation %s is available between %s and %s.", relation, p1Name, p2Name);
    else printf("\n3. No, the relation %s is not available between %s and %s.", relation, p1Name, p2Name);
}

/**
 * A recursive functions that performs DFS to find the path between
 * two given vertices.
 */
void displayPath(struct Person *root, char *sourceName, char *targetName, char *path, int *visitedVertex) {
    char newPath[256];
    strcpy(newPath, path);
    if (strlen(path) > 0) strcat(newPath, " --> ");
    strcat(newPath, sourceName);

    struct Relation *relation = root->adjacencyList;
    while (relation != nullptr) {
        if (strcmp(relation->to->name, targetName) == 0) {
            printf("\n\tFound: [%s --> %s]", newPath, targetName);
        } else {
            int index = memberIndex(relation->to->name);
            if (visitedVertex[index] != TRUE) {
                visitedVertex[index] = TRUE;
                displayPath(relation->to, relation->to->name, targetName, newPath, visitedVertex);
            }
        }
        relation = relation->next;
    }
}

/**
 * Displays all the relationship between two family members.
 */
void displayAllRelations() {
    //1. Initialize visited members.
    int visitedMembers[family->vertexCount];
    for (int i = 0; i < family->vertexCount; i++) visitedMembers[i] = FALSE;

    char sourceMember[16] = "Laxman";
    char targetMember[16] = "Shyam";

    printf("\n5. All the available relations: ");
    if (memberIndex(sourceMember) == -1) {
        printf("\nSource member is not available.");
        return;
    }

    if (memberIndex(targetMember) == -1) {
        printf("\nTarget member is not available.");
        return;
    }
    visitedMembers[memberIndex(sourceMember)] = TRUE;
    displayPath(personByName(sourceMember), sourceMember, targetMember, "", visitedMembers);
}

/**
 * Display the all the available relations of the given vertex.
 */
void displayPersonRelations() {
    char personName[16] = "Dasharath";
    struct Person *sPerson = personByName(personName);
    printf("\n4. All the available relations of \"%s\": [", personName);
    struct Relation *ePerson = sPerson->adjacencyList;
    while (ePerson != nullptr) {
        printf("%s, ", ePerson->label);
        ePerson = ePerson->next;
    }
    printf("]\n");
}

/**
 * Perform Graph Cleanup to make make memory free.
 */
void cleanupFamilyGraph() {
    if (family->root == nullptr) return;
    struct Person *vPerson = family->root;
    while (vPerson != nullptr) {
        struct Person *tPerson = vPerson;
        vPerson = vPerson->next;
        free(tPerson);
    }
}

/**
 * Program starts here.
 * @return 0 with successful output.
 */
int main() {
    initFamilyGraph();
    /**
     * 1. Display all the graph entities.
     */
    displayGraph();

    /**
     * 2. Check if the given vertex is present or not.
     */
    displayPersonCheck();

    /**
     * 3. Check if the given relation is present with source
     * and destination name.
     */
    displayRelationCheck();

    /**
     * Question 4. How many relations are exists for a given vertex ?
     */
    displayPersonRelations();

    /**
     * 5. Display all the available relations between two persons.
     */
    displayAllRelations();

    /**
     * Release the memory.
     */
    cleanupFamilyGraph();
    printf("\n");
    return 0;
}