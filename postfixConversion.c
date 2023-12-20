#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXSTACK 100

// Stack implementation
char stack[MAXSTACK];
int top = -1;

void push(char item) {
    if (top >= MAXSTACK - 1) {
        printf("Stack Overflow\n");
        return;
    }
    stack[++top] = item;
}

char pop() {
    if (top < 0) {
        printf("Stack Underflow\n");
        return -1;
    }
    return stack[top--];
}

int isOperator(char ch) {
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^') {
        return 1;
    }
    return 0;
}

int precedence(char ch) {
    if (ch == '^') {
        return 3;
    } else if (ch == '*' || ch == '/') {
        return 2;
    } else if (ch == '+' || ch == '-') {
        return 1;
    }
    return -1;
}

// Function to convert an infix expression to a postfix expression
void infixToPostfix(char* infix, char* postfix) {
    int i, j;
    char ch, topOperator;

    for (i = 0, j = 0; infix[i] != '\0'; i++) {
        ch = infix[i];

        if (isalnum(ch)) {
            postfix[j++] = ch;
        } else if (ch == '(') {
            push(ch);
        } else if (ch == ')') {
            while ((topOperator = pop()) != '(') {
                postfix[j++] = topOperator;
            }
        } else if (isOperator(ch)) {
            while (precedence(ch) <= precedence(stack[top]) && top != -1) {
                topOperator = pop();
                postfix[j++] = topOperator;
            }
            push(ch);
        }
    }

    while (top != -1) {
        topOperator = pop();
        postfix[j++] = topOperator;
    }
    postfix[j] = '\0';
}

int main() {
    char infix[100], postfix[100];
    printf("Enter an infix expression: ");
    scanf("%s", infix);
    infixToPostfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);
    return 0;
}
