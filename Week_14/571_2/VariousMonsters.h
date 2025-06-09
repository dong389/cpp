#pragma once
#include "Monster.h"
#include <iostream>
#include <string>

class Zombie : public Monster {
public:
    Zombie(std::string n = "허접좀비", std::string i = "×", int x = 0, int y = 0)
        : Monster(n, i, x, y) {}
    ~Zombie() { std::cout << "[Zombie]"; }
};

class Vampire : public Monster {
public:
    Vampire(std::string n = "뱀파이어", std::string i = "⊙", int x = 0, int y = 0)
        : Monster(n, i, x, y) {}
    ~Vampire() { std::cout << "[Vampire]"; }

    void move(int** map, int maxx, int maxy) {
        if (!isSleep()) {
            int dir = rand() % 4;
            if (dir == 0) p[0]--;
            else if (dir == 1) p[0]++;
            else if (dir == 2) p[1]--;
            else p[1]++;
            clip(maxx, maxy);
            eat(map);
        }
    }
};

class KGhost : public Monster {
public:
    KGhost(std::string n = "처녀귀신", std::string i = "♠", int x = 0, int y = 0)
        : Monster(n, i, x, y) {}
    ~KGhost() { std::cout << "[KGhost]"; }

    void move(int** map, int maxx, int maxy) {
        if (!isSleep()) {
            p = Point(rand() % maxx, rand() % maxy);
            clip(maxx, maxy);
            eat(map);
        }
    }
};

class Jiangshi : public Monster {
    bool bHori;
public:
    Jiangshi(std::string n = "대륙강시", std::string i = "♣", int x = 0, int y = 0, bool bH = true)
        : Monster(n, i, x, y), bHori(bH) {}
    ~Jiangshi() { std::cout << "[Jiangshi]"; }

    void move(int** map, int maxx, int maxy) {
        if (!isSleep()) {
            int dir = rand() % 2;
            int jump = rand() % 2 + 1;
            if (bHori)
                p[0] += (dir == 0) ? -jump : jump;
            else
                p[1] += (dir == 0) ? -jump : jump;
            clip(maxx, maxy);
            eat(map);
        }
    }
};