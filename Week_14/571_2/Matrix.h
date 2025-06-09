#pragma once
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <stdexcept>

class Matrix {
    int rows, cols; // 행과 열의 크기
    int** mat;      // 데이터 행렬
public:
    Matrix(int r = 0, int c = 0) : rows(r), cols(c), mat(nullptr) {
        if (r > 0 && c > 0) {
            mat = new int*[rows];
            for (int i = 0; i < rows; i++)
                mat[i] = new int[cols](); // Initialize to zero
        }
    }

    Matrix(const Matrix& other) : rows(other.rows), cols(other.cols), mat(nullptr) {
        if (rows > 0 && cols > 0) {
            mat = new int*[rows];
            for (int i = 0; i < rows; i++) {
                mat[i] = new int[cols];
                for (int j = 0; j < cols; j++)
                    mat[i][j] = other.mat[i][j];
            }
        }
    }

    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            if (mat != nullptr) {
                for (int i = 0; i < rows; i++)
                    delete[] mat[i];
                delete[] mat;
            }
            rows = other.rows;
            cols = other.cols;
            mat = nullptr;
            if (rows > 0 && cols > 0) {
                mat = new int*[rows];
                for (int i = 0; i < rows; i++) {
                    mat[i] = new int[cols];
                    for (int j = 0; j < cols; j++)
                        mat[i][j] = other.mat[i][j];
                }
            }
        }
        return *this;
    }

    ~Matrix() {
        if (mat != nullptr) {
            for (int i = 0; i < rows; i++)
                delete[] mat[i];
            delete[] mat;
        }
    }

    int& elem(int x, int y) {
        if (x < 0 || x >= cols || y < 0 || y >= rows)
            throw std::out_of_range("Matrix index out of bounds");
        return mat[y][x];
    }

    int Rows() { return rows; }
    int Cols() { return cols; }
    int** Data() { return mat; }

    void print(const char* str = "Mat") {
        std::cout << str << " " << rows << "x" << cols << std::endl;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++)
                std::cout << std::setw(4) << mat[i][j];
            std::cout << "\n";
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