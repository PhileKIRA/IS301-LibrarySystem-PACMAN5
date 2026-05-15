#include <stdio.h>
#include "auth.h"
#include "books.h"
#include "members.h"
#include "borrowing.h"
#include "filehandling.h"
#include "menu.h"

#define BOOK_FILE "data/book.txt"
#define MEMBER_FILE "data/members.txt"
#define BORROW_FILE "data/borrow_records.txt"
#define REPORT_FILE "data/inventory_report.txt"

static void bookManagementMenu(Book books[], int *bookCount) {
    int choice;
    do {
        showBookManagementMenu();
        choice = getMenuChoice();
        switch (choice) {
            case 1:
                if (displayAllBooks(books, *bookCount)) printf("All Books Displayed.\n");
                break;
            case 2:
                if (searchBook(books, *bookCount)) printf("Book Found.\n");
                break;
            case 3:
                if (addBook(books, bookCount)) { saveBooks(books, *bookCount, BOOK_FILE); printf("Book Added.\n"); }
                break;
            case 4:
                if (removeBook(books, bookCount)) { saveBooks(books, *bookCount, BOOK_FILE); printf("Book Removed.\n"); }
                break;
            case 5:
                if (updateBookQuantity(books, *bookCount)) { saveBooks(books, *bookCount, BOOK_FILE); printf("Quantity Updated.\n"); }
                break;
            case 0:
                printf("Returning to main menu...\n");
                break;
            default:
                printf("Invalid option. Please retry.\n");
        }
    } while (choice != 0);
}

static void memberManagementMenu(Member members[], int *memberCount) {
    int choice;
    do {
        showMemberManagementMenu();
        choice = getMenuChoice();
        switch (choice) {
            case 1:
                if (registerMember(members, memberCount)) { saveMembers(members, *memberCount, MEMBER_FILE); printf("Member Registered.\n"); }
                break;
            case 2:
                if (displayMembers(members, *memberCount)) printf("Details Displayed.\n");
                break;
            case 3:
                if (updateMember(members, *memberCount)) { saveMembers(members, *memberCount, MEMBER_FILE); printf("Information Updated.\n"); }
                break;
            case 4:
                if (deleteMember(members, memberCount)) { saveMembers(members, *memberCount, MEMBER_FILE); printf("Member Deleted.\n"); }
                break;
            case 0:
                printf("Returning to main menu...\n");
                break;
            default:
                printf("Invalid option. Please retry.\n");
        }
    } while (choice != 0);
}

static void borrowingRecordsMenu(Book books[], int *bookCount, Member members[], int memberCount, BorrowRecord records[], int *recordCount) {
    int choice;
    do {
        showBorrowingRecordsMenu();
        choice = getMenuChoice();
        switch (choice) {
            case 1:
                if (issueBook(books, *bookCount, members, memberCount, records, recordCount)) {
                    saveBooks(books, *bookCount, BOOK_FILE);
                    saveBorrowRecords(records, *recordCount, BORROW_FILE);
                    printf("Book Issued.\n");
                }
                break;
            case 2:
                if (returnBook(books, *bookCount, records, *recordCount)) {
                    saveBooks(books, *bookCount, BOOK_FILE);
                    saveBorrowRecords(records, *recordCount, BORROW_FILE);
                    printf("Book Returned.\n");
                }
                break;
            case 3:
                if (displayBorrowRecords(records, *recordCount)) printf("User History Shown.\n");
                break;
            case 0:
                printf("Returning to main menu...\n");
                break;
            default:
                printf("Invalid option. Please retry.\n");
        }
    } while (choice != 0);
}

static void reportsMenu(Book books[], int bookCount, Member members[], int memberCount, BorrowRecord records[], int recordCount) {
    int choice;
    do {
        showReportsMenu();
        choice = getMenuChoice();
        switch (choice) {
            case 1:
                if (generateInventoryReport(books, bookCount, REPORT_FILE)) printf("Inventory Generated.\n");
                break;
            case 2:
                printf("Member Activity Form\n");
                if (displayMemberActivity(members, memberCount, records, recordCount)) printf("Activities Shown.\n");
                break;
            case 0:
                printf("Returning to main menu...\n");
                break;
            default:
                printf("Invalid option. Please retry.\n");
        }
    } while (choice != 0);
}

int main(void) {
    Book books[MAX_BOOKS];
    Member members[MAX_MEMBERS];
    BorrowRecord records[MAX_BORROWS];
    int bookCount, memberCount, recordCount;
    int choice;

    if (!login()) return 0;

    bookCount = loadBooks(books, BOOK_FILE);
    memberCount = loadMembers(members, MEMBER_FILE);
    recordCount = loadBorrowRecords(records, BORROW_FILE);

    do {
        showMainMenu();
        choice = getMenuChoice();
        switch (choice) {
            case 1: bookManagementMenu(books, &bookCount); break;
            case 2: memberManagementMenu(members, &memberCount); break;
            case 3: borrowingRecordsMenu(books, &bookCount, members, memberCount, records, &recordCount); break;
            case 4: reportsMenu(books, bookCount, members, memberCount, records, recordCount); break;
            case 5:
                saveBooks(books, bookCount, BOOK_FILE);
                saveMembers(members, memberCount, MEMBER_FILE);
                saveBorrowRecords(records, recordCount, BORROW_FILE);
                printf("Data saved. Program ended.\n");
                break;
            default: printf("Invalid option. Please retry.\n");
        }
    } while (choice != 5);
    return 0;
}

