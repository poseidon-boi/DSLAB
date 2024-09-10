#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
    char name[50];
    int rollno;
    char grade;
};

void display(struct student stud[], int size) {
    for (int i=0; i<size; i++)
        printf("%d\t%s\t%c\n", stud[i].rollno, stud[i].name, stud[i].grade);
}

void sort(struct student s[], int size) {
    for (int i=1; i<size; i++) {
        int temp = s[i].rollno, j;
        struct student tempstud = s[i];
        for (j=i-1; (j>=0) && (temp<s[j].rollno); j--)
            s[j+1] = s[j];
        s[j+1] = tempstud;
    }
}

void removenewline(char str[]) {
    for (int i=0; str[i] != '\0'; i++)
        if (str[i] == '\n') {
            str[i] = '\0';
            break;
        }
}

int main() {
    struct student s[3];
    for (int i=0; i<3; i++) {
        printf("Enter name of student %d: ", i+1);
        fgets(s[i].name, 50, stdin);
        removenewline(s[i].name);
        printf("Enter rollno and grade: ");
        scanf("%d %c", &s[i].rollno, &s[i].grade);
        while (getchar() != '\n');
    }
    sort(s, 3);
    printf("The sorted order is:\n");
    display(s, 3);
    return 0;
}
