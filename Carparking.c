#include <stdio.h>
#define MAX 10

int deque[MAX];
int front = -1, rear = -1;

// Check if deque is full
int isFull() {
    return ((front == 0 && rear == MAX - 1) || (front == rear + 1));
}

// Check if deque is empty
int isEmpty() {
    return (front == -1);
}

// Insert at front
void insertFront(int item) {
    if (isFull()) {
        printf("Deque is full\n");
        return;
    }
    if (isEmpty()) {
        front = rear = 0;
    } else if (front == 0) {
        front = MAX - 1;
    } else {
        front--;
    }
    deque[front] = item;
}

// Insert at rear
void insertRear(int item) {
    if (isFull()) {
        printf("Deque is full\n");
        return;
    }
    if (isEmpty()) {
        front = rear = 0;
    } else if (rear == MAX - 1) {
        rear = 0;
    } else {
        rear++;
    }
    deque[rear] = item;
}

// Delete from front
void deleteFront() {
    if (isEmpty()) {
        printf("Deque is empty\n");
        return;
    }
    printf("Deleted from front: %d\n", deque[front]);
    if (front == rear) {
        front = rear = -1;
    } else if (front == MAX - 1) {
        front = 0;
    } else {
        front++;
    }
}

// Delete from rear
void deleteRear() {
    if (isEmpty()) {
        printf("Deque is empty\n");
        return;
    }
    printf("Deleted from rear: %d\n", deque[rear]);
    if (front == rear) {
        front = rear = -1;
    } else if (rear == 0) {
        rear = MAX - 1;
    } else {
        rear--;
    }
}

// Display deque
void display() {
    if (isEmpty()) {
        printf("Deque is empty\n");
        return;
    }
    printf("Deque contents: ");
    int i = front;
    while (1) {
        printf("%d ", deque[i]);
        if (i == rear)
            break;
        i = (i + 1) % MAX;
    }
    printf("\n");
}

// Main function
int main() {
    insertRear(10);
    insertRear(20);
    insertFront(5);
    insertFront(2);
    display();

    deleteRear();
    deleteFront();
    display();

    return 0;
}
