#pragma once
#include "Canvas.h"
#define DIM 40

class Monster {
    string name, icon; // 몬스터 이름과 아이콘
    int x, y, nItem;   // 현재 위치와 먹은 아이템 수
    int nEnergy;       // 몬스터의 에너지 (문제 1)
    static int count;  // 몬스터 수를 추적하는 정적 변수 (문제 4)

    void clip(int maxx, int maxy) {
        if (x < 0) x = 0;
        if (x >= maxx) x = maxx - 1;
        if (y < 0) y = 0;
        if (y >= maxy) y = maxy - 1;
    }
    void eat(int** map) {
        if (map[y][x] == 1) {
            map[y][x] = 0;
            nItem++;
            nEnergy += 10; // 아이템을 먹으면 에너지 증가 (문제 1)
        } else {
            nEnergy--; // 이동 시 에너지 감소 (문제 1)
        }
    }
public:
    Monster(string n = "몬스터", string i = "★", int px = 0, int py = 0)
        : name(n), icon(i), x(px), y(py), nItem(0), nEnergy(100) { // 에너지 초기화 (문제 1)
        count++; // 몬스터 생성 시 카운트 증가 (문제 4)
    }
    ~Monster() { 
        cout << "\t" << name << icon << " 사라짐...\n"; 
        count--; // 몬스터 소멸 시 카운트 감소 (문제 4)
    }

    void draw(Canvas& canvas) { canvas.draw(x, y, icon); }
    void move(int** map, int maxx, int maxy) {
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
        cout << "\t" << name << icon << ": 아이템=" << nItem 
             << ", 에너지=" << nEnergy << endl; // 에너지 출력 추가 (문제 1)
    }
    int getEnergy() { return nEnergy; } // 에너지 반환 함수 (문제 2)
    static void printCount() { 
        cout << "전체 몬스터 수 = " << count << endl; // 몬스터 수 출력 (문제 4)
    }
};

int Monster::count = 0; // 정적 멤버 변수 초기화 (문제 4)