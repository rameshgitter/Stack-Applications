#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include<string.h>

// Stack type
struct Stack {
    int top;
    unsigned capacity;
    int* array;
};

// Stack Operations
struct Stack* createStack(unsigned capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    if (!stack)
        return NULL;
    stack->top = -1;
    stack->capacity = capacity;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}

int isFull(struct Stack* stack) {
    return stack->top == stack->capacity - 1;
}

int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

void push(struct Stack* stack, int item) {
    if (isFull(stack))
        return;
    stack->array[++stack->top] = item;
}

int pop(struct Stack* stack) {
    if (isEmpty(stack))
        return -1;
    return stack->array[stack->top--];
}

int peek(struct Stack* stack) {
    if (isEmpty(stack))
        return -1;
    return stack->array[stack->top];
}

// Evaluate a postfix expression
int evaluatePostfix(char* exp) {
    struct Stack* stack = createStack(strlen(exp));
    int i, operand1, operand2, result;
    char ch;

    if (!stack)
        return -1;

    for (i = 0; exp[i]; i++) {
        ch = exp[i];

        if (isdigit(ch)) {
            push(stack, ch - '0');
        } else {
            operand2 = pop(stack);
            operand1 = pop(stack);

            switch (ch) {
                case '+':
                    result = operand1 + operand2;
                    break;
                case '-':
                    result = operand1 - operand2;
                    break;
                case '*':
                    result = operand1 * operand2;
                    break;
                case '/':
                    result = operand1 / operand2;
                    break;
                default:
                    return -1;
            }

            push(stack, result);
        }
    }

    return pop(stack);
}

// Evaluate a prefix expression
int evaluatePrefix(char* exp) {
    struct Stack* stack = createStack(strlen(exp));
    int i, operand1, operand2, result;
    char ch;

    if (!stack)
        return -1;

    for (i = strlen(exp) - 1; i >= 0; i--) {
        ch = exp[i];

        if (isdigit(ch)) {
            push(stack, ch - '0');
        } else {
            operand1 = pop(stack);
            operand2 = pop(stack);

            switch (ch) {
                case '+':
                    result = operand1 + operand2;
                    break;
                case '-':
                    result = operand1 - operand2;
                    break;
                case '*':
                    result = operand1 * operand2;
                    break;
                case '/':
                    result = operand1 / operand2;
                    break;
                default:
                    return -1;
            }

            push(stack, result);
        }
    }

    return pop(stack);
}

int main() {
    char postfixExp[50];
    printf("enter your postfix expression: ");
    scanf("%s",postfixExp);
    char prefixExp[50];
    printf("enter your prefix expression: ");
    scanf("%s",prefixExp);

    printf("Postfix Expression: %s\n", postfixExp);
    printf("Evaluation Result: %d\n", evaluatePostfix(postfixExp));

    printf("Prefix Expression: %s\n", prefixExp);
    printf("Evaluation Result: %d\n", evaluatePrefix(prefixExp));

    return 0;
}
