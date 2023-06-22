#include <iostream>
#include <vector>
#include <stdlib.h>
#include <ctime>
#include <iomanip>

using namespace std;

typedef vector<vector<int> > matrix;

matrix add(matrix A, matrix B)
{
    int n = A.size();
    matrix C(n, vector<int>(n));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}

matrix subtract(matrix A, matrix B)
{
    int n = A.size();
    matrix C(n, vector<int>(n));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    return C;
}

void printMatrix(matrix A)
{
    int size = A.size();
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cout << setw(size) << A[i][j];
        }
        cout << endl;
    }
}

matrix auto_fill_matrices(int size)
{
    matrix A(size, vector<int>(size));
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            A[i][j] = rand() % 10;
        }
    }
    return A;
}

matrix inputMatrix(int size)
{
    matrix A;
    int inp;
    for (int i = 0; i < size; i++)
    {
        vector<int> temp;
        cout << endl
             << "Enter the values for " << i + 1 << "th row:" << endl;
        for (int j = 0; j < size; j++)
        {
            cout << "For " << j + 1 << "th column: ";
            cin >> inp;
            temp.push_back(inp);
            cout << endl;
        }
        A.push_back(temp);
    }
    return A;
}

matrix strassen(matrix A, matrix B)
{
    int n = A.size();
    int halfSize = n / 2;

    // If we reach to a pair of matrix where both of them has only one value
    // then we will multiply the elements and store it in a new matrix C
    // and then return the matrix
    if (n == 1)
    {
        matrix C(1, vector<int>(1));
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }

    // Creating matrices into submatrices of half of the original size
    matrix A11(n / 2, vector<int>(n / 2)), A12(n / 2, vector<int>(n / 2)), A21(n / 2, vector<int>(n / 2)), A22(n / 2, vector<int>(n / 2));
    matrix B11(n / 2, vector<int>(n / 2)), B12(n / 2, vector<int>(n / 2)), B21(n / 2, vector<int>(n / 2)), B22(n / 2, vector<int>(n / 2));

    // Dividing the matrix into sub-matrices
    for (int i = 0; i < n / 2; i++)
    {
        for (int j = 0; j < n / 2; j++)
        {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + halfSize];
            A21[i][j] = A[i + halfSize][j];
            A22[i][j] = A[i + halfSize][j + halfSize];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + halfSize];
            B21[i][j] = B[i + halfSize][j];
            B22[i][j] = B[i + halfSize][j + halfSize];
        }
    }

    // Recursive calls to Strassen's Algorithm
    matrix M1 = strassen(add(A11, A22), add(B11, B22));
    matrix M2 = strassen(add(A21, A22), B11);
    matrix M3 = strassen(A11, subtract(B12, B22));
    matrix M4 = strassen(A22, subtract(B21, B11));
    matrix M5 = strassen(add(A11, A12), B22);
    matrix M6 = strassen(subtract(A21, A11), add(B11, B12));
    matrix M7 = strassen(subtract(A12, A22), add(B21, B22));

    // Calculate submatrices of result matrix C
    matrix C11 = subtract(add(add(M1, M4), M7), M5);
    matrix C12 = add(M3, M5);
    matrix C21 = add(M2, M4);
    matrix C22 = subtract(add(add(M1, M3), M6), M2);

    // Combining the matrices C11, C12, C21, C22 to form a bigger matrix
    // and returning it
    matrix C(n, vector<int>(n));
    for (int i = 0; i < n / 2; i++)
    {
        for (int j = 0; j < n / 2; j++)
        {
            C[i][j] = C11[i][j];
            C[i][j + halfSize] = C12[i][j];
            C[i + halfSize][j] = C21[i][j];
            C[i + halfSize][j + halfSize] = C22[i][j];
        }
    }
    return C;
}

int main()
{
    matrix A, B;
    int n, m, inp;
    char choice;
    srand(time(NULL));
    cout << endl
         << "Enter the number of rows and columns in Matrix A: ";
    cin >> n;
    cout << endl
         << "Enter the number of rows and columns in Matrix B: ";
    cin >> m;

    if (n == m)
    {

        cout << endl
             << "\nDo you want to randomly generate the matrix(Y/N): ";
        cin >> choice;
        if (choice == 'Y' || choice == 'y')
        {
            A = auto_fill_matrices(n);
            cout << endl
                 << "The Matrix A is: " << endl;
            printMatrix(A); // Displaying Matrix A
            B = auto_fill_matrices(m);
            cout << endl
                 << "The Matrix B is: " << endl;
            printMatrix(B); // Displaying Matrix B
        }
        else
        {
            // Input for matrix A
            cout << endl
                 << "Enter the matrix elements for A" << endl;
            A = inputMatrix(n);
            cout << endl
                 << "The Matrix A is: " << endl;
            printMatrix(A); // Displaying Matrix A

            // Input for matrix B
            cout << endl
                 << "\nEnter the matrix elements for B" << endl;
            B = inputMatrix(m);
            cout << endl
                 << "The Matrix B is: " << endl;
            printMatrix(B); // Displaying Matrix B
        }
        matrix result = strassen(A, B);
        cout << endl
             << "\nThe Matrix Multiplication is: " << endl;
        printMatrix(result);
    }
    else
    {
        cout << endl
             << "Since the matrix order is not same, Therefore The two matrices cannot be multiplied using strassen's algorithm!!";
    }

    return 0;
}
