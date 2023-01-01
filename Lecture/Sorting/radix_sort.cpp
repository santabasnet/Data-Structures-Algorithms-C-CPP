/**
 * Lab-Sheet - 7: Sorting Algorithms.
 *
 * Radix Sort: a non-comparative sorting algorithm, works based on their
 * digits radix. It uses grouping based on the digits places and ordering
 * the grouped elements together with previously ordered items.
 *
 * Example:
 *
 *  Data Input: 181 289 390 121 145 736 514 212
 *
 *  Identify the largest element: 736 and it has 3 digits. So, the loop runs
 *  upto 3 passes i.e. hundreds place.
 *
 *  Pass I: Sort on the basis of 0th place.
 *  -------------------------------------------------------------------------
 *  Bucket 0:   390
 *  Bucket 1:   181 121
 *  Bucket 2:   212
 *  Bucket 3:
 *  Bucket 4:   514
 *  Bucket 5:   145
 *  Bucket 6:   736
 *  Bucket 7:
 *  Bucket 8:
 *  Bucket 9:   289
 *
 *  Output:
 *              390 181 121 212 514 145 736 289
 *
 *  Pass II: Sort on the basis of 10th place.
 *  -------------------------------------------------------------------------
 *  Bucket 0:
 *  Bucket 1:   212 514
 *  Bucket 2:   121
 *  Bucket 3:   736
 *  Bucket 4:   145
 *  Bucket 5:
 *  Bucket 6:
 *  Bucket 7:
 *  Bucket 8:   181 289
 *  Bucket 9:   390
 *
 *  Output:
 *              212 514 121 736 145 181 289 390
 *
 *  Pass III: Sort on the basis of the 100th place.
 *  -------------------------------------------------------------------------
 *  Bucket 0:
 *  Bucket 1:   121 145 181
 *  Bucket 2:   212 289
 *  Bucket 3:   390
 *  Bucket 4:
 *  Bucket 5:   514
 *  Bucket 6:
 *  Bucket 7:   736
 *  Bucket 8:
 *  Bucket 9:
 *
 *  Output:
 *              121 145 181 212 289 390 514 736

 *
 * Time Complexity:
 *  1. Base Case: O(n+k): It happens if the data is already sorted.
 *  2. Average Case: O(nk): It happens if the data elements are randomized.
 *  3. Worst Case: O(nk): It happens if the data elements are in reverse ordered.
 *
 * By: Santa Basnet
 * Everest Engineering College.
 * Date: 2021-12-10
 */

int main() {

    return 0;
}