/**
 * Problem Find all the positive integers among x, y and z that makes
 * sum is equal to 5.
 * Author: Santa
 * Date: 2022-01-30
 * Everest Engineering College
 */

#include <cstdio>
#include <cstring>

const int UPPER_BOUND = 5;

/**
 * Algorithm 1: O(n^3)
 */
void algorithmNCubed() {
    for(int x = 0; x <= UPPER_BOUND; x ++)
        for(int y = 0; y <= UPPER_BOUND; y ++)
            for(int z = 0; z <= UPPER_BOUND; z ++)
                if(x + y + z == UPPER_BOUND)  printf("\n(%d, %d, %d)", x, y, z);

}

/**
 * Algorithm 2: O(n^2)
 */
void algorithmNSquared() {
    for(int x = 0; x <= UPPER_BOUND; x ++)
        for(int y = 0; y <= UPPER_BOUND; y ++){
            int z = UPPER_BOUND - (x + y);
            if(z >= 0)  printf("\n(%d, %d, %d)", x, y, z);
        }

}

/**
 * Main function starts here with success 0.
 * @return
 */
int main() {
    algorithmNCubed();
    printf("\n");
    algorithmNSquared();
    return 0;
}