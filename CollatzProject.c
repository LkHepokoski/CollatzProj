/* ----------------------------------------------------------------
 *    File: CollatzProject.c
 *  Author: Luke Hepokoski & Jose Suarez
 *   Class: COP 4610 Summer 2023
 *   Panther IDS: 6446285 &
 * Purpose: Write a program to generate a sequence in child process
 * ---------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>



void collatz_sequence(int n, int child_num) {
    while (n != 1) {
        printf("Child %d: %d\n", child_num, n);

        if (n % 2 == 0)
            n = n / 2;
        else
            n = (3 * n) + 1;
    }

    printf("Child %d: 1\n", child_num);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <number>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    int n_plus_4 = n + 4;

    if (n <= 0 || n >= 40) {
        printf("Number must be greater than zero and less than 40.\n");
        return 1;
    }

    pid_t pid1, pid2;

    pid1 = fork();
    if (pid1 == 0) {
        // Child process 1
        collatz_sequence(n, 1);
        return 0;
    } else if (pid1 < 0) {
        printf("Failed to fork child process 1.\n");
        return 1;
    }

    pid2 = fork();
    if (pid2 == 0) {
        // Child process 2
        collatz_sequence(n_plus_4, 2);
        return 0;
    } else if (pid2 < 0) {
        printf("Failed to fork child process 2.\n");
        return 1;
    }

    // Parent process
    int status;
    wait(&status);
    wait(&status);

    return 0;
}