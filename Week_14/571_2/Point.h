#pragma once
#include <iostream>
#include <cmath>
#include <stdexcept>

class Point {
    int x, y; // 점의 x와 y 좌표 값
    friend class Monster; // Monster를 친구 클래스로 등록
    friend class Canvas;  // Canvas를 친구 클래스로 등록
public:
    Point(int xx = 0, int yy = 0) : x(xx), y(yy) {}

    int& operator[](int id) { // 인덱스 연산자
        if (id == 0) return x;
        if (id == 1) return y;
        throw std::out_of_range("Point index out of range");
    }

    operator double() const {
        return std::sqrt(static_cast<double>(x * x + y * y));
    }

    void clip(int maxx, int maxy) {
        if (x < 0) x = 0;
        if (x >= maxx) x = maxx - 1;
        if (y < 0) y = 0;
        if (y >= maxy) y = maxy - 1;
    }

    Point operator-() const {
        return Point(-x, -y);
    }

    bool operator==(const Point& p) const {
        return x == p.x && y == p.y;
    }

    bool operator!=(const Point& p) const {
        return x != p.x || y != p.y;
    }

    Point operator-(const Point& p) const {
        return Point(x - p.x, y - p.y);
    }

    Point operator+(const Point& p) const {
        return Point(x + p.x, y + p.y);
    }

    Point& operator+=(const Point& p) {
        x += p.x;
        y += p.y;
        return *this;
    }

    Point& operator-=(const Point& p) {
        x -= p.x;
        y -= p.y;
        return *this;
    }
};