# IS301-LibrarySystem-PACMAN5
This repository is for IS301 Major Projects Submission

--------------------------------------------------------------
User Manual - Library Management System
Login Information
Username: admin
Password: admin123
How to Run
Download or locate the file (.exe) click to run it:

library_system.exe

## Program Flow
After the administrator logs in, the main menu displays five options:

1. Book Management
2. Member Management
3. Borrowing Records
4. Reports
5. Exit

## Book Management
Selecting Book Management opens these options:

1. Add Book - user fills in book details. If successful, the system displays `Book Added.` If an error occurs, the user can retry.
2. Search Books - user enters a title or author. If successful, the system displays `Book Found.` If an error occurs, the user can retry.
3. Add Books - user fills in book details. If successful, the system displays `Book Added.` If an error occurs, the user can retry.
4. Delete Books - user enters/selects a book ID to delete. If successful, the system displays `Book Removed.` If an error occurs, the user can retry.
5. Update Quantity - user enters a book ID and the new quantity. If successful, the system displays `Quantity Updated.` If an error occurs, the user can retry.
4. Search Book - user enters title or author. If found, the system displays `Book Found.` If not found, the user can retry.
5. Display Books - system shows all books in inventory. If successful, the system displays `All Books Displayed.` If an error occurs, the user can retry.
0. Back to Main Menu - returns to the main menu.

## Member Management
Selecting Member Management opens these options:

1. Register Member - user fills in a registration form. If successful, the system displays `Member Registered.` If an error occurs, the user can retry.
2. View Member Details - system retrieves and displays member information. If successful, the system displays `Details Displayed.` If an error occurs, the user can retry.
3. Update Information - user edits member details. If successful, the system displays `Information Updated.` If an error occurs, the user can retry.
4. Delete Member - user enters/selects a member ID to delete. If successful, the system displays `Member Deleted.` If an error occurs, the user can retry.
0. Back to Main Menu - returns to the main menu.

## Borrowing Records
Selecting Borrowing Records opens these options:

1. Issue Books - user fills in borrowing details. If successful, the system displays `Book Issued.` If an error occurs, the user can retry.
2. Return Book - user fills in return details. If successful, the system displays `Book Returned.` If an error occurs, the user can retry.
3. Borrowing History - system retrieves and displays records. If successful, the system displays `User History Shown.` If an error occurs, the user can retry.
0. Back to Main Menu - returns to the main menu.

## Reports
Selecting Reports opens these options:

1. Generate Inventory - system generates inventory report. If successful, the system displays `Inventory Generated.` If an error occurs, the user can retry.
2. Member Activity - user enters a member ID and the system displays activity records. If successful, the system displays `Activities Shown.` If an error occurs, the user can retry.
0. Back to Main Menu - returns to the main menu.

## Exit
Selecting Exit from the main menu saves all data and ends the program.

## Data Files
- `data/book.txt` stores book information.
- `data/members.txt` stores member information.
- `data/borrow_records.txt` stores borrowing and return records.
- `data/inventory_report.txt` stores the generated inventory report.


## Back option
- Type `0` in any submenu to return to the main menu.
- Type `B` or `0` during any form/input to cancel the current action and go back.
- All user input is visible while typing.
