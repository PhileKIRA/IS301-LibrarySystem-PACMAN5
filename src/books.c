#include <stdio.h>
#include <string.h>
#include "books.h"
#include "filehandling.h"

int displayAllBooks(Book books[], int count) {
    int i;
    if (count == 0) {
        printf("Error: No books available. Please retry after adding books.\n");
        return 0;
    }

    printf("\n%-10s %-30s %-20s %-15s %-6s %-8s %-12s\n", "BookID", "Title", "Author", "Genre", "Year", "Qty", "Status");
    printf("-----------------------------------------------------------------------------------------------------------\n");
    for (i = 0; i < count; i++) {
        printf("%-10s %-30s %-20s %-15s %-6d %-8d %-12s\n",
               books[i].bookID, books[i].title, books[i].author, books[i].genre,
               books[i].yearPublished, books[i].quantity,
               books[i].quantity > 0 ? "Available" : "Unavailable");
    }
    return 1;
}

int findBookByID(Book books[], int count, const char *bookID) {
    int i;
    for (i = 0; i < count; i++) {
        if (strcmp(books[i].bookID, bookID) == 0) return i;
    }
    return -1;
}

int searchBook(Book books[], int count) {
    char keyword[MAX_TEXT];
    int i, found = 0;

    if (count == 0) {
        printf("Error: No books available to search. Please retry after adding books.\n");
        return 0;
    }

    if (!readTextOrBack("Enter title or author to search: ", keyword, sizeof(keyword))) return 0;

    if (strlen(keyword) == 0) {
        printf("Error: Search criteria cannot be empty. Please retry.\n");
        return 0;
    }

    for (i = 0; i < count; i++) {
        if (strstr(books[i].title, keyword) != NULL || strstr(books[i].author, keyword) != NULL) {
            if (!found) printf("\nSearch results:\n");
            printf("%s | %s | %s | %s | %d | Qty: %d\n",
                   books[i].bookID, books[i].title, books[i].author,
                   books[i].genre, books[i].yearPublished, books[i].quantity);
            found = 1;
        }
    }

    if (!found) {
        printf("Error: Book not found. Please retry.\n");
        return 0;
    }
    return 1;
}

int addBook(Book books[], int *count) {
    Book newBook;

    if (*count >= MAX_BOOKS) {
        printf("Error: Book storage is full. Please retry after removing old records.\n");
        return 0;
    }

    if (!readTextOrBack("Enter Book ID: ", newBook.bookID, sizeof(newBook.bookID))) return 0;

    if (strlen(newBook.bookID) == 0 || findBookByID(books, *count, newBook.bookID) != -1) {
        printf("Error: Invalid or duplicate Book ID. Please retry.\n");
        return 0;
    }

    if (!readTextOrBack("Enter Title: ", newBook.title, sizeof(newBook.title))) return 0;

    if (!readTextOrBack("Enter Author: ", newBook.author, sizeof(newBook.author))) return 0;

    if (!readTextOrBack("Enter Genre: ", newBook.genre, sizeof(newBook.genre))) return 0;

    if (!readIntOrBack("Enter Year Published: ", &newBook.yearPublished)) return 0;

    if (!readIntOrBack("Enter Quantity: ", &newBook.quantity)) return 0;

    if (strlen(newBook.title) == 0 || strlen(newBook.author) == 0 || strlen(newBook.genre) == 0 || newBook.quantity < 0) {
        printf("Error: Book details are incomplete or invalid. Please retry.\n");
        return 0;
    }

    books[*count] = newBook;
    (*count)++;
    return 1;
}

int updateBookQuantity(Book books[], int count) {
    char bookID[20];
    int index;
    int newQuantity;

    if (count == 0) {
        printf("Error: No books available to update. Please retry after adding books.\n");
        return 0;
    }

    if (!readTextOrBack("Enter Book ID to update quantity: ", bookID, sizeof(bookID))) return 0;

    index = findBookByID(books, count, bookID);
    if (index == -1) {
        printf("Error: Book not found. Please retry.\n");
        return 0;
    }

    printf("Current quantity for %s is %d.\n", books[index].title, books[index].quantity);
    if (!readIntOrBack("Enter new quantity: ", &newQuantity)) return 0;

    if (newQuantity < 0) {
        printf("Error: Quantity cannot be negative. Please retry.\n");
        return 0;
    }

    books[index].quantity = newQuantity;
    return 1;
}

int removeBook(Book books[], int *count) {
    char bookID[20];
    int index, i;

    if (!readTextOrBack("Enter Book ID to remove: ", bookID, sizeof(bookID))) return 0;

    index = findBookByID(books, *count, bookID);
    if (index == -1) {
        printf("Error: Book not found. Please retry.\n");
        return 0;
    }

    for (i = index; i < *count - 1; i++) books[i] = books[i + 1];
    (*count)--;
    return 1;
}

int generateInventoryReport(Book books[], int count, const char *filename) {
    FILE *fp = fopen(filename, "w");
    int i;

    if (fp == NULL) {
        printf("Error: Could not create inventory report. Please retry.\n");
        return 0;
    }

    fprintf(fp, "LIBRARY INVENTORY REPORT\n");
    fprintf(fp, "========================================\n\n");

    for (i = 0; i < count; i++) {
        fprintf(fp, "BookID: %s\n", books[i].bookID);
        fprintf(fp, "Title: %s\n", books[i].title);
        fprintf(fp, "Author: %s\n", books[i].author);
        fprintf(fp, "Genre: %s\n", books[i].genre);
        fprintf(fp, "Year Published: %d\n", books[i].yearPublished);
        fprintf(fp, "Quantity: %d\n", books[i].quantity);
        fprintf(fp, "Availability Status: %s\n", books[i].quantity > 0 ? "Available" : "Unavailable");
        fprintf(fp, "----------------------------\n");
    }

    fclose(fp);
    return 1;
}

