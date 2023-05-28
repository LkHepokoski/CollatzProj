/* ----------------------------------------------------------------
 * File: LukeHepokoski.c
 * Authors: Luke Hepokoski & Jose Suarez
 * Class: COP 4610 Summer 2023
 * Panther IDs: 6446285 & 6248985
 * Purpose: This program takes a single command-line argument,
 * which should be a positive integer less than 40.
 * It generates two child processes that calculate and print the
 * Collatz sequence for the given number and its incremented value.
 * The parent process waits for both child processes to complete
 * and then prints a completion message.
 * ---------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <number>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]); // converts console input string into int
    int n_plus_4 = n + 4;

    // checks if n is within valid range
    if (n <= 0 || n >= 40) {
        return 1; // exits if n is not within valid range
    }

    pid_t pid1, pid2; // declare process variables

    // forks 1st process to generate sequence
    pid1 = fork();
    if (pid1 == 0) {
        // Child process 1
        printf("From Child1, pid=%d init: number=%d\n", getpid(), n);

        // Collatz algorithm
        while (n != 1) {
            if (n % 2 == 0) // if n % 2 == 0 means n is even
                n = n / 2;
            else
                n = (3 * n) + 1; // if n is odd

            printf("From Child1: number=%d\n", n);
        }

        printf("From Child1, pid=%d Im done!\n", getpid());
        return 0;
    } else if (pid1 < 0) {
        return 1; // exits if process fails
    }
    // forks 2nd process to generate sequence
    pid2 = fork();
    if (pid2 == 0) {
        // Child process 2
        printf("From Child2, pid=%d init: number=%d\n", getpid(), n_plus_4);

        // Collatz algorithm
        while (n_plus_4 != 1) {
            if (n_plus_4 % 2 == 0) // if n % 2 == 0 means n is even
                n_plus_4 = n_plus_4 / 2;
            else
                n_plus_4 = (3 * n_plus_4) + 1; // if n is odd use odd algorithm

            printf("From Child2: number=%d\n", n_plus_4);
        }

        printf("From Child2, pid=%d Im done!\n", getpid());
        return 0;
    } else if (pid2 < 0) {
        return 1; // exits if process fails
    }

    // Parent process
    printf("This is the Parent waiting!\n");

    int status;
    wait(&status);
    wait(&status);

    printf("All my Children Complete\n");

    return 0;
}
