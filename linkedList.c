#include <stdio.h>
#include <stdlib.h>

// Define a node structure for the singly linked list
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Define a structure for the list itself
typedef struct List {
    Node* head;
    Node* tail;
} List;

// Function prototypes
void ListInsertAfter(List* list, int currentItem, int newItem);
int ListRemove(List* list, int itemToRemove);
Node* ListSearch(List* list, int key);
void ListInsertionSortSinglyLinked(List* list);

// Function to allocate memory for a new node and initialize it with data
Node* allocateNewNode(int item) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = item;
    newNode->next = NULL;
    return newNode;
}

// Function to initialize an empty list
void initList(List* list) {
    list->head = NULL;
    list->tail = NULL;
}

// Function to append an item to the list
void ListAppend(List* list, int item) {
    Node* newNode = allocateNewNode(item);
    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        list->tail->next = newNode;
        list->tail = newNode;
    }
}

// Function to prepend an item to the list
void ListPrepend(List* list, int item) {
    Node* newNode = allocateNewNode(item);
    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        newNode->next = list->head;
        list->head = newNode;
    }
}

// Function to insert a node after a specific node
void ListInsertAfter(List* list, int currentItem, int newItem) {
    Node* currentNode = ListSearch(list, currentItem);
    if (currentNode != NULL) {
        Node* newNode = allocateNewNode(newItem);
        newNode->next = currentNode->next;
        currentNode->next = newNode;
        if (currentNode == list->tail) {
            list->tail = newNode;
        }
    }
}

// Function to search for a node with a specific data value
Node* ListSearch(List* list, int key) {
    Node* curNode = list->head;
    while (curNode != NULL) {
        if (curNode->data == key) {
            return curNode;
        }
        curNode = curNode->next;
    }
    return NULL;
}

// Function to remove a node with a specific data value
int ListRemove(List* list, int itemToRemove) {
    Node* current = list->head;
    Node* previous = NULL;
    while (current != NULL) {
        if (current->data == itemToRemove) {
            if (previous == NULL) {
                list->head = current->next;
                if (list->head == NULL) {
                    list->tail = NULL;
                }
            } else {
                previous->next = current->next;
                if (current == list->tail) {
                    list->tail = previous;
                }
            }
            free(current);
            return 1;
        }
        previous = current;
        current = current->next;
    }
    return 0;
}

// Function to traverse and print the list
void ListTraverse(List* list) {
    Node* curNode = list->head;
    while (curNode != NULL) {
        printf("%d -> ", curNode->data);
        curNode = curNode->next;
    }
    printf("NULL\n");
}

// Function to sum data values in the list
int sumDataValues(List* list) {
    int sum = 0;
    Node* curNode = list->head;
    while (curNode != NULL) {
        sum += curNode->data;
        curNode = curNode->next;
    }
    return sum;
}

// Function to sort the linked list using insertion sort
void ListInsertionSortSinglyLinked(List* list) {
    if (list->head == NULL || list->head->next == NULL) {
        return;
    }
    Node* sorted = NULL;
    Node* current = list->head;
    while (current != NULL) {
        Node* next = current->next;
        if (sorted == NULL || sorted->data >= current->data) {
            current->next = sorted;
            sorted = current;
        } else {
            Node* temp = sorted;
            while (temp->next != NULL && temp->next->data < current->data) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = next;
    }
    list->head = sorted;
}

// main function
int main() {
    // Austin Bangle
    // Chpt4 PA
    
    List myList;
    initList(&myList);
    
    // Display empty list
    printf("List: ");
    ListTraverse(&myList);
    
    // Sum of empty list
    printf("The sum of the lists data values is: %d\n", sumDataValues(&myList));
    
    // Append and insert values as per expected output
    ListPrepend(&myList, 30);
    ListInsertAfter(&myList, 30, 40);
    ListInsertAfter(&myList, 40, 70);
    ListInsertAfter(&myList, 70, 10);
    ListInsertAfter(&myList, 10, 60);
    ListInsertAfter(&myList, 60, 20);
    ListInsertAfter(&myList, 20, 50);
    
    // Display list
    ListTraverse(&myList);
    
    // Remove head and specific node
    ListRemove(&myList, 30);
    ListRemove(&myList, 10);
    
    // Display list after removals
    ListTraverse(&myList);
    
    // Search for values
    printf("Node 50 was %s.\n", ListSearch(&myList, 50) ? "found" : "not found");
    printf("Node 15 was %s.\n", ListSearch(&myList, 15) ? "found" : "not found");
    
    // Sort list
    ListInsertionSortSinglyLinked(&myList);
    printf("Sorted list: ");
    ListTraverse(&myList);
    
    // Final sum
    printf("The sum of the lists data values is: %d\n", sumDataValues(&myList));
    
    return 0;
}

