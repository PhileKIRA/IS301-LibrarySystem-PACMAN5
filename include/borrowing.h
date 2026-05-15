#ifndef BORROWING_H
#define BORROWING_H

#include "books.h"
#include "members.h"

#define MAX_BORROWS 1000

typedef struct {
    char recordID[20];
    char bookID[20];
    char memberID[20];
    char borrowedDate[20];
    char returnDate[20];
    char status[20];
} BorrowRecord;

int issueBook(Book books[], int bookCount, Member members[], int memberCount, BorrowRecord records[], int *recordCount);
int returnBook(Book books[], int bookCount, BorrowRecord records[], int recordCount);
int displayBorrowRecords(BorrowRecord records[], int count);
int displayMemberActivity(Member members[], int memberCount, BorrowRecord records[], int recordCount);

#endif

