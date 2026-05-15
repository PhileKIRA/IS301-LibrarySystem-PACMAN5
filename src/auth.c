#include <stdio.h>
#include <string.h>
#include "auth.h"
#include "filehandling.h"

int login(void) {
    char username[30];
    char password[30];
    int attempts = 3;

    printf("========================================\n");
    printf(" Library Management System Login\n");
    printf("========================================\n");
   

    while (attempts > 0) {
        if (!readTextOrBack("Username: ", username, sizeof(username))) return 0;
        if (!readTextOrBack("Password: ", password, sizeof(password))) return 0;

        if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
            printf("Login successful. Welcome, Administrator.\n");
            return 1;
        }

        attempts--;
        printf("Invalid login. Attempts remaining: %d\n", attempts);
    }

    printf("Access denied. Program will close.\n");
    return 0;
}

