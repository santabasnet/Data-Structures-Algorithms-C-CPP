/**
 * Recursion for Factorial with Tail Call Optimization.
 *
 * By: Santa Basnet
 * Everest Engineering college.
 * Date: 2021-11-30
 */

#include <cstdio>

/**
 * Factorial with Tail Call Recursion.
 */
long factorialGo(long number, long result) {
    if (number == 1) return result;
    else return factorialGo(number - 1, result * number);
}

/**
 * Factorial Function that calls to
 */
long factorial(long number) {
    return factorialGo(number, 1);
}

/**
 * Normal Factorial with Recursion.
 */
 long int factorialNormal(long int number){
     if (number == 1) return 1;
     else return number * factorialNormal(number - 1);
 }

/**
 * Main Function Starts Here with return 1 for successful exits.
 * @return 1.
 */
int main() {
    long value = 20;
    printf("\nFactorial of %ld is %ld.", value, factorial(value));
    return 1;
}