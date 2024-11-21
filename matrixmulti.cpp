#include <iostream>
#include <pthread.h>
#include <vector>

using namespace std;

// Global variables for dimensions
int ROWS_A, COLS_A, ROWS_B, COLS_B;

// Matrices (dynamically allocated)
vector<vector<int>> A, B, C;

// Structure to hold data for each thread
struct ThreadData {
    int row;
    int col;
};

// Function to perform multiplication for one element
void* multiplyElement(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    int row = data->row;
    int col = data->col;

    C[row][col] = 0;
    for (int k = 0; k < COLS_A; k++) {
        C[row][col] += A[row][k] * B[k][col];
    }

    pthread_exit(0);
}

int main() {
    // Input dimensions of matrices
    cout << "Enter dimensions of Matrix A (rows and columns): ";
    cin >> ROWS_A >> COLS_A;
    cout << "Enter dimensions of Matrix B (rows and columns): ";
    cin >> ROWS_B >> COLS_B;

    // Check if matrix multiplication is possible
    if (COLS_A != ROWS_B) {
        cerr << "Matrix multiplication not possible: Incompatible dimensions." << endl;
        return -1;
    }

    // Initialize matrices
    A.resize(ROWS_A, vector<int>(COLS_A));
    B.resize(ROWS_B, vector<int>(COLS_B));
    C.resize(ROWS_A, vector<int>(COLS_B));

    // Input values for Matrix A
    cout << "Enter elements of Matrix A:" << endl;
    for (int i = 0; i < ROWS_A; i++) {
        for (int j = 0; j < COLS_A; j++) {
            cin >> A[i][j];
        }
    }

    // Input values for Matrix B
    cout << "Enter elements of Matrix B:" << endl;
    for (int i = 0; i < ROWS_B; i++) {
        for (int j = 0; j < COLS_B; j++) {
            cin >> B[i][j];
        }
    }

    pthread_t threads[ROWS_A][COLS_B];
    ThreadData threadData[ROWS_A][COLS_B];

    // Create threads to compute each element of the resultant matrix
    for (int i = 0; i < ROWS_A; i++) {
        for (int j = 0; j < COLS_B; j++) {
            threadData[i][j].row = i;
            threadData[i][j].col = j;

            int ret = pthread_create(&threads[i][j], nullptr, multiplyElement, &threadData[i][j]);
            if (ret != 0) {
                cerr << "Error: Unable to create thread." << endl;
                return -1;
            }
        }
    }

    // Wait for all threads to finish
    for (int i = 0; i < ROWS_A; i++) {
        for (int j = 0; j < COLS_B; j++) {
            pthread_join(threads[i][j], nullptr);
        }
    }

    // Print the resultant matrix
    cout << "Resultant Matrix C:" << endl;
    for (int i = 0; i < ROWS_A; i++) {
        for (int j = 0; j < COLS_B; j++) {
            cout << C[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}