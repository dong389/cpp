#ifndef MONSTER_H
#define MONSTER_H

#include "Canvas.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

#define DIM 40

class Monster {
protected:
    std::string name, icon; // 몬스터 이름과 화면 출력용 아이콘
    int x, y, nItem;        // 현재 위치와 먹은 아이템 수

    void clip(int maxx, int maxy) {
        if (maxx <= 0 || maxy <= 0) return; // 유효하지 않은 맵 크기
        x = std::max(0, std::min(x, maxx - 1));
        y = std::max(0, std::min(y, maxy - 1));
    }

    void eat(int** map, int maxx, int maxy) {
        if (map == nullptr || x < 0 || x >= maxx || y < 0 || y >= maxy) return;
        if (map[y] != nullptr && map[y][x] == 1) {
            map[y][x] = 0;
            nItem++;
        }
    }

public:
    Monster(std::string n = "나괴물", std::string i = "★", int px = 0, int py = 0)
        : name(n), icon(i), x(px), y(py), nItem(0) {}

    virtual ~Monster() {
        std::cout << "\t" << name << icon << " 물러갑니다~~~\n";
    }

    void draw(Canvas& canvas) {
        canvas.draw(x, y, icon);
    }

    virtual void move(int** map, int maxx, int maxy) {
        if (map == nullptr || maxx <= 0 || maxy <= 0) return;
        switch (rand() % 8) {
        case 0: y--; break;           // 상
        case 1: x++; y--; break;      // 우상
        case 2: x++; break;           // 우
        case 3: x++; y++; break;      // 우하
        case 4: y++; break;           // 하
        case 5: x--; y++; break;      // 좌하
        case 6: x--; break;           // 좌
        case 7: x--; y--; break;      // 좌상
        }
        clip(maxx, maxy);
        eat(map, maxx, maxy);
    }

    void print() {
        std::cout << "\t" << name << icon << ":" << nItem << std::endl;
    }

    int getX() const { return x; }
    int getY() const { return y; }
};

#endif // MONSTER_H_2025