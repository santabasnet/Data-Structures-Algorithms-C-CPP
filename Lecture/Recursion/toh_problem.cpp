/**
 * Tower of Hanoi program demonstration with Recursion.
 *
 * There are three rods exists and on rod contains 'n' numbers
 * of disks with different sizes but are placed in orders following
 * that a smaller disk cannot be place below the larger disk.
 *
 * Problem: We require to transfer all the initialized disk to the
 * other one by preserving the same rule with utilizing three disks.
 *
 * By Santa Basnet
 * Everest Engineering College.
 * Date: 2021-11-30
 */

#include <cstdio>

/**
 * TOH function prototype.
 */
void towerOfHanoi(int, char, char, char);

/**
 * Main starts here.
 * @return 1 with successful termination.
 */
int main() {
    towerOfHanoi(4, 'A', 'B', 'C');
    return 1;
}

/**
* Recursive implementation of TOH problem.
*/
void towerOfHanoi(int noOfDisks, char firstRod, char secondRod, char thirdRod) {
    if (noOfDisks == 1) {
        printf("Disk plate 1 moved from %c to %c. \n", firstRod, thirdRod);
        return;
    }
    towerOfHanoi(noOfDisks - 1, firstRod, thirdRod, secondRod);
    printf("Disk plate %d moved from %c to %c. \n", noOfDisks, firstRod, thirdRod);
    towerOfHanoi(noOfDisks - 1, secondRod, firstRod, thirdRod);
}