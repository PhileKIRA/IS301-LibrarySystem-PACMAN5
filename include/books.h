#ifndef BOOKS_H
#define BOOKS_H

#define MAX_BOOKS 500
#define MAX_TEXT 100

typedef struct {
    char bookID[20];
    char title[MAX_TEXT];
    char author[MAX_TEXT];
    char genre[50];
    int yearPublished;
    int quantity;
} Book;

int displayAllBooks(Book books[], int count);
int findBookByID(Book books[], int count, const char *bookID);
int searchBook(Book books[], int count);
int addBook(Book books[], int *count);
int updateBookQuantity(Book books[], int count);
int removeBook(Book books[], int *count);
int generateInventoryReport(Book books[], int count, const char *filename);

#endif

