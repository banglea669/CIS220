// Austin Bangle
// Chpt3 PA

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 25 // Define the size of the array

// Function to perform Bubble Sort
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap arr[j] and arr[j+1]
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Function to print the array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[SIZE]; // Declare an array of size 25
    
    // Seed the random number generator
    srand(time(0));
    
    // Populate the array with random numbers between 1 and 1000
    for (int i = 0; i < SIZE; i++) {
        arr[i] = (rand() % 1000) + 1;
    }
    
    // Print the unsorted array
    printf("Unsorted array: \n");
    printArray(arr, SIZE);
    
    // Sort the array using Bubble Sort
    bubbleSort(arr, SIZE);
    
    // Print the sorted array
    printf("Sorted array: \n");
    printArray(arr, SIZE);
    
    return 0;
}
