/**
 * Recursion Example.
 * 1. Normal Case.
 * 2. Tail Recursion.
 *
 * By Santa Basnet
 * Everest Engineering College.
 * Date: 2021-
 */

#include <cstdio>

/**
 * Recursive Definition for Fibonacci Series.
 * @param n
 * @return nth item of the fibonacci series.
 */
long fibonacci(long n) {
    if (n <= 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

/**
 * Helper function for tail call optimization.
 */
long fibonacciGo(long n, long first, long second){
     if(n == 0) return first;
     else if(n == 1) return second;
     else return fibonacciGo(n-1, second, first + second);
}

/**
 * Fibonacci recursion with Tail call optimization.
 * @param n
 * @return nth item of the fibonacci series.
 */
long fibonacciTail(long n) {
    return fibonacciGo(n, 0, 1);
}


/**
 * Program starts from here.
 * @return 1 with successful execution.
 */
int main() {
    long n;
    printf("\nInput n: ");
    scanf("%ld", &n);
    printf("\n%ldth fibonacci number: %ld", n, fibonacciTail(n));
    return 1;
}