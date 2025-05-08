#pragma once
#include <iostream>
#include <string>
#include <algorithm> // std::max 사용을 위해 추가
#define DIM 40

using namespace std;

class Monster {
    string name, icon;      // 몬스터 이름과 화면 출력용 아이콘
    int x, y;               // 현재 위치
    int nItem;              // 먹은 아이템 개수
    int nEnergy;            // 에너지 (추가)

    void clip(int maxx, int maxy) { // 맵의 경계를 넘지 않도록 제한
        if (x < 0) x = 0;
        if (x >= maxx) x = maxx - 1;
        if (y < 0) y = 0;
        if (y >= maxy) y = maxy - 1;
    }

    void eat(int map[DIM][DIM]) { // 아이템을 먹거나 실패할 때 처리
        if (map[y][x] == 1) {     // 아이템이 있는 경우
            map[y][x] = 0;
            nItem++;
            nEnergy += 8;         // 에너지를 8 증가
        } else {                  // 아이템이 없는 경우
            nEnergy = max(0, nEnergy - 1); // 에너지를 1 감소 (최소값 0)
        }
    }

public:
    Monster(string n = "Monster", string i = "M", int px = 0, int py = 0)
        : name(n), icon(i), x(px), y(py), nItem(0), nEnergy(100) {}

    ~Monster() {
        cout << "\t" << name << " " << icon << " 소멸되었습니다~\n"; // 중복 제거
    }

    void draw(Canvas& canvas) {
        canvas.draw(x, y, icon);
    }

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
        cout << "\t" << name << icon 
             << ": 아이템=" << nItem 
             << ", 에너지=" << nEnergy << endl;
    }
};
