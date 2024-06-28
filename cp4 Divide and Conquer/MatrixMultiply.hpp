#include<vector>
#include <iostream>
using namespace std;

vector<vector<int>> MatrixMultiplication(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;
}



// sum of two matrices
// both matrices shall have nxn size
vector<vector<int>> MatrixSummation(vector<vector<int>>& MatrixA,
                                    vector<vector<int>>& MatrixB){

    int size = MatrixA.size();
    vector<vector<int>> MatrixC(size, vector<int>(size, 0));
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            MatrixC[i][j] = MatrixA[i][j] + MatrixB[i][j];

        }
    }
    return MatrixC;
}
// subtract matrices
vector<vector<int>> MatrixSubtraction(vector<vector<int>>& MatrixA,
                                    vector<vector<int>>& MatrixB){

    int size = MatrixA.size();
    vector<vector<int>> MatrixC(size, vector<int>(size, 0));
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            MatrixC[i][j] = MatrixA[i][j] - MatrixB[i][j];

        }
    }
    return MatrixC;
}

vector<vector<int>> StrassenRecursive(vector<vector<int>>& MatrixA,
                                       vector<vector<int>>& MatrixB){
    int MatrixSize = MatrixA.size();
    vector<vector<int>> MatrixC(MatrixSize, vector<int>(MatrixSize, 0));
    if(MatrixSize == 1){
        MatrixC[0][0] = MatrixA[0][0] * MatrixB[0][0];
        return MatrixC;
    }
    else{
        int NewSize = MatrixSize / 2;

        /// Initialize submatrices
        vector<vector<int>> MatrixA11(NewSize, vector<int>(NewSize, 0));
        vector<vector<int>> MatrixA12(NewSize, vector<int>(NewSize, 0));
        vector<vector<int>> MatrixA21(NewSize, vector<int>(NewSize, 0));
        vector<vector<int>> MatrixA22(NewSize, vector<int>(NewSize, 0));
        vector<vector<int>> MatrixB11(NewSize, vector<int>(NewSize, 0));
        vector<vector<int>> MatrixB12(NewSize, vector<int>(NewSize, 0));
        vector<vector<int>> MatrixB21(NewSize, vector<int>(NewSize, 0));
        vector<vector<int>> MatrixB22(NewSize, vector<int>(NewSize, 0));
        vector<vector<int>> MatrixC11(NewSize, vector<int>(NewSize, 0));
        vector<vector<int>> MatrixC12(NewSize, vector<int>(NewSize, 0));
        vector<vector<int>> MatrixC21(NewSize, vector<int>(NewSize, 0));
        vector<vector<int>> MatrixC22(NewSize, vector<int>(NewSize, 0));

        // divide matrices into four submatrices
        for (int i = 0; i < NewSize; i++) {
            for (int j = 0; j < NewSize; j++) {
                MatrixA11[i][j] = MatrixA[i][j];
                MatrixA12[i][j] = MatrixA[i][j + NewSize];
                MatrixA21[i][j] = MatrixA[i + NewSize][j];
                MatrixA22[i][j] = MatrixA[i + NewSize][j + NewSize];

                MatrixB11[i][j] = MatrixB[i][j];
                MatrixB12[i][j] = MatrixB[i][j + NewSize];
                MatrixB21[i][j] = MatrixB[i + NewSize][j];
                MatrixB22[i][j] = MatrixB[i + NewSize][j + NewSize];
            }
        }
        vector<vector<int>> s1 = MatrixSubtraction(MatrixB12,MatrixB22);
        vector<vector<int>> s2 = MatrixSummation(MatrixA11,MatrixA12);
        vector<vector<int>> s3 = MatrixSummation(MatrixA21,MatrixA22);
        vector<vector<int>> s4 = MatrixSubtraction(MatrixB21,MatrixB11);
        vector<vector<int>> s5 = MatrixSummation(MatrixA11,MatrixA22);
        vector<vector<int>> s6 = MatrixSummation(MatrixB11,MatrixB22);
        vector<vector<int>> s7 = MatrixSubtraction(MatrixA12,MatrixA22);
        vector<vector<int>> s8 = MatrixSummation(MatrixB21,MatrixB22);
        vector<vector<int>> s9 = MatrixSubtraction(MatrixA11,MatrixA21);
        vector<vector<int>> s10 = MatrixSummation(MatrixB11,MatrixB12);

        //recursive calls of algorithm:
        vector<vector<int>> r1 = StrassenRecursive(MatrixA11,s1);
        vector<vector<int>> r2 = StrassenRecursive(s2, MatrixB22);
        vector<vector<int>> r3 = StrassenRecursive(s3, MatrixB11);
        vector<vector<int>> r4 = StrassenRecursive(MatrixA22, s4);
        vector<vector<int>> r5 = StrassenRecursive(s5, s6);
        vector<vector<int>> r6 = StrassenRecursive(s7,s8);
        vector<vector<int>> r7 = StrassenRecursive(s9,s10);


        // Compute submatrices for Strassen's algorithm
        vector<vector<int>> TempMatrixA = MatrixSummation(r5, r4);
        vector<vector<int>> TempMatrixB = MatrixSummation(TempMatrixA, r6);

        MatrixC11 = MatrixSubtraction(TempMatrixB, r2);
        MatrixC12 = MatrixSummation(r1, r2);
        MatrixC21 = MatrixSummation(r3, r4);

        TempMatrixA = MatrixSummation(r5, r1);
        TempMatrixB = MatrixSubtraction(TempMatrixA, r3);
        MatrixC22 = MatrixSubtraction(TempMatrixB, r7);


        //assembling the matrix C
        for (int i = 0; i < NewSize ; i++) {
            for (int j = 0 ; j < NewSize ; j++) {
                MatrixC[i][j] = MatrixC11[i][j];
                MatrixC[i][j + NewSize] = MatrixC12[i][j];
                MatrixC[i + NewSize][j] = MatrixC21[i][j];
                MatrixC[i + NewSize][j + NewSize] = MatrixC22[i][j];
            }
        }



    }

    return MatrixC;
}


// Helper function to sum two matrices
vector<vector<int>> MatrixSummation(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }

    return C;
}

// Function to compare two matrices
bool AreMatricesEqual(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    if (n != B.size()) return false;

    for (int i = 0; i < n; ++i) {
        if (A[i].size() != B[i].size()) return false;
        for (int j = 0; j < n; ++j) {
            if (A[i][j] != B[i][j]) return false;
        }
    }

    return true;
}

// Function to display a matrix
void DisplayMatrix(const vector<vector<int>>& matrix) {
    int n = matrix.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Test cases
void TestStrassenRecursive() {
    vector<vector<int>> A = {{1, 2}, {3, 4}};
    vector<vector<int>> B = {{5, 6}, {7, 8}};

    cout << "Matrix A:" << endl;
    DisplayMatrix(A);
    cout << "Matrix B:" << endl;
    DisplayMatrix(B);

    vector<vector<int>> expected = MatrixMultiplication(A, B);
    vector<vector<int>> result = StrassenRecursive(A, B);

    cout << "Expected Result:" << endl;
    DisplayMatrix(expected);
    cout << "Result from StrassenRecursive:" << endl;
    DisplayMatrix(result);

    if (AreMatricesEqual(expected, result)) {
        cout << "Test passed!" << endl;
    } else {
        cout << "Test failed!" << endl;
    }
}
/*
int main() {
    TestStrassenRecursive();
    return 0;
}
*/