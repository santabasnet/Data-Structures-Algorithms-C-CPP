/**
 * B-Tree.
 *
 * M-Way Search Tree: its a search tree that can have (m-1) keys and m children.
 * As an example: binary search tree is a 2-Way search tree.
 *
 * Is a self balancing M-Way search tree with the following constraints:
 * 1. Minimum of Ceiling(m/2) children.
 * 2. A root node can have minimum 2 children(1 key).
 * 3. All leaf nodes should have in the same level.
 * 4. The tree creation process follows bottom-up approach.
 *
 * An Example: create a B-tree of order m = 4 with the following values.
 *  10, 20, 40, 50, 60, 70, 80, 30, 35, 5 and 15.
 *
 * a. Insert 10.
 *
 *      [|10|]
 *
 * b. Insert 20 and 40.
 *
 *      [|10|20|40]
 *
 * c. Insert 50.
 *      In this is case there is no space to insert 50. Already 3 keys are there
 *      in the node of m=4 degree B-tree.
 *
 *      In this case we split the node after inserting 50 in the existing node.
 *
 *      [10|20|40|50], split from median position. We choose, right element called
 *      left biased tree. We can choose left element if you prefer, called left
 *      biased tree, i.e. being said, it have more keys in the left sub tree.
 *
 *              [|40|]
 *            /       \
 *      [|10|20|]       [|50|]
 *
 * d. Insert 60 and 70.
 *
 *
 *              [|40|]
 *            /       \
 *      [|10|20|]       [|50|60|70|]
 *
 * e. Insert 80.
 *
 *              [|40|]
 *            /       \
 *      [|10|20|]       [|50|60|70|80], No space, then split it.
 *
 *                  [|40|70|]
 *                 /     |    \
 *        [|10|20|]  [|50|60|] [|80|]
 *
 * f. Insert 30.
 *
 *                  [|40|70|]
 *                 /     |    \
 *        [|10|20|30]  [|50|60|] [|80|]
 *
 *
 * g. Insert 35.
 *
 *                   [|40|70|]
 *                 /     |      \
 *      [|10|20|30|35|] [|50|60|] [|80|]  No space, then split it.
 *
 *                   [|30|40|70|]
 *               /     /   |      \
 *       [|10|20|] [|35|] [|50|60|] [|80|]
 *
 * h. Insert 5.
 *
 *                     [|30|40|70|]
 *                 /     /   |      \
 *      [|5|10|20|] [|35|] [|50|60|] [|80|]
 *
 * i. Insert 15.
 *
 *
 *                   [|30|40|70|]
 *                 /     /   |      \
 *      [|5|10|15|20|] [|35|] [|50|60|] [|80|] not possible, key full, then split it.
 *
 *                  [|15|30|40|70|]    , key full, not possible.
 *              /    /     /   |      \
 *      [|5|10|] [|20|] [|35|] [|50|60|] [|80|]
 *
 *
 *                  [|40|]
 *                 /       \
 *        [|15|30|]        [|70|]
 *       /    |    \        |     \
 * [|5|10|] [|20|] [|35|] [|50|60|] [|80|]
 *
 *  Grows upto level 3. Completed.
 *
 *
 *  B+ trees: Builds a multi-level tree.
 *  -------------
 *  a. Record pointers are placed in the leaf nodes only.
 *  b. Leaf nodes are in same level and form a linked list, becomes dense index.
 *  c. Leaf nodes can have copy of the record pointers from their parents.
 *
 *
 *                    [|40|]
 *                 /           \
 *        [|15|30|]            [|70|]
 *      /    |    \               \          \
 * [|5|10|]->[|15|20|]->[30|35|]->[40|50|60|]->[70|80|]
 *
 *
 * Everest Engineering College.
 * Date: 2022/01/20
 */

/**
 * The Main function return 0 for successful outcome.
 * @return 0
 */
int main() {
    // Put your code here
    return 0;
}