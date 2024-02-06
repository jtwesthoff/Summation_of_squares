# Summation of Squares using Threads

This C program calculates the summation of squares of numbers using multiple threads. Each thread calculates the square of its assigned number, and the program computes the total summation of these squares.

## Features

- Utilizes pthreads library for multithreading capabilities.
- Uses mutexes for safe concurrent access to shared variables.
- The number of threads and the range of numbers can be adjusted by modifying the `NUM_THREADS` constant.

## How it Works

1. The program initializes a mutex to ensure safe access to the global accumulator variable.
2. It creates multiple threads, each responsible for calculating the square of a number within a specified range.
3. Each thread computes the square of its assigned number and updates the global accumulator with the result.
4. After all threads have finished their computations, the program outputs the total summation of squares.

## Usage

To compile the program, use the following command:

``` bash
gcc -o Summation_of_squares Summation_of_squares.c -pthread
```

To run the compiled program, execute the following command:

```bash
./Summation_of_squares
```

## Configuration

You can adjust the number of threads and the range of numbers by modifying the `NUM_THREADS` constant in the source code.

## Dependencies

- pthreads library (POSIX Threads)
