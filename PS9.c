#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX 100     
#define THREADS 4   


typedef enum {
    ADD,
    SUBTRACT,
    MULTIPLY,
    EXIT
} Operation;


typedef struct {
    int (*A)[MAX];     
    int (*B)[MAX];     
    int (*C)[MAX];    
    int startRow;      
    int endRow;        
    int n;             
    int m;             
    Operation op;      
} ThreadData;

// Function to perform matrix operations
void* performOperation(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    for (int i = data->startRow; i < data->endRow; i++) {
        for (int j = 0; j < data->n; j++) {
            switch (data->op) {
                case ADD:
                    data->C[i][j] = data->A[i][j] + data->B[i][j];
                    break;
                case SUBTRACT:
                    data->C[i][j] = data->A[i][j] - data->B[i][j];
                    break;
                case MULTIPLY:
                    // Initialize C[i][j] to 0 for multiplication
                    data->C[i][j] = 0;
                    for (int k = 0; k < data->m; k++) {
                        data->C[i][j] += data->A[i][k] * data->B[k][j];
                    }
                    break;
            }
        }
    }
    pthread_exit(NULL);
}

// Function to print a matrix
void printMatrix(int matrix[MAX][MAX], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];
    int n, m, p;
    int operation;

    while (1) {
        // Input operation type
        printf("Choose operation: 0 for Addition, 1 for Subtraction, 2 for Multiplication, 3 to Exit: ");
        scanf("%d", &operation);

        // Check for exit
        if (operation == EXIT) {
            printf("Exiting the program.\n");
            break;
        }

        // Input matrix dimensions
        printf("Enter number of rows and columns for matrix A: ");
        scanf("%d %d", &n, &m);
        
        // For multiplication, input the number of columns for matrix B
        if (operation == MULTIPLY) {
            printf("Enter number of columns for matrix B: ");
            scanf("%d", &p);
        } else {
            p = m; // For addition and subtraction, columns of B should match A
        }

        // Input matrices
        printf("Enter elements of matrix A:\n");
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                scanf("%d", &A[i][j]);

        printf("Enter elements of matrix B:\n");
        for (int i = 0; i < (operation == MULTIPLY ? m : n); i++)
            for (int j = 0; j < p; j++)
                scanf("%d", &B[i][j]);

        // Set the number of columns in the result matrix based on the operation
        int resultCols = (operation == MULTIPLY) ? p : m;

        pthread_t threads[THREADS];
        ThreadData threadData[THREADS];

        // Calculate the number of rows per thread
        int rowsPerThread = n / THREADS;

        // Create threads
        for (int i = 0; i < THREADS; i++) {
            threadData[i].A = A;
            threadData[i].B = B;
            threadData[i].C = C;
            threadData[i].startRow = i * rowsPerThread;
            threadData[i].endRow = (i == THREADS - 1) ? n : (i + 1) * rowsPerThread; // Handle last thread
            threadData[i].n = m; // For addition/subtraction
            threadData[i].m = p; // For multiplication
            threadData[i].op = operation; // Set operation type

            pthread_create(&threads[i], NULL, performOperation, (void*)&threadData[i]);
        }

        // Wait for threads to finish
        for (int i = 0; i < THREADS; i++) {
            pthread_join(threads[i], NULL);
        }

        // Output the result
        printf("Resultant matrix C:\n");
        printMatrix(C, n, resultCols);
    }

    return 0;
}