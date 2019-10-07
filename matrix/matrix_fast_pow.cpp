#include <iostream>
#include <cstdlib>

using namespace std;

/*
matrix a with dimension (m,s)
matrix b with dimension (s,n)
*/
int** MatrixMultiply(int** a, int** b, int m, int s, int n) {
    int** result = new int*[m];
    for (int i = 0; i < m; ++i) {
        result[i] = new int[n];
        memset(result[i], 0, sizeof(int) * n);
    }

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < s; ++k) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    return result;
}

void DeleteArray(int** a, int dim_m) {
    if (a != nullptr) {
        for (int i = 0; i < dim_m; ++i) {
            delete[] a[i];
        }
        delete[] a;
        a = nullptr;
    }
}

int** CreateMatrix(int dim_m, int dim_n) {
    int** a = new int* [dim_m];
    for (int i = 0; i < dim_m; ++i) {
        a[i] = new int[dim_n];
    }
    return a;
}

void PrintMatrix(int** a, int dim_m, int dim_n) {
    for (int i = 0; i < dim_m; ++i) {
        for (int j = 0; j < dim_n; ++j) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
}


double NumberPower(double base, int exponent) {
    if (base && exponent == 0) {
        return 1;
    } else if (base == 0 && exponent == 0) {
        exit(1);
    }

    bool isNegativeExponent = false;
    if (exponent < 0) {
        isNegativeExponent = true;
        exponent = -exponent;
    }

    double res = 1;
    while (exponent) {
        if (exponent & 1) {
            res *= base;
        }
        base *= base;
        exponent >>= 1;
    }
    return isNegativeExponent ? 1.0 / res : res;
}

/*
Matrix base with dimension (dim, dim)
*/
int** MatrixPower(int** base, int dim, int exponent) {
    int** res = new int* [dim];
    // Initialize res as a identity matrix
    for (int i = 0; i < dim; ++i) {
        res[i] = new int[dim];
        memset(res[i], 0, sizeof(int) * dim);
        res[i][i] = 1;
    }

    int** oldMatrix = nullptr;
    while (exponent) {
        if (exponent & 1) {
            oldMatrix = res;
            res = MatrixMultiply(res, base, dim, dim, dim);
            DeleteArray(oldMatrix, dim);
        }
        oldMatrix = base;
        base = MatrixMultiply(base, base, dim, dim, dim);
        DeleteArray(oldMatrix, dim);
        exponent >>= 1;
    }

    return res;
}

int main() {
    double x;
    int n;
    cout << "Input base and exponent: ";
    while (cin >> x >> n) {
        cout << "Result: ";
        cout << NumberPower(x, n) << endl;
        break;
    }

    cout << "========" << endl;

    int dim_m;
    int dim_s;
    int dim_n;
    cout << "Row of the first matrix: ";
    cin >> dim_m;
    if (dim_m < 1) {
        cout << "Invalid matrix size!" << endl;
        exit(1);
    }
    cout << "Column of the first matrix or Row of the second matrix: ";
    cin >> dim_s;
    if (dim_s < 1) {
        cout << "Invalid matrix size!" << endl;
        exit(1);
    }
    cout << "Column of the second matrix: ";
    cin >> dim_n;
    if (dim_n < 1) {
        cout << "Invalid matrix size!" << endl;
        exit(1);
    }

    int i, j;
    int** a = CreateMatrix(dim_m, dim_s);
    int** b = CreateMatrix(dim_s, dim_n);

    cout << "Matrix a: " << endl;
    for (i = 0; i < dim_m; ++i) {
        for (j = 0; j <dim_s; ++j) {
            cin >> a[i][j];
        }
    }
    cout << "Matrix b: " << endl;
    for (i = 0; i < dim_s; ++i) {
        for (j = 0; j <dim_n; ++j) {
            cin >> b[i][j];
        }
    }

    int** res = MatrixMultiply(a, b, dim_m, dim_s, dim_n);
    cout << "a * b =" << endl;
    PrintMatrix(res, dim_m, dim_n);

    DeleteArray(a, dim_m);
    DeleteArray(b, dim_s);
    DeleteArray(res, dim_m);

    cout << "========" << endl;

    int dim;
    cout << "Matrix base with row, col = ";
    cin >> dim;
    if (dim < 1) {
        cout << "Invalid matrix size!" << endl;
        exit(1);
    }
    cout << "Matrix base: " << endl;
    int** base = CreateMatrix(dim, dim);
    for (i = 0; i < dim; ++i) {
        for (j = 0; j < dim; ++j) {
            cin >> base[i][j]; 
        }
    }
    int exponent;
    cout << "Exponent = ";
    cin >> exponent;
    if (exponent < 0) {
        cout << "Invalid exponent!" << endl;
    }
    int** powerResult = MatrixPower(base, dim, exponent);
    cout << "The exponent power of matrix base:" << endl;
    PrintMatrix(powerResult, dim, dim);

    return 0;
}

