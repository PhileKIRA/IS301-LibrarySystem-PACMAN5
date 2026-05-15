#ifndef FILEHANDLING_H
#define FILEHANDLING_H

#include "books.h"
#include "members.h"
#include "borrowing.h"

int loadBooks(Book books[], const char *filename);
int saveBooks(Book books[], int count, const char *filename);
int loadMembers(Member members[], const char *filename);
int saveMembers(Member members[], int count, const char *filename);
int loadBorrowRecords(BorrowRecord records[], const char *filename);
int saveBorrowRecords(BorrowRecord records[], int count, const char *filename);
void removeNewline(char *str);
int isBackCommand(const char *str);
int readTextOrBack(const char *prompt, char *buffer, int size);
int readIntOrBack(const char *prompt, int *value);

#endif

