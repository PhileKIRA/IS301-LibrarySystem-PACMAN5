#include <stdio.h>
#include <string.h>
#include "borrowing.h"
#include "books.h"
#include "members.h"
#include "filehandling.h"

static int findRecordByID(BorrowRecord records[], int count, const char *recordID) {
    int i;
    for (i = 0; i < count; i++) {
        if (strcmp(records[i].recordID, recordID) == 0) return i;
    }
    return -1;
}

int issueBook(Book books[], int bookCount, Member members[], int memberCount, BorrowRecord records[], int *recordCount) {
    BorrowRecord record;
    int bookIndex, memberIndex;

    if (*recordCount >= MAX_BORROWS) {
        printf("Error: Borrow record storage is full. Please retry after clearing records.\n");
        return 0;
    }

    if (!readTextOrBack("Enter Record ID: ", record.recordID, sizeof(record.recordID))) return 0;

    if (strlen(record.recordID) == 0 || findRecordByID(records, *recordCount, record.recordID) != -1) {
        printf("Error: Invalid or duplicate Record ID. Please retry.\n");
        return 0;
    }

    if (!readTextOrBack("Enter Book ID: ", record.bookID, sizeof(record.bookID))) return 0;

    bookIndex = findBookByID(books, bookCount, record.bookID);
    if (bookIndex == -1) {
        printf("Error: Book not found. Please retry.\n");
        return 0;
    }

    if (books[bookIndex].quantity <= 0) {
        printf("Error: Book is currently unavailable. Please retry.\n");
        return 0;
    }

    if (!readTextOrBack("Enter Member ID: ", record.memberID, sizeof(record.memberID))) return 0;

    memberIndex = findMemberByID(members, memberCount, record.memberID);
    if (memberIndex == -1) {
        printf("Error: Member not found. Register the member first, then retry.\n");
        return 0;
    }

    if (!readTextOrBack("Enter Borrowed Date (YYYY-MM-DD): ", record.borrowedDate, sizeof(record.borrowedDate))) return 0;

    if (strlen(record.borrowedDate) == 0) {
        printf("Error: Borrowed date cannot be empty. Please retry.\n");
        return 0;
    }

    strcpy(record.returnDate, "N/A");
    strcpy(record.status, "Borrowed");

    records[*recordCount] = record;
    (*recordCount)++;
    books[bookIndex].quantity--;
    return 1;
}

int returnBook(Book books[], int bookCount, BorrowRecord records[], int recordCount) {
    char recordID[20];
    int recordIndex, bookIndex;

    if (!readTextOrBack("Enter Borrow Record ID: ", recordID, sizeof(recordID))) return 0;

    recordIndex = findRecordByID(records, recordCount, recordID);
    if (recordIndex == -1) {
        printf("Error: Borrow record not found. Please retry.\n");
        return 0;
    }

    if (strcmp(records[recordIndex].status, "Returned") == 0) {
        printf("Error: This book has already been returned. Please retry.\n");
        return 0;
    }

    if (!readTextOrBack("Enter Return Date (YYYY-MM-DD): ", records[recordIndex].returnDate, sizeof(records[recordIndex].returnDate))) return 0;

    if (strlen(records[recordIndex].returnDate) == 0) {
        printf("Error: Return date cannot be empty. Please retry.\n");
        return 0;
    }

    strcpy(records[recordIndex].status, "Returned");

    bookIndex = findBookByID(books, bookCount, records[recordIndex].bookID);
    if (bookIndex != -1) books[bookIndex].quantity++;

    return 1;
}

int displayBorrowRecords(BorrowRecord records[], int count) {
    int i;
    if (count == 0) {
        printf("Error: No borrowing history available. Please retry after borrowing a book.\n");
        return 0;
    }

    printf("\n%-10s %-10s %-10s %-15s %-15s %-10s\n", "RecordID", "BookID", "MemberID", "Borrowed", "Returned", "Status");
    printf("-------------------------------------------------------------------------------\n");
    for (i = 0; i < count; i++) {
        printf("%-10s %-10s %-10s %-15s %-15s %-10s\n",
               records[i].recordID, records[i].bookID, records[i].memberID,
               records[i].borrowedDate, records[i].returnDate, records[i].status);
    }
    return 1;
}

int displayMemberActivity(Member members[], int memberCount, BorrowRecord records[], int recordCount) {
    char memberID[20];
    int i, found = 0, memberIndex;

    if (memberCount == 0 || recordCount == 0) {
        printf("Error: No member activity available. Please retry after borrowing records exist.\n");
        return 0;
    }

    if (!readTextOrBack("Enter Member ID for activity report: ", memberID, sizeof(memberID))) return 0;

    memberIndex = findMemberByID(members, memberCount, memberID);
    if (memberIndex == -1) {
        printf("Error: Member not found. Please retry.\n");
        return 0;
    }

    printf("\nMember Activity for %s (%s)\n", members[memberIndex].name, members[memberIndex].memberID);
    printf("%-10s %-10s %-15s %-15s %-10s\n", "RecordID", "BookID", "Borrowed", "Returned", "Status");
    printf("----------------------------------------------------------------\n");

    for (i = 0; i < recordCount; i++) {
        if (strcmp(records[i].memberID, memberID) == 0) {
            printf("%-10s %-10s %-15s %-15s %-10s\n",
                   records[i].recordID, records[i].bookID, records[i].borrowedDate,
                   records[i].returnDate, records[i].status);
            found = 1;
        }
    }

    if (!found) {
        printf("Error: No activity records found for this member. Please retry.\n");
        return 0;
    }
    return 1;
}

