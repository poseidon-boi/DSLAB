#include <stdio.h>
#include <stdlib.h>

void removenewline(char str[]) {
    for (int i=0; str[i] != '\0'; i++)
        if (str[i] == '\n') {
            str[i] = '\0';
            break;
        }
}

void concat(char* str1, char* str2) {
    int i = 0, j = 0;
    for (; str1[i] != '\0'; i++);
    for (; str2[j] != '\0'; j++)
        str1[i+j] = str2[j];
    str1[i+j] = '\0';
}

void copy(char* str1, char* str2) {
    int i = 0;
    for (; str2[i] != '\0'; i++)
        str1[i] = str2[i];
    str1[i] = '\0';
}

int convert(char* exp, char* infix) {
    int top = -1, len;
    char opd[200][300], opd1[300], opd2[300];
    for (len = 0; exp[len] != '\0'; len++);
    for (int i = len-1; i >= 0; i--) {
        if (exp[i] >= '0' && exp[i] <= '9') { // || (exp[i] >= 'a' && exp[i] <= 'z') || (exp[i] >= 'A' && exp[i] <= 'A')) {
            opd[++top][0] = exp[i];
            opd[top][1] = '\0';
            continue;
        }
        if (top <= 0) {
            printf("Invalid expression");
            return 1;
        }
        copy(opd1, opd[top--]);
        copy(opd2, opd[top--]);
        switch (exp[i]) {
            case '+':
            case '-':
            case '*':
            case '/':
            case '%':
                opd[++top][0] = '(';
                opd[top][1] = '\0';
                concat(opd[top], opd1);
                char expi[2];
                expi[0] = exp[i];
                expi[1] = '\0';
                concat(opd[top], expi);
                concat(opd[top], opd2);
                concat(opd[top], ")");
                break;
            default:
                printf("Invalid operator");
                return 1;
        }
    }
    if (top != 0) {
        printf("Invalid expression");
        return 1;
    }
    copy(infix, opd[0]);
    return 0;
}

int main() {
    printf("Enter the expression: ");
    char exp[200], infix[300];
    int error;
    fgets(exp, 200, stdin);
    removenewline(exp);
    error = convert(exp, infix);
    if (error == 1)
        return 1;
    printf("The infix expression is: %s", infix);
    return 0;
}