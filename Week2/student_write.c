#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
    char *name;
    char *branch;
    int rollno;
    char grade;
};

/** Removes newline character from the end of the fgets string, if it exists
 * @param str The string to remove newline character from
 */
void removenewline(char str[]) {
    for (int i=0; str[i] != '\0'; i++)
        if (str[i] == '\n') {
            str[i] = '\0';
            break;
        }
}

/** Gets data and appends to a file called student_records.csv */
void appendtomainfile() {
    FILE *fp;
    fp = fopen("student_records.csv", "a");
    printf("Enter number of students to add: ");
    int n;
    scanf("%d", &n);
    while (getchar() != '\n');
    struct student s[n];
    for (int i=0; i<n; i++) {
        printf("Enter name of student %d: ", i+1);
        s[i].name = malloc(100);
        fgets(s[i].name, 100, stdin);
        removenewline(s[i].name);
        printf("Enter rollno and grade: ");
        scanf("%d %c", &s[i].rollno, &s[i].grade);
        while (getchar() != '\n');
        printf("Enter branch: ");
        s[i].branch = malloc(100);
        fgets(s[i].branch, 100, stdin);
        removenewline(s[i].branch);
    }
    for (int i = 0; i < n; i++) {
        fprintf(fp, "%s,%s,%d,%c\n", s[i].name, s[i].branch, s[i].rollno, s[i].grade);
    }
}

/** Reads student_records.csv and creates subfiles with students of specific branches */
void createbranchfiles() {
    FILE *mainreader;
    mainreader = fopen("student_records.csv", "r");
    char *record = malloc(250);
    while (1) {
        fgets(record, 250, mainreader);
        if (record == NULL || feof(mainreader) || ferror(mainreader))
            break;
        struct student s;
        s.rollno = 0;
        int i = 0;
        s.name = malloc(100);
        s.branch = malloc(100);
        for (; record[i] != ','; i++)
            s.name[i] = record[i];
        i++;
        for (int j = 0; record[i] != ','; i++, j++)
            s.branch[j] = record[i];
        i++;
        for (; record[i] != ','; i++)
            s.rollno = s.rollno * 10 + (record[i] - '0');
        i++;
        s.grade = record[i];
        printf("%s,%s,%d,%c\n", s.name, s.branch, s.rollno, s.grade);
        FILE *branchfilewriter;
        char *branchfile = malloc(100);
        strcpy(branchfile, s.branch);
        strcat(branchfile, ".csv");
        branchfilewriter = fopen(branchfile, "a");
        fprintf(branchfilewriter, "%s,%s,%d,%c\n", s.name, s.branch, s.rollno, s.grade);
        s.name = (char*) NULL;
        s.branch = (char*) NULL;
        branchfile = (char*) NULL;
        free(s.name);
        free(s.branch);
        free(branchfile);
    }
    free(record);
}

int main() {
    printf("Enter 1 to add to record, and 2 to create branch files: ");
    int ch;
    scanf("%d", &ch);
    if (ch == 1)
        appendtomainfile();
    else if (ch == 2)
        createbranchfiles();
    else
        printf("Invalid choice");
    return 0;
}