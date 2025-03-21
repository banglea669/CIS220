//Austin Bangle
//Chpt5 PA
#include <stdio.h>
#include <stdlib.h>

// Define a Node structure for each element in the queue
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Define a Queue structure to represent the queue implemented as a linked list
typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;

// Function to create and initialize an empty queue
Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (queue == NULL) {
        printf("Memory allocation error!\n");
        exit(1);
    }
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

// Enqueue operation: adds an item to the end of the queue
void enqueue(Queue* queue, int item) {
    // Allocate new node and assign data (newNode->next is set to NULL)
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation error!\n");
        exit(1);
    }
    // Set the node's member values
    newNode->data = item;
    newNode->next = NULL;
    
    if (queue->front == NULL) {
        // If the queue is empty, set front to the new node
        queue->front = newNode;
    } else {
        // Otherwise, link the new node at the end of the queue
        queue->rear->next = newNode;
    }
    // Update the rear pointer to the new node
    queue->rear = newNode;
}

// Dequeue operation: removes and returns the item from the front of the queue
int dequeue(Queue* queue) {
    if (queue->front == NULL) {
        return -1;  // If queue is empty return -1
    }
    // Save the data from the front node and move the front pointer
    Node* temp = queue->front;
    int dequeuedItem = temp->data;
    queue->front = temp->next;
    // If the queue becomes empty, update the rear pointer to NULL
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    // Free memory for the dequeued node
    free(temp); 
    return dequeuedItem;
}

// Function to check if the queue is empty
int isEmpty(Queue* queue) {
    return (queue->front == NULL);  // Return true if the queue is empty
}

// Function to peek at the front item without removing it
int peek(Queue* queue) {
    if (queue->front == NULL) {
        return 0;  // Return 0 if the queue is empty
    }
    return queue->front->data;  // Return the front item without removing it
}

// Function to get the length of the queue
int getLength(Queue* queue) {
    int length = 0;
    Node* current = queue->front;
    while (current != NULL) {
        length++;
        current = current->next;
    }
    return length;
}

// Function to traverse and display the queue
void displayQueue(Queue* queue) {
    if (queue->front == NULL) {
        printf("Queue is empty.\n");
        return;
    }
    Node* current = queue->front;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    Queue* queue = createQueue();
    
    // 1. Display the queue
    printf("Queue initially: ");
    displayQueue(queue);

    // 2. Call isEmpty to display if the queue is empty
    printf("Is the queue empty? %s\n", isEmpty(queue) ? "Yes" : "No");

    // 3. Call peek and display the top item in the queue
    printf("Peek top item: %d\n", peek(queue));

    // 4. Display the queue's length
    printf("Queue length: %d\n", getLength(queue));

    // 5. Enqueue item 1 to queue
    enqueue(queue, 1);

    // 6. Enqueue item 2 to queue
    enqueue(queue, 2);

    // 7. Call peek and display the top item in the queue
    printf("Peek top item after enqueuing 1 and 2: %d\n", peek(queue));

    // 8. Enqueue item 3 to queue
    enqueue(queue, 3);

    // 9. Display the queue's length
    printf("Queue length after enqueuing 3: %d\n", getLength(queue));

    // 10. Dequeue an item from the queue and display the item’s value
    printf("Dequeued item: %d\n", dequeue(queue));

    // 11. Call peek and display the top item in the queue
    printf("Peek top item after dequeuing: %d\n", peek(queue));

    // 12. Enqueue item 4 to queue
    enqueue(queue, 4);

    // 13. Display the queue
    printf("Queue after enqueuing 4: ");
    displayQueue(queue);

    // 14. Enqueue item 5 to queue
    enqueue(queue, 5);

    // 15. Dequeue an item from the queue and display the item’s value
    printf("Dequeued item: %d\n", dequeue(queue));

    // 16. Enqueue item 6 to queue
    enqueue(queue, 6);

    // 17. Display the queue’s length
    printf("Queue length after enqueuing 6: %d\n", getLength(queue));

    // 18. Display the queue
    printf("Queue after enqueuing 6: ");
    displayQueue(queue);

    // 19. Dequeue an item from the queue and display the item’s value
    printf("Dequeued item: %d\n", dequeue(queue));

    // 20. Call isEmpty to display if the queue is empty
    printf("Is the queue empty? %s\n", isEmpty(queue) ? "Yes" : "No");

    // 21. Dequeue an item from the queue and display the item’s value
    printf("Dequeued item: %d\n", dequeue(queue));

    // 22. Dequeue an item from the queue and display the item’s value
    printf("Dequeued item: %d\n", dequeue(queue));

    // 23. Display the queue’s length
    printf("Queue length after dequeuing two items: %d\n", getLength(queue));

    // 24. Dequeue an item from the queue and display the item’s value
    printf("Dequeued item: %d\n", dequeue(queue));

    // 25. Dequeue an item from the queue and display the item’s value
    printf("Dequeued item: %d\n", dequeue(queue));

    // 26. Call isEmpty to display if the queue is empty
    printf("Is the queue empty? %s\n", isEmpty(queue) ? "Yes" : "No");

    // Free the queue structure (all nodes should have been dequeued by now)
    free(queue);
    
    return 0;
}

