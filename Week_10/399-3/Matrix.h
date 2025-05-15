#pragma once
#include <iostream>
#include <iomanip>
using namespace std;

class Matrix {
    int rows, cols;  // 행과 열의 크기
    int** mat;       // 2차원 배열 데이터
public:
    Matrix(int r = 0, int c = 0) : rows(r), cols(c), mat(nullptr) {
        mat = new int*[rows];
        for (int i = 0; i < rows; i++)
            mat[i] = new int[cols];
    }
    ~Matrix() {
        if (mat != nullptr) {
            for (int i = 0; i < rows; i++)
                delete[] mat[i];
            delete[] mat;
        }
    }
    int& elem(int x, int y) { return mat[y][x]; }
    int Rows() const { return rows; }
    int Cols() const { return cols; }
    int** Data() { return mat; }
    void print(const char* str = "Matrix") const {
        cout << str << " " << rows << "x" << cols << endl;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++)
                cout << setw(4) << mat[i][j];
            cout << "\n";
        }
    }
    void setRand(int val = 100) {
        if (mat != nullptr) {
            for (int i = 0; i < rows; i++)
                for (int j = 0; j < cols; j++)
                    mat[i][j] = rand() % val;
        }
    }
};