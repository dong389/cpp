#pragma once
#include "Canvas.h"
#define DIM 40

class Monster {
    string name, icon;    // 몬스터의 이름과 아이콘
    int x, y, nItem;      // 몬스터의 위치와 먹은 아이템 개수
    int nEnergy;          // 몬스터의 에너지

    void clip(int maxx, int maxy) {
        if (x < 0) x = 0;
        if (x >= maxx) x = maxx - 1;
        if (y < 0) y = 0;
        if (y >= maxy) y = maxy - 1;
    }
    void eat(int map[DIM][DIM]) {
        if (map[y][x] == 1) {
            map[y][x] = 0;
            nItem++;
            nEnergy += 8;  // 아이템을 먹으면 에너지가 8 증가
        } else {
            nEnergy -= 1;  // 아이템을 먹지 못하면 에너지가 1 감소
            if (nEnergy < 0) nEnergy = 0;  // 에너지의 최솟값은 0
        }
    }
public:
    Monster(string n = "Monster", string i = "X", int px = 0, int py = 0)
        : name(n), icon(i), x(px), y(py), nItem(0), nEnergy(100) {}  // 에너지는 100으로 초기화

    Monster(const Monster& other)  // 복사 생성자 추가
        : name(other.name), icon(other.icon), x(other.x), y(other.y), 
          nItem(other.nItem), nEnergy(other.nEnergy) {}

    ~Monster() { cout << "\t" << name << icon << "가 사라졌습니다.\n"; }

    void draw(Canvas &canvas) { canvas.draw(x, y, icon); }
    void move(int map[DIM][DIM], int maxx, int maxy) {
        switch (rand() % 8) {
        case 0: y--; break;
        case 1: x++; y--; break;
        case 2: x++; break;
        case 3: x++; y++; break;
        case 4: y++; break;
        case 5: x--; y++; break;
        case 6: x--; break;
        case 7: x--; y--; break;
        }
        clip(maxx, maxy);
        eat(map);
    }
    void print() { 
        cout << "\t" << name << icon << ": " << nItem << "개 아이템, 에너지: " << nEnergy << endl; 
    }
};
