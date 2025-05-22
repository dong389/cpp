#ifndef VARIOUS_MONSTERS_H
#define VARIOUS_MONSTERS_H

#include "Monster.h"
#include <iostream>
#include <cstdlib>
#include <string>

class Zombie : public Monster {
public:
    Zombie(std::string n = "허접좀비", std::string i = "★", int x = 0, int y = 0)
        : Monster(n, i, x, y) {}
    ~Zombie() { std::cout << " Zombie"; }
};

class Vampire : public Monster {
public:
    Vampire(std::string n = "뱀파이어", std::string i = "♠", int x = 0, int y = 0)
        : Monster(n, i, x, y) {}
    ~Vampire() { std::cout << " Vampire"; }

    void move(int** map, int maxx, int maxy) {
        if (map == nullptr || maxx <= 0 || maxy <= 0) return;
        int dir = rand() % 4;
        if (dir == 0) x--;
        else if (dir == 1) x++;
        else if (dir == 2) y--;
        else y++;
        clip(maxx, maxy);
        eat(map, maxx, maxy);
    }
};

class KGhost : public Monster {
public:
    KGhost(std::string n = "처녀귀신", std::string i = "♣", int x = 0, int y = 0)
        : Monster(n, i, x, y) {}
    ~KGhost() { std::cout << " KGhost"; }

    void move(int** map, int maxx, int maxy) {
        if (map == nullptr || maxx <= 0 || maxy <= 0) return;
        x = rand() % maxx;
        y = rand() % maxy;
        clip(maxx, maxy);
        eat(map, maxx, maxy);
    }
};

class Jiangshi : public Monster {
protected:
    bool bHori;
public:
    Jiangshi(std::string n = "뛰뛰강시", std::string i = "♦", int x = 0, int y = 0, bool bH = true)
        : Monster(n, i, x, y), bHori(bH) {}
    ~Jiangshi() { std::cout << " Jiangshi"; }

    void move(int** map, int maxx, int maxy) {
        if (map == nullptr || maxx <= 0 || maxy <= 0) return;
        int dir = rand() % 2;
        int jump = rand() % 2 + 1;
        if (bHori) x += (dir == 0 ? -jump : jump);
        else y += (dir == 0 ? -jump : jump);
        clip(maxx, maxy);
        eat(map, maxx, maxy);
    }
};

class Smombi : public Monster {
public:
    Smombi(std::string n = "스몸비", std::string i = "☎", int x = 0, int y = 0)
        : Monster(n, i, x, y) {}
    ~Smombi() { std::cout << " Smombi"; }

    void move(int** map, int maxx, int maxy) {
        if (map == nullptr || maxx <= 0 || maxy <= 0) return;
        int dir = rand() % 4;
        switch (dir) {
        case 0: x++; y--; break; // 우상
        case 1: x++; y++; break; // 우하
        case 2: x--; y++; break; // 좌하
        case 3: x--; y--; break; // 좌상
        }
        clip(maxx, maxy);
        eat(map, maxx, maxy);
    }
};

class Siangshi : public Jiangshi {
    int moveCount;
    static const int SWITCH_INTERVAL = 5; // 5번 이동마다 방향 전환
public:
    Siangshi(std::string n = "샹시", std::string i = "♢", int x = 0, int y = 0, bool bH = true)
        : Jiangshi(n, i, x, y, bH), moveCount(0) {}
    ~Siangshi() { std::cout << " Siangshi"; }

    void move(int** map, int maxx, int maxy) {
        if (map == nullptr || maxx <= 0 || maxy <= 0) return;
        moveCount++;
        if (moveCount >= SWITCH_INTERVAL) {
            bHori = !bHori; // 가로/세로 전환
            moveCount = 0;
        }
        Jiangshi::move(map, maxx, maxy);
    }
};

class Gumiho : public Monster {
public:
    Gumiho(std::string n = "구미호", std::string i = "♡", int x = 0, int y = 0)
        : Monster(n, i, x, y) {}
    ~Gumiho() { std::cout << " Gumiho"; }

    void move(int** map, int maxx, int maxy) {
        if (map == nullptr || maxx <= 0 || maxy <= 0) return;
        int dir = rand() % 4;
        switch (dir) {
        case 0: x++; y--; break; // 우상
        case 1: x++; y++; break; // 우하
        case 2: x--; y++; break; // 좌하
        case 3: x--; y--; break; // 좌상
        }
        clip(maxx, maxy);
        eat(map, maxx, maxy);
    }
};

#endif // VARIOUS_MONSTERS_H_2025