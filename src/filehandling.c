#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifdef _WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#include <sys/types.h>
#endif
#include "filehandling.h"

void removeNewline(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

static void clearExtraInput(char *str) {
    int ch;
    if (strchr(str, '\n') == NULL) {
        while ((ch = getchar()) != '\n' && ch != EOF) { }
    }
}

static void ensureDataFolder(void) {
#ifdef _WIN32
    mkdir("data");
#else
    mkdir("data", 0777);
#endif
}

static void trimSpaces(char *str) {
    int start = 0;
    int end = (int)strlen(str) - 1;

    while (str[start] == ' ' || str[start] == '\t') start++;
    while (end >= start && (str[end] == ' ' || str[end] == '\t' || str[end] == '\r')) {
        str[end] = '\0';
        end--;
    }
    if (start > 0) memmove(str, str + start, strlen(str + start) + 1);
}

int isBackCommand(const char *str) {
    return (strcmp(str, "B") == 0 || strcmp(str, "b") == 0 || strcmp(str, "0") == 0);
}

int readTextOrBack(const char *prompt, char *buffer, int size) {
    printf("%s", prompt);
    if (fgets(buffer, size, stdin) == NULL) return 0;
    clearExtraInput(buffer);
    removeNewline(buffer);
    trimSpaces(buffer);

    if (isBackCommand(buffer)) {
        printf("Action cancelled. Returning to previous menu...\n");
        return 0;
    }
    return 1;
}

int readIntOrBack(const char *prompt, int *value) {
    char line[50];
    char *endptr;

    printf("%s", prompt);
    if (fgets(line, sizeof(line), stdin) == NULL) return 0;
    clearExtraInput(line);
    removeNewline(line);
    trimSpaces(line);

    if (isBackCommand(line)) {
        printf("Action cancelled. Returning to previous menu...\n");
        return 0;
    }

    *value = (int)strtol(line, &endptr, 10);
    if (line[0] == '\0' || *endptr != '\0') {
        printf("Error: Invalid number. Please retry.\n");
        return 0;
    }
    return 1;
}

int loadBooks(Book books[], const char *filename) {
    FILE *fp;
    int count = 0;

    ensureDataFolder();
    fp = fopen(filename, "r");
    if (fp == NULL) {
        fp = fopen(filename, "w");
        if (fp != NULL) fclose(fp);
        return 0;
    }

    while (count < MAX_BOOKS &&
           fscanf(fp, " %19[^,],%99[^,],%99[^,],%49[^,],%d,%d\n",
                  books[count].bookID,
                  books[count].title,
                  books[count].author,
                  books[count].genre,
                  &books[count].yearPublished,
                  &books[count].quantity) == 6) {
        count++;
    }

    fclose(fp);
    return count;
}

int saveBooks(Book books[], int count, const char *filename) {
    FILE *fp;
    int i;

    ensureDataFolder();
    fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error: Cannot write to %s\n", filename);
        return 0;
    }

    for (i = 0; i < count; i++) {
        fprintf(fp, "%s,%s,%s,%s,%d,%d\n",
                books[i].bookID,
                books[i].title,
                books[i].author,
                books[i].genre,
                books[i].yearPublished,
                books[i].quantity);
    }

    fclose(fp);
    return 1;
}

int loadMembers(Member members[], const char *filename) {
    FILE *fp;
    int count = 0;

    ensureDataFolder();
    fp = fopen(filename, "r");
    if (fp == NULL) {
        fp = fopen(filename, "w");
        if (fp != NULL) fclose(fp);
        return 0;
    }

    while (count < MAX_MEMBERS &&
           fscanf(fp, " %19[^,],%99[^,],%29[^\n]\n",
                  members[count].memberID,
                  members[count].name,
                  members[count].phone) == 3) {
        count++;
    }

    fclose(fp);
    return count;
}

int saveMembers(Member members[], int count, const char *filename) {
    FILE *fp;
    int i;

    ensureDataFolder();
    fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error: Cannot write to %s\n", filename);
        return 0;
    }

    for (i = 0; i < count; i++) {
        fprintf(fp, "%s,%s,%s\n",
                members[i].memberID,
                members[i].name,
                members[i].phone);
    }

    fclose(fp);
    return 1;
}

int loadBorrowRecords(BorrowRecord records[], const char *filename) {
    FILE *fp;
    int count = 0;

    ensureDataFolder();
    fp = fopen(filename, "r");
    if (fp == NULL) {
        fp = fopen(filename, "w");
        if (fp != NULL) fclose(fp);
        return 0;
    }

    while (count < MAX_BORROWS &&
           fscanf(fp, " %19[^,],%19[^,],%19[^,],%19[^,],%19[^,],%19[^\n]\n",
                  records[count].recordID,
                  records[count].bookID,
                  records[count].memberID,
                  records[count].borrowedDate,
                  records[count].returnDate,
                  records[count].status) == 6) {
        count++;
    }

    fclose(fp);
    return count;
}

int saveBorrowRecords(BorrowRecord records[], int count, const char *filename) {
    FILE *fp;
    int i;

    ensureDataFolder();
    fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error: Cannot write to %s\n", filename);
        return 0;
    }

    for (i = 0; i < count; i++) {
        fprintf(fp, "%s,%s,%s,%s,%s,%s\n",
                records[i].recordID,
                records[i].bookID,
                records[i].memberID,
                records[i].borrowedDate,
                records[i].returnDate,
                records[i].status);
    }

    fclose(fp);
    return 1;
}

