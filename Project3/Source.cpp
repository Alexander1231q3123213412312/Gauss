#include <iostream>
#include <cmath>

using namespace std;

void inputMatrix(double**& matrix, int rowM, int columnM) {
    matrix = new double* [rowM];
    for (int i = 0; i < rowM; i++) {
        matrix[i] = new double[columnM];
        cout << "Введите " << columnM << " знач. " << i + 1 << " строки через пробел" << endl;
        for (int j = 0; j < columnM; j++) {
            cin >> matrix[i][j];
        }
    }
}

void printMatrix(double** matrix, int rowM, int columnM) {
    for (int i = 0; i < rowM; i++) {
        for (int j = 0; j < columnM; j++) {
            cout << fixed << matrix[i][j];
        }
        cout << endl;
    }
}

void deleteMatrix(double** matrix, int sizeM)
{
    for (int i = 0; i < sizeM; i++)
        delete[] matrix[i];
    delete[] matrix;
}

double* gaussMethod(double** matrix, double* b, int sizeM)  //b - вектор свободных коэффициентов
{
    double* x, maxMultiplier, temp, temp2;
    int k, index;
    const double eps = 0.000000001;  // точность
    x = new double[sizeM];
    k = 0;
    while (k < sizeM) {
        // Поиск строки с максимальным по модулю элементом
        maxMultiplier = fabs(matrix[k][k]);
        index = k;
        for (int i = k + 1; i < sizeM; i++) {
            if (fabs(matrix[i][k]) > maxMultiplier) {
                maxMultiplier = fabs(matrix[i][k]);
                index = i;
            }
        }
        // проверка на нулевой столбец
        if (maxMultiplier <= eps) {
            cout << "\nРешение получить невозможно - вырожденная матрица\n";
            return 0;
        }
        // Перестановка строк
        for (int j = 0; j < sizeM; j++) {
            swap(matrix[k][j], matrix[index][j]);
        }
        swap(b[k], b[index]);
        temp2 = matrix[k][k];
        // создаем единичную матрицу
        for (int i = 0; i < sizeM; i++)
        {
            temp = matrix[i][k];
            if (fabs(temp) <= eps) {
                matrix[i][k] = 0;
            }
            if (i == k) {
                continue; // уравнение не вычитать само из себя
            }
            for (int j = 0; j < sizeM; j++) {
                matrix[i][j] -= temp * (matrix[k][j] / temp2);
            }
            b[i] -= temp * (b[k] / temp2);
        }
        k++;
    }
    // обратная подстановка
    for (k = sizeM - 1; k >= 0; k--) {
        temp2 = matrix[k][k];
        matrix[k][k] /= temp2;
        b[k] /= temp2;
        x[k] = b[k];
    }
    return x;
}


int main()
{
    setlocale(LC_ALL, "RUS");
    double** matrixA;
    double* solution, * freeCoeff;
    int row = 0, ans = 0;
    cout << "Введите порядок матрицы: ";
    cin >> row;
    freeCoeff = new double[row];
    cout << "Введем коэффициенты при Х: " << endl;
    inputMatrix(matrixA, row, row);
    cout << "Введем свободные коэффициенты через пробел: " << endl;
    for (int i = 0; i < row; i++) {
        cin >> freeCoeff[i];

        solution = gaussMethod(matrixA, freeCoeff, row);

        if (!solution) {
            deleteMatrix(matrixA, row);
            delete[] solution;
            delete[] freeCoeff;
            continue;
        }
        cout << "\n\n";
        printMatrix(matrixA, row, row);

        cout << "\nРешение СЛАУ: Х=[";
        for (int i = 0; i < row; i++) {
            cout << fixed << solution[i];
        }
        cout << "]" << endl << endl;
    }
}
