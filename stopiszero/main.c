#include <stdio.h>
#include <stdlib.h>
#define max 100

typedef struct {
    int top;
    int ele[max];
} stack;

void initstack(stack *s) {
    s->top = -1;
}

int isFull(stack *s) {
    return (s->top == max - 1);
}

void push(stack *s, int e) {
    s->top++;
    s->ele[s->top] = e;
}

int isEmpty(stack *s) {
    return (s->top == -1);
}

int pop(stack *s) {
    int e = s->ele[s->top];
    s->top--;
    return e;
}

void display(stack *s) {
    FILE *fp4 = fopen("content.txt", "w");
    if ((s->top) == -1) {
        printf("Stack is empty. \n");
    } else {
        printf("Stack elements are\n");
        for (int i = s->top; i > 0; i--) {
            printf("%d\n", s->ele[i]);
            fprintf(fp4, "%d ", s->ele[i]);
        }
    }
}

int main() {
    stack s;
    int p, t, q, i, num, count1 = 0, count2 = 0;
    FILE *fp1 = fopen("display.txt", "w");
    printf("Enter the range: \n");
    scanf("%d %d", &p, &q);
    printf("Enter the number of elements to generate: ");
    scanf("%d", &t);
    FILE *fp5 = fopen("process.txt", "w");
    fprintf(fp5, "Generated elements are: ");
    for (i = 0; i < t; i++) {
        num = (rand() % (p - q + 1)) + p;
        printf("%d\n", num);
        fprintf(fp1, "%d ", num);
        fprintf(fp5, "%d ", num);
    }
    fprintf(fp5, "\n");
    fclose(fp1);
    fp1 = fopen("display.txt", "r");
    FILE *fp2 = fopen("enter.txt", "w");
    FILE *fp3 = fopen("delete.txt", "w");
    initstack(&s);
    int e, ch;

    // Set s->top to 0
    s.top = 0;

    while (1) {
        printf("\n1.push\n 2.pop\n 3.display\n 4.exit\n");
        printf("Enter the choice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1:
                if (isFull(&s))
                    printf("Stack overflow\n");
                else {
                    printf("Enter the element: ");
                    fscanf(fp1, "%d ", &e);
                    printf("%d", e);
                    fprintf(fp2, "%d ", e);
                    fprintf(fp5, "Pushed element is %d\n", e);
                    count1++;
                    push(&s, e);
                }
                break;
            case 2:
                if (isEmpty(&s))
                    printf("Empty Stack\n");
                else {
                    e = pop(&s);
                    fprintf(fp3, "%d ", e);
                    fprintf(fp5, "Popped element is %d\n", e);
                    count2++;
                }
                break;
            case 3:
                display(&s);
                fprintf(fp5, "Numbers of pushed elements is: %d\n", count1);
                fprintf(fp5, "Total number of popped elements is: %d\n", count2);
                fprintf(fp5, "Number of elements left in stack is: %d\n", count1 - count2);
                break;
            case 4:
                exit(0);
        }
    }
}
