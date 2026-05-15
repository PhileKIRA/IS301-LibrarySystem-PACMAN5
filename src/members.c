#include <stdio.h>
#include <string.h>
#include "members.h"
#include "filehandling.h"

int displayMembers(Member members[], int count) {
    int i;
    if (count == 0) {
        printf("Error: No members registered. Please retry after registering a member.\n");
        return 0;
    }

    printf("\n%-12s %-30s %-20s\n", "MemberID", "Name", "Phone");
    printf("---------------------------------------------------------------\n");
    for (i = 0; i < count; i++) {
        printf("%-12s %-30s %-20s\n", members[i].memberID, members[i].name, members[i].phone);
    }
    return 1;
}

int findMemberByID(Member members[], int count, const char *memberID) {
    int i;
    for (i = 0; i < count; i++) {
        if (strcmp(members[i].memberID, memberID) == 0) return i;
    }
    return -1;
}

int registerMember(Member members[], int *count) {
    Member newMember;

    if (*count >= MAX_MEMBERS) {
        printf("Error: Member storage is full. Please retry after removing old records.\n");
        return 0;
    }

    if (!readTextOrBack("Enter Member ID: ", newMember.memberID, sizeof(newMember.memberID))) return 0;

    if (strlen(newMember.memberID) == 0 || findMemberByID(members, *count, newMember.memberID) != -1) {
        printf("Error: Invalid or duplicate Member ID. Please retry.\n");
        return 0;
    }

    if (!readTextOrBack("Enter Member Name: ", newMember.name, sizeof(newMember.name))) return 0;

    if (!readTextOrBack("Enter Phone Number: ", newMember.phone, sizeof(newMember.phone))) return 0;

    if (strlen(newMember.name) == 0 || strlen(newMember.phone) == 0) {
        printf("Error: Member details cannot be empty. Please retry.\n");
        return 0;
    }

    members[*count] = newMember;
    (*count)++;
    return 1;
}

int updateMember(Member members[], int count) {
    char memberID[20];
    int index;

    if (!readTextOrBack("Enter Member ID to update: ", memberID, sizeof(memberID))) return 0;

    index = findMemberByID(members, count, memberID);
    if (index == -1) {
        printf("Error: Member not found. Please retry.\n");
        return 0;
    }

    if (!readTextOrBack("Enter new name: ", members[index].name, sizeof(members[index].name))) return 0;

    if (!readTextOrBack("Enter new phone number: ", members[index].phone, sizeof(members[index].phone))) return 0;

    if (strlen(members[index].name) == 0 || strlen(members[index].phone) == 0) {
        printf("Error: Information cannot be empty. Please retry.\n");
        return 0;
    }
    return 1;
}

int deleteMember(Member members[], int *count) {
    char memberID[20];
    int index, i;

    if (*count == 0) {
        printf("Error: No members available to delete. Please retry after registering members.\n");
        return 0;
    }

    if (!readTextOrBack("Enter Member ID to delete: ", memberID, sizeof(memberID))) return 0;

    index = findMemberByID(members, *count, memberID);
    if (index == -1) {
        printf("Error: Member not found. Please retry.\n");
        return 0;
    }

    for (i = index; i < *count - 1; i++) {
        members[i] = members[i + 1];
    }
    (*count)--;
    return 1;
}
