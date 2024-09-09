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

int prefix_to_infix(char* exp, char* infix) {
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

int input_prec(char symbol) {
    switch(symbol) {
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 3;
        case '^': return 6;
        case '(': return 9;
        case ')': return 0;
        default: return 7;
    }
}

int stack_prec(char symbol) {
    switch(symbol) {
        case '+':
        case '-': return 2;
        case '*':
        case '/': return 4;
        case '^': return 5;
        case '(': return 0;
        case '#': return -1;
        default: return 8;
    }
}

int infix_to_postfix(char* infix, char* postfix) {
    char stk[300];
    int top = -1, j = 0;
    stk[++top] = '#';
    for (int i = 0; infix[i] != '\0'; i++) {
        char symbol = infix[i];
        while (stack_prec(stk[top]) > input_prec(symbol))
            postfix[j++] = stk[top--];
        if (stack_prec(stk[top]) != input_prec(symbol))
            stk[++top] = symbol;
        else
            top--;
    }
    postfix[j] = '\0';
    if (stk[top] != '#') {
        printf("Invalid expression");
        return 1;
    }
    return 0;
}

int main() {
    printf("Enter the expression: ");
    char prefix[200], infix[300], postfix[300];
    int error;
    fgets(prefix, 200, stdin);
    removenewline(prefix);
    error = prefix_to_infix(prefix, infix);
    if (error == 1)
        return 1;
    error = infix_to_postfix(infix, postfix);
    if (error)
        return 1;
    printf("The postfix expression is: %s", postfix);
    return 0;
}