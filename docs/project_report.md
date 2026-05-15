# IS301 Structured Programming Project Report

## 1. Introduction
This project is a console-based Library Management System developed in the C programming language. The system allows administrators to manage books, members, and borrowing records. It uses text files to store data, which allows records to be saved and reused when the program is opened again.

## 2. Project Objectives
The objectives of this project are to:

- Develop a structured program to manage a library inventory.
- Apply file input and output operations using text files.
- Use control structures such as selection and repetition.
- Apply modular programming by separating the system into different source files and header files.
- Use arrays and structures to manage in-memory data.
- Practice debugging, testing, and documenting a complete C program.

## 3. Problem Analysis and Requirements
The system must allow the administrator to manage library records in a simple menu-driven interface. The main requirements are:

- Read book details from `books.txt`.
- Store books, members, and borrowing records in text files.
- Display all books.
- Search books by title or author.
- Add new books.
- Update book quantity.
- Generate an inventory report.
- Register and update members.
- Issue and return books.
- Maintain borrowing history.
- Handle errors such as invalid input, missing files, and duplicate IDs.

## 4. System Design

### 4.1 Main System Flow
1. Start program.
2. Display login screen.
3. Validate administrator username and password.
4. Load books, members, and borrowing records from text files.
5. Display the main menu.
6. Administrator selects an option.
7. The selected function is executed.
8. Updated data is saved to text files.
9. Program continues until the administrator chooses exit.

### 4.2 Menu Structure
The system menu contains the following options:

1. Display all books
2. Search book by title or author
3. Add new book
4. Update book quantity
5. Remove book
6. Register new member
7. View members
8. Update member information
9. Issue/borrow book
10. Return book
11. View borrowing records
12. Generate inventory report
0. Save and exit

### 4.3 Module Breakdown
| Module | Purpose |
|---|---|
| `main.c` | Controls program flow and connects all modules. |
| `auth.c/auth.h` | Handles administrator login. |
| `books.c/books.h` | Handles book display, search, add, update, delete, and report generation. |
| `members.c/members.h` | Handles member registration, viewing, and updating. |
| `borrowing.c/borrowing.h` | Handles book borrowing and returning. |
| `filehandling.c/filehandling.h` | Handles reading and writing text files. |
| `menu.c/menu.h` | Displays the system menu and reads menu choices. |
| `books.h` | Contains the `Book` structure and book function prototypes. |
| `members.h` | Contains the `Member` structure and member function prototypes. |
| `borrowing.h` | Contains the `BorrowRecord` structure and borrowing/report function prototypes. |

## 5. Data Structures

### 5.1 Book Structure
```c
typedef struct {
    char bookID[20];
    char title[100];
    char author[100];
    char genre[50];
    int yearPublished;
    int quantity;
} Book;
```

### 5.2 Member Structure
```c
typedef struct {
    char memberID[20];
    char name[100];
    char phone[30];
} Member;
```

### 5.3 Borrow Record Structure
```c
typedef struct {
    char recordID[20];
    char bookID[20];
    char memberID[20];
    char borrowedDate[20];
    char returnDate[20];
    char status[20];
} BorrowRecord;
```

## 6. Algorithms and Pseudocode

### 6.1 Main System Algorithm
```text
START
Display login screen
IF login is successful THEN
    Load books from books.txt
    Load members from members.txt
    Load borrow records from borrow_records.txt
    REPEAT
        Display menu
        Read user choice
        Perform selected operation
        Save updated records
    UNTIL user selects exit
ELSE
    Display access denied
END IF
STOP
```

### 6.2 Login Pseudocode
```text
SET attempts = 3
WHILE attempts > 0
    READ username
    READ password
    IF username = admin AND password = admin123 THEN
        Display login successful
        Return true
    ELSE
        Reduce attempts by 1
        Display invalid login
    END IF
END WHILE
Return false
```

### 6.3 Book Management Pseudocode
```text
FOR display all books:
    IF book count is zero THEN
        Display no books available
    ELSE
        FOR each book
            Display book details
        END FOR
    END IF

FOR add book:
    READ book ID
    IF book ID already exists THEN
        Display duplicate error
    ELSE
        READ title, author, genre, year, quantity
        Add book to array
        Save books to file
    END IF

FOR update quantity:
    READ book ID
    Search for book ID
    IF found THEN
        READ new quantity
        Update quantity
        Save books to file
    ELSE
        Display book not found
    END IF
```

### 6.4 Member Management Pseudocode
```text
FOR register member:
    READ member ID
    IF member ID exists THEN
        Display duplicate error
    ELSE
        READ member name and phone
        Add member to array
        Save members to file
    END IF

FOR update member:
    READ member ID
    IF member exists THEN
        READ new name and phone
        Update member record
        Save members to file
    ELSE
        Display member not found
    END IF
```

### 6.5 Borrowing Pseudocode
```text
FOR issue book:
    READ record ID
    READ book ID
    IF book does not exist THEN
        Display book not found
    ELSE IF book quantity is zero THEN
        Display unavailable
    ELSE
        READ member ID
        IF member does not exist THEN
            Display member not found
        ELSE
            READ borrowed date
            Create borrow record
            Reduce book quantity by 1
            Save books and borrow records
        END IF
    END IF

FOR return book:
    READ borrow record ID
    IF record exists and status is Borrowed THEN
        READ return date
        Change status to Returned
        Increase book quantity by 1
        Save books and borrow records
    ELSE
        Display record not found or already returned
    END IF
```

### 6.6 Report Generation Pseudocode
```text
OPEN inventory_report.txt for writing
IF file cannot open THEN
    Display error message
ELSE
    FOR each book
        Write book ID, title, author, genre, year, quantity, and status
    END FOR
    Close file
    Display report generated message
END IF
```

## 7. Implementation
The system was implemented using modular C files. Each module has a specific responsibility, making the code easier to understand, maintain, and test.

| File | Purpose |
|---|---|
| `main.c` | Controls the whole program. |
| `auth.c/auth.h` | Handles login and authentication. |
| `books.c/books.h` | Handles adding, searching, updating, removing books, and generating reports. |
| `members.c/members.h` | Handles member registration, viewing, and updating. |
| `borrowing.c/borrowing.h` | Handles issuing and returning books. |
| `filehandling.c/filehandling.h` | Handles reading and writing text files. |
| `menu.c/menu.h` | Displays menus and reads menu choices. |
| `books.txt` | Stores book data. |
| `members.txt` | Stores member data. |
| `borrow_records.txt` | Stores borrowing history. |
| `inventory_report.txt` | Stores generated inventory report. |

## 8. File Handling

### books.txt
The system reads `books.txt` when the program starts. Each line follows this format:

```text
BookID,Title,Author,Genre,YearPublished,Quantity
```

### members.txt
The system stores member information using this format:

```text
MemberID,Name,Phone
```

### borrow_records.txt
Borrowing records are stored using this format:

```text
RecordID,BookID,MemberID,BorrowedDate,ReturnDate,Status
```

### inventory_report.txt
The report file is generated when the administrator selects the report option. It lists all books with their availability status.

### Missing File Handling
If a file is missing, the system displays a warning message. A new file is created automatically when records are saved.

## 9. Testing
| Test | Input | Expected Result | Actual Result | Status |
|---|---|---|---|---|
| Login | Correct username/password | Access granted | Access granted | Pass |
| Login | Wrong password | Error message and attempts reduced | Error message displayed | Pass |
| Display books | Select option 1 | All books displayed | All books displayed | Pass |
| Search book | Existing title | Book found | Book found | Pass |
| Search book | Unknown title | No matching book found | No matching book found | Pass |
| Add book | Valid book details | Book saved | Book saved | Pass |
| Add book | Duplicate Book ID | Duplicate error | Duplicate error shown | Pass |
| Update quantity | Existing Book ID | Quantity updated | Quantity updated | Pass |
| Borrow book | Available book and valid member | Quantity reduced | Quantity reduced | Pass |
| Return book | Valid borrow record | Quantity increased | Quantity increased | Pass |
| Generate report | Select option 12 | Report created | Report created | Pass |
| Exit | Select option 0 | Data saved and program closes | Data saved and program closes | Pass |

## 10. Challenges and Solutions
| Challenge | Solution |
|---|---|
| File reading errors | Added checks for missing files and warning messages. |
| Invalid menu input | Added validation when reading menu choices. |
| Duplicate book/member IDs | Checked existing IDs before saving new records. |
| Managing several features | Used separate modules for books, members, borrowing, authentication, and file handling. |
| Maintaining persistent data | Used text files for storing books, members, and borrowing records. |

## 11. User Manual
A separate user manual is included in `docs/user_manual.md`. It explains how to compile, run, log in, and use every menu option.

## 12. Conclusion
The Library Management System successfully demonstrates structured programming concepts in C. It uses functions, arrays, structures, control statements, and file handling to manage a real-world library scenario. The system supports book management, member management, borrowing records, and report generation.

## 13. References
- Course project specification provided in IS301 Structured Programming.
- GeeksforGeeks. (n.d.). C Programming Language.
- TutorialsPoint. (n.d.). C File I/O.

## 14. Appendices
The appendices include flowchart images, sample `books.txt`, sample `members.txt`, sample `borrow_records.txt`, sample `inventory_report.txt`, and source code files.


## Updated Program Flow
The program was updated to follow the required grouped menu structure. After login, the system displays five main options: Book Management, Member Management, Borrowing Records, Reports, and Exit.

### Main Menu
1. Book Management
2. Member Management
3. Borrowing Records
4. Reports
5. Exit

### Book Management Flow
The Book Management menu contains Display Books, Search Books, Add Books, Delete Books, Update Quantity, and Exit to Main Menu. Successful actions display messages such as `Book Added.`, `Book Removed.`, `Quantity Updated.`, `Book Found.`, and `All Books Displayed.` Errors display a retry message.

### Member Management Flow
The Member Management menu contains Register Member, View Member Details, Update Information, and Exit to Main Menu. Successful actions display `Member Registered.`, `Details Displayed.`, and `Information Updated.` Errors display a retry message.

### Borrowing Records Flow
The Borrowing Records menu contains Issue Books, Return Book, Borrowing History, and Exit to Main Menu. Successful actions display `Book Issued.`, `Book Returned.`, and `User History Shown.` Errors display a retry message.

### Reports Flow
The Reports menu contains Generate Inventory, Member Activity, and Exit to Main Menu. Successful actions display `Inventory Generated.` and `Activities Shown.` Errors display a retry message.

### Testing Confirmation
The updated program was compiled successfully. A test run confirmed that login, main menu navigation, submenu navigation, inventory generation, and program exit are working correctly.
