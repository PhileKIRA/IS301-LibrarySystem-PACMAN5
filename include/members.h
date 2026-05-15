#ifndef MEMBERS_H
#define MEMBERS_H

#ifndef MAX_TEXT
#define MAX_TEXT 100
#endif
#define MAX_MEMBERS 500

typedef struct {
    char memberID[20];
    char name[MAX_TEXT];
    char phone[30];
} Member;

int displayMembers(Member members[], int count);
int findMemberByID(Member members[], int count, const char *memberID);
int registerMember(Member members[], int *count);
int updateMember(Member members[], int count);
int deleteMember(Member members[], int *count);

#endif

