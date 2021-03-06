﻿# System and Device Programming
# Laboratory number 02



Note
----

Threads and advanced synchronization with threads
(semaphores, mutexes, ..., barriers).



Exercise 01 (A and B)
---------------------

Implement a *sequential* program in C that:
- Takes a single argument n from the command line
- Randomly generates two array (v1 and v2) of size n, and a matrix (mat) of
  dimension (n x n),
  All random values must be in the range [-0.5, 0.5]
- Evaluate the following product
  res = v1^T * mat * v2
  (where v1^T is the transpose of v1) in two steps, as it first computes
  v = v1^T * mat
  then
  res = v * v2
- Prints the result res.

For example, let us suppose that n=5, and v1, v2 and mat are the
following ones:

v1^T = [ -0.0613 -0.1184  0.2655  0.2952 -0.3131 ] 

mat  = [ -0.3424 -0.3581  0.1557  0.2577  0.2060	
          0.4706 -0.0782 -0.4643  0.2431 -0.4682
          0.4572  0.4157  0.3491  0.1078 -0.2231	
         -0.0146  0.2922  0.4340 -0.1555 -0.4029
          0.3003  0.4595  0.1787 -0.3288 -0.4656 ]

v2^T = [ -0.3235  0.1948 -0.1829  0.4502 -0.4656 ]

Then, the result of the computation is:

res = v1^T * mat * v2 = (v1^T * mat) * v2 = 0.0194

After the sequential program correctly computes the final result,
transform it into two *concurrent* programs using Pthreads.

Organize the version A of the concurrent program as follows:

- The main thread creates the arrays, the matrix, and it runs n threads.
  Then, it waits the termination of all n threads.
- Each thread i performs the product of the array v1^T with i-th row
  of mat, which produces the i-th element of vector v.
- When all threads have terminated their task, the main thread compute
  the final result as
  res = v * v2

Organize the version B of the concurrent program as version A, but
once v has been computed the final result (res = v * v2) is computed
by one of the created threads (not by the main threads), the last one
terminating its product operation,



Exercise 02
-----------

Given an array v of 2^n elements v[i], i.e.,

v = { v[0], v[1], ... , x[2^n − 1]}

its k-th prefix sum (the cumulative sum vector) is the sum of its first k+1
elements, i.e.,
v[0] + v[1] + ... + v[k]

Write a C program using Pthreads that:
* Receives an integer value n as argument of the command line
* Randomly generates an array v of 2^n integer elements in the range [1-9]
* Computes the prefix sum of v as follows.

For an array v of 2^n elements, it is possible to compute all values of
the prefix sum in n steps, by means of 2^n−1 concurrent threads, each
associated to an array element.

For example for n=3 and 2^3 = 8 elements, each step consists of each
thread taking two elements, and computing a result:
* In the first step each thread computes the sums of adjacent elements
  (i.e., gap = 1=2^0). 
* In the second step, each thread computes the sums of the elements
  that are 2 elements away (i.e., gap = 2 = 2^1).
* In the third step, each thread computes the sums of the elements
  that are 4 elements away (i.e., gap = 4 = 2^2).
After 3 steps, all sum prefix values are computed.

In general, if we have 2^n elements in v, step i computes the sums of
elements that are 2^(i-1) elements away.
After n steps, all cumulative sum values are computed.

For example, let us suppose the program is run as:

> cumulative_sum  3

It should compute (and eventually display) the following:

Initial array v:  2  4  6  1  3  5  8  7
v after step 1 :  2  6 10  7  4  8 13 15
                  Computed as: v[0]=v[0], v[1]=v[0]+v[1],
		               v[2]=v[1]+v[2], etc., v[n-1]=v[n-2]+v[n-1]
v after step 2 :  2  6 12 13 14 15 17 23
                  Computed as: v[0]=v[0], v[1]=v[1], v[2]=v[0]+v[2],
                               v[3]=v[1]+v[3], etc., v[n-1]=v[n-3]+v[n-1]
v after step 3 :  2  6 12 13 16 21 29 36
                  Computed as: v[0]=v[0], etc., v[3]=v[4], v[4]=v[0]+v[4],
                               v[5]=v[1]+v[5], etc., v[n-1]=v[n-5]+v[n-1]

Please notice that:

1. The main thread allocates, fills, and print the initial content of
   array v

2. All threads are initially created by the main thread, they have all
   the same code, and must synchronize their activity according to the
   steps that have been illustrated, exploiting maximum concurrency.

3. The array v must be updated in place, i.e., you cannot allocate
   auxiliary arrays.

4. Each thread must loop for no more than n times (the number of
   steps) before exiting.

5. Some threads terminate before the n-th step.
   In particular thread i terminates after step i, with i in range [1–n].

6. The main thread prints immediately the value in x[0], then it waits
   the termination of each threads i, in order of creation, and
   immediately prints the value stored in x[i].


Suggestions
-----------
* First design and write the pseudo-code of a solution excluding rule 5.
* Then, update your solution including rule 5.
  Please notice that:
  - if you refer to x[i-gap], index i-gap must be non negative
  - you must properly manage a variable that stores the number of
    active threads, which must be decremented according to rule 5.
