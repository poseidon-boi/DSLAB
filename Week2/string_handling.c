#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void removenewline(char str[]) {
    for (int i=0; str[i] != '\0'; i++)
        if (str[i] == '\n') {
            str[i] = '\0';
            break;
        }
}

int str_len(char str[]) {
    int i;
    for (i=0; str[i]!='\0'; i++);
    return i;
}

void concat(char str1[], char str2[]) {
    int len1 = str_len(str1);
    for (int i=0; i<str_len(str2); i++)
        str1[len1+i] = str2[i];
}

int strcomp(char str1[], char str2[]) {
    int i;
    for (i=0; (str1[i] != '\0') && (str2[i] != '\0'); i++) {
        if (str1[i] - str2[i] != 0)
            return str1[i] - str2[i];
    }
    return str1[i] - str2[i];
}

void insert_sub(char mainstr[], char substr[], int index) {
    int mainlen = str_len(mainstr), sublen = str_len(substr);
    if (index >= mainlen || index < 0) {
        printf("Invalid index");
        return;
    }
    char tempstr[100];
    int i, j;
    for (i=0; mainstr[i] != '\0'; i++)
        tempstr[i] = mainstr[i+index];
    tempstr[i] = '\0';
    for (i=0; i<sublen; i++)
        mainstr[i+index] = substr[i];
    for (i=0; i<str_len(tempstr); i++)
        mainstr[i+index+sublen] = tempstr[i];
    mainstr[mainlen+sublen] = '\0';
}

void delete_sub(char mainstr[], char substr[]) {
    int mainlen = str_len(mainstr), sublen = str_len(substr);
    short present = 0, pos;
    for (int i=0; i<mainlen; i++) {
        int j;
        for (j=0; j<sublen; j++)
            if(mainstr[i+j] != substr[j])
                break;
        if (j==sublen) {
            present = 1;
            pos = i;
        }
    }
    if (present == 0)
        return;
    int i;
    for (i=pos; mainstr[i+sublen] != '\0'; i++)
        mainstr[i] = mainstr[i+sublen];
    mainstr[i] = '\0';
}

int main() {
    char str[100], str2[100];
    printf("Enter a string: ");
    fgets(str, 100, stdin);
    removenewline(str);
    printf("The length of the string is %d\n", str_len(str));
    printf("Enter a second string: ");
    fgets(str2, 100, stdin);
    removenewline(str2);
    printf("The output of comparing the strings is %d\n", strcomp(str, str2));
    concat(str, str2);
    printf("The concatenated string is: %s\n", str);
    printf("Enter substring to delete: ");
    fgets(str2, 100, stdin);
    removenewline(str2);
    delete_sub(str, str2);
    printf("New string is: %s\n", str);
    printf("Enter a substring: ");
    fgets(str2, 100, stdin);
    removenewline(str2);
    printf("Enter index to insert: ");
    int index;
    scanf("%d", &index);
    insert_sub(str, str2, index);
    printf("New string is: %s\n", str);
    return 0;
}

