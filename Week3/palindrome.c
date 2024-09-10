#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char pop(char stk[], int *top) {
    if (*top == -1)
        return '\0';
    return stk[(*top)--];
}

void push(char stk[], int size, int *top, char data) {
    if (*top == size-1) {
        printf("Stack overflow");
        return;
    }
    stk[++*top] = data;
}

int main() {
    char str[100], rev[100];
    printf("Enter a string: ");
    scanf(" %s", &str);
    int len = strlen(str), top = -1;
    for (int i=0; i<len; i++)
        push(rev, len, &top, str[i]);
    for (int i=0; i<len/2; i++) {
        if (str[i] != pop(rev, &top)) {
            printf("Not a palindrome");
            return 0;
        }
    }
    printf("Palindrome");
    return 0;
}
