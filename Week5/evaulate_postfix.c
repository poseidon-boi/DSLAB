#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ERROR -973845

void removenewline(char str[]) {
    for (int i=0; str[i] != '\0'; i++)
        if (str[i] == '\n') {
            str[i] = '\0';
            break;
        }
}

int eval(char* exp) {
    int result, opd[150], top = -1;
    for (int i = 0; exp[i] != '\0'; i++) {
        if (exp[i] >= '0' && exp[i] <= '9') {
            opd[++top] = exp[i]-'0';
            continue;
        }
        if (top <= 0) {
            printf("Invalid expression");
            return ERROR;
        }
        int opd2 = opd[top--];
        int opd1 = opd[top--];
        switch (exp[i]) {
            case '+':
                opd[++top] = opd1 + opd2;
                break;
            case '-':
                opd[++top] = opd1 - opd2;
                break;
            case '*':
                opd[++top] = opd1 * opd2;
                break;
            case '/':
                opd[++top] = opd1 / opd2;
                break;
            case '%':
                opd[++top] = opd1 % opd2;
                break;
            default:
                printf("Invalid operator");
                return ERROR;
        }
    }
    if (top != 0) {
        printf("Invalid expression");
        return ERROR;
    }
    return opd[0];
}

int main() {
    printf("Enter the expression: ");
    char *exp, result;
    fgets(exp, 200, stdin);
    removenewline(exp);
    result = eval(exp);
    if (result == ERROR)
        return 1;
    printf("The result is %d", result);
    return 0;
}