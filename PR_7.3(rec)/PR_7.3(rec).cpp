#include <iostream>
#include <iomanip>
#include <time.h>

using namespace std;

void Create(int** a, const int rowCount, const int colCount, const int Low, const int High);
void Input(int** a, const int rowCount, const int colCount, int rowIndex, int colIndex);
void Print(int** a, const int rowCount, const int colCount, int rowIndex, int colIndex);
int Part1_Count(int** a, const int rowCount, const int colCount, int rowIndex, int colIndex);
void Part2_SaddlePointRow(int** a, const int rowCount, const int colCount, int& No, const int rowNo, int colNo);
void Part2_SaddlePointRows(int** a, const int rowCount, const int colCount, int& No, int rowNo);
bool IsMaxInRowN(int** a, const int rowNo, const int max, const int colCount, int colNo);
bool IsMinInColK(int** a, const int colNo, const int min, const int rowCount, int rowNo);

int main()
{
    srand((unsigned)time(NULL));

    int Low = -17;
    int High = 15;
    int rowCount, colCount;

    cout << "rowCount = "; cin >> rowCount;
    cout << "colCount = "; cin >> colCount;

    int** a = new int* [rowCount];
    for (int i = 0; i < rowCount; i++)
        a[i] = new int[colCount];

    Create(a, rowCount, colCount, Low, High);
    //Input(a, rowCount, colCount, 0, 0);
    Print(a, rowCount, colCount, 0, 0);

    int sum = Part1_Count(a, rowCount, colCount, 0, 0);
    if (sum > 0)
        cout << "Sum = " << sum << endl;
    else
        cout << "There are no negative elements" << endl;
    cout << endl;
    
    cout << "Saddle points: max in row & min in col" << endl;
    cout << setw(4) << "No" << setw(6) << "Row" << setw(6) << "Col" << endl;

    int No = 0;
    Part2_SaddlePointRows(a, rowCount, colCount, No, 0);
    cout << endl;

    for (int i = 0; i < rowCount; i++)
        delete[] a[i];
    delete[] a;

    return 0;
}

void Create(int** a, const int rowCount, const int colCount, const int Low, const int High)
{
    if (rowCount <= 0 || colCount <= 0)
        return;

    a[rowCount - 1][colCount - 1] = Low + rand() % (High - Low + 1);
    Create(a, rowCount, colCount - 1, Low, High);
    Create(a, rowCount - 1, colCount, Low, High);
}

void Input(int** a, const int rowCount, const int colCount, int rowIndex, int colIndex)
{
    if (rowIndex >= rowCount)
        return;

    if (colIndex < colCount)
    {
        cout << "a[" << rowIndex << "][" << colIndex << "] = ";
        cin >> a[rowIndex][colIndex];
        Input(a, rowCount, colCount, rowIndex, colIndex + 1);
    }
    else
    {
        Input(a, rowCount, colCount, rowIndex + 1, 0);
    }
}

void Print(int** a, const int rowCount, const int colCount, int rowIndex, int colIndex)
{
    if (rowIndex >= rowCount)
        return;

    if (colIndex < colCount)
    {
        cout << setw(4) << a[rowIndex][colIndex];
        Print(a, rowCount, colCount, rowIndex, colIndex + 1);
    }
    else
    {
        cout << endl;
        Print(a, rowCount, colCount, rowIndex + 1, 0);
    }
}

int Part1_Count(int** a, const int rowCount, const int colCount, int rowIndex, int colIndex)
{
    if (rowIndex >= rowCount)
        return 0;

    if (colIndex < colCount)
    {
        if (a[rowIndex][colIndex] < 0)
            return Part1_Count(a, rowCount, colCount, rowIndex, colIndex + 1);
        else
            return a[rowIndex][colIndex] + Part1_Count(a, rowCount, colCount, rowIndex, colIndex + 1);
    }
    else
    {
        return Part1_Count(a, rowCount, colCount, rowIndex + 1, 0);
    }
}

bool IsMaxInRowN(int** a, const int rowNo, const int max, const int colCount, int colNo)
{
    if (a[rowNo][colNo] > max)
        return false;
    if (colNo < colCount - 1)
        return IsMaxInRowN(a, rowNo, max, colCount, colNo + 1);
    else
        return true;
}
bool IsMinInColK(int** a, const int colNo, const int min, const int rowCount, int rowNo)
{
    if (a[rowNo][colNo] < min)
        return false;
    if (rowNo < rowCount - 1)
        return IsMinInColK(a, colNo, min, rowCount, rowNo + 1);
    else
        return true;
}
void Part2_SaddlePointRow(int** a, const int rowCount, const int colCount, int& No, const int rowNo, int colNo)
{
    if (IsMaxInRowN(a, rowNo, a[rowNo][colNo], colCount, 0) &&
        IsMinInColK(a, colNo, a[rowNo][colNo], rowCount, 0))
    {
        cout << setw(4) << ++No << setw(6) << rowNo << setw(6) << colNo << endl;
    }
    if (colNo < colCount - 1)
        Part2_SaddlePointRow(a, rowCount, colCount, No, rowNo, colNo + 1);
}
void Part2_SaddlePointRows(int** a, const int rowCount, const int colCount, int& No, int rowNo)
{
    Part2_SaddlePointRow(a, rowCount, colCount, No, rowNo, 0);
    if (rowNo < rowCount - 1)
        Part2_SaddlePointRows(a, rowCount, colCount, No, rowNo + 1);
}