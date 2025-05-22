#ifndef MONSTER_WORLD_H
#define MONSTER_WORLD_H

#include "Canvas.h"
#include "VariousMonsters.h"
#include "Matrix.h"
#include <thread>
#include <chrono>
#include <cstdio>
#include <iostream>

#define MAXMONS 8

class MonsterWorld {
    Matrix world; // 맵 데이터
    int xMax, yMax, nMon, nMove;
    Monster* pMon[MAXMONS];
    Canvas canvas;

    int& Map(int x, int y) {
        if (x < 0 || x >= xMax || y < 0 || y >= yMax) {
            throw std::out_of_range("Map index out of bounds");
        }
        return world.elem(x, y);
    }

    bool isDone() { return countItems() == 0; }

    int countItems() {
        int nItems = 0;
        for (int y = 0; y < yMax; y++) {
            for (int x = 0; x < xMax; x++) {
                try {
                    if (Map(x, y) > 0) nItems++;
                } catch (const std::out_of_range&) {
                    // 무시, 안전성 보장
                }
            }
        }
        return nItems;
    }

    void print() {
        canvas.clear();
        for (int y = 0; y < yMax; y++) {
            for (int x = 0; x < xMax; x++) {
                try {
                    if (Map(x, y) > 0) canvas.draw(x, y, "◆");
                } catch (const std::out_of_range&) {
                    // 무시
                }
            }
        }
        for (int i = 0; i < nMon; i++) {
            if (pMon[i] != nullptr) {
                pMon[i]->draw(canvas);
            }
        }
        canvas.print("[ Monster World (세상의 모든 귀신) ]");

        std::cerr << "전체 이동 횟수 = " << nMove << std::endl;
        std::cerr << "남은 아이템 수 = " << countItems() << std::endl;
        for (int i = 0; i < nMon; i++) {
            if (pMon[i] != nullptr) {
                pMon[i]->print();
            }
        }
    }

public:
    MonsterWorld(int w, int h) : world(h, w), canvas(w, h), xMax(w), yMax(h), nMon(0), nMove(0) {
        if (w <= 0 || h <= 0) {
            throw std::invalid_argument("Invalid map dimensions");
        }
        if (world.Data() == nullptr) {
            throw std::runtime_error("Failed to initialize world map");
        }
        for (int i = 0; i < MAXMONS; i++) {
            pMon[i] = nullptr; // 배열 초기화
        }
        for (int y = 0; y < yMax; y++) {
            for (int x = 0; x < xMax; x++) {
                try {
                    Map(x, y) = 1; // 맵에 아이템 배치
                } catch (const std::out_of_range&) {
                    std::cerr << "Error: Failed to initialize map at (" << x << "," << y << ")\n";
                }
            }
        }
    }

    ~MonsterWorld() {
        for (int i = 0; i < nMon; i++) {
            delete pMon[i];
            pMon[i] = nullptr;
        }
    }

    void add(Monster* m) {
        if (nMon < MAXMONS && m != nullptr) {
            pMon[nMon++] = m;
        }
    }

    void play(int maxwalk, int wait) {
        if (world.Data() == nullptr) {
            std::cerr << "Error: World map is not initialized\n";
            return;
        }
        print();
        std::cerr << "엔터를 눌러주세요...";
        getchar();
        for (int i = 0; i < maxwalk; i++) {
            for (int k = 0; k < nMon; k++) {
                if (pMon[k] != nullptr) {
                    pMon[k]->move(world.Data(), xMax, yMax);
                }
            }
            nMove++;
            print();
            if (isDone()) break;
            std::this_thread::sleep_for(std::chrono::milliseconds(wait));
        }
    }
};

#endif // MONSTER_WORLD_H_2025