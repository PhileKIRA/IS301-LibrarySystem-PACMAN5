#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "filehandling.h"

void showMainMenu(void) {
    printf("\n========================================\n");
    printf(" LIBRARY MANAGEMENT SYSTEM\n");
    printf("========================================\n");
    printf("1. Book Management\n2. Member Management\n3. Borrowing Records\n4. Reports\n5. Exit Program\n");
    printf("----------------------------------------\n");
}
void showBookManagementMenu(void) {
    printf("\n========== BOOK MANAGEMENT ==========\n");
    printf("1. Display Books\n2. Search Books\n3. Add Books\n4. Delete Books\n5. Update Quantity\n0. Back to Main Menu\n");
    printf("Tip: Enter B or 0 inside any form to go back.\n");
    printf("------------------------------------\n");
}
void showMemberManagementMenu(void) {
    printf("\n========= MEMBER MANAGEMENT =========\n");
    printf("1. Register Member\n2. View Member\n3. Update Member\n4. Delete Member\n0. Back to Main Menu\n");
    printf("Tip: Enter B or 0 inside any form to go back.\n");
    printf("------------------------------------\n");
}
void showBorrowingRecordsMenu(void) {
    printf("\n========= BORROWING RECORDS =========\n");
    printf("1. Issue Books\n2. Return Books\n3. Borrowing History\n0. Back to Main Menu\n");
    printf("Tip: Enter B or 0 inside any form to go back.\n");
    printf("------------------------------------\n");
}
void showReportsMenu(void) {
    printf("\n============== REPORTS ==============\n");
    printf("1. Generate Inventory\n2. Member Activity\n0. Back to Main Menu\n");
    printf("Tip: Enter B or 0 inside any form to go back.\n");
    printf("------------------------------------\n");
}
int getMenuChoice(void) {
    char line[50];
    char *endptr;
    int choice;
    printf("Enter your choice: ");
    if (fgets(line, sizeof(line), stdin) == NULL) return -1;
    removeNewline(line);
    choice = (int)strtol(line, &endptr, 10);
    if (line[0] == '\0' || *endptr != '\0') return -1;
    return choice;
}

