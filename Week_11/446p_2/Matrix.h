#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

class Matrix {
    int rows, cols;     // 행과 열의 크기
    int** mat;          // 동적 행렬 데이터

public:
    Matrix(int r = 0, int c = 0) : rows(r), cols(c), mat(nullptr) {
        if (r > 0 && c > 0) {
            try {
                mat = new int*[rows];
                for (int i = 0; i < rows; i++) {
                    mat[i] = new int[cols](); // 0으로 초기화
                }
            } catch (const std::bad_alloc&) {
                std::cerr << "Error: Matrix memory allocation failed\n";
                rows = 0;
                cols = 0;
                mat = nullptr;
            }
        }
    }

    ~Matrix() {
        if (mat != nullptr) {
            for (int i = 0; i < rows; i++) {
                delete[] mat[i];
            }
            delete[] mat;
        }
    }

    int& elem(int x, int y) {
        if (mat == nullptr || x < 0 || x >= cols || y < 0 || y >= rows) {
            throw std::out_of_range("Matrix index out of bounds");
        }
        return mat[y][x];
    }

    int Rows() const { return rows; }
    int Cols() const { return cols; }

    int** Data() { return mat; } // 캡슐화 문제 주의

    void print(const std::string& str = "Mat") {
        std::cout << str << " " << rows << "x" << cols << std::endl;
        if (mat == nullptr) {
            std::cout << "Empty matrix" << std::endl;
            return;
        }
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                std::cout << std::setw(4) << mat[i][j];
            }
            std::cout << "\n";
        }
    }

    void setRand(int val = 100) {
        if (mat != nullptr) {
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    mat[i][j] = rand() % val;
                }
            }
        }
    }
};

#endif // MATRIX_H_2025