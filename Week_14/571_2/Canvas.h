#pragma once
#include <iostream>
#include <string>
#include <ncurses.h>
#include "Point.h"

#define MAXLINES 100

class Canvas {
    std::string line[MAXLINES];
    int xMax, yMax;
public:
    Canvas(int nx = 10, int ny = 10) : xMax(nx), yMax(ny) {
        if (yMax > MAXLINES) {
            throw std::out_of_range("Canvas yMax exceeds MAXLINES");
        }
        for (int y = 0; y < yMax; y++) {
            line[y] = std::string(xMax * 2, ' ');
        }
    }

    void draw(int x, int y, const std::string& val) {
        if (x >= 0 && y >= 0 && x < xMax && y < yMax) {
            line[y].replace(x * 2, 2, val);
        }
    }

    void draw(Point& p, const std::string& val) {
        draw(p[0], p[1], val); // 수정: p.x, p.y 사용
    }

    void reset(const std::string& val = ". ") { // 수정: clear -> reset
        for (int y = 0; y < yMax; y++) {
            for (int x = 0; x < xMax; x++) {
                draw(x, y, val);
            }
        }
    }

    void print(const char* title = "<My Canvas>") {
        clear(); // ncurses clear screen
        mvprintw(0, 0, "%s", title);
        for (int y = 0; y < yMax; y++) {
            mvprintw(y + 1, 0, "%s", line[y].c_str());
        }
        refresh();
    }
};