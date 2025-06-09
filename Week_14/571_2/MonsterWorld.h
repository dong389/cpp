#pragma once
#include "Canvas.h"
#include "VariousMonsters.h"
#include "Human.h"
#include "Matrix.h"
#include <chrono>
#include <thread>
#include <iostream>
#include <string>

#define MAXMONS 8

class MonsterWorld {
    Matrix world;
    int xMax, yMax, nMon, nMove;
    Monster* pMon[MAXMONS];
    Canvas canvas;

    int& Map(int x, int y) { return world.elem(x, y); }

    bool isDone() { return countItems() == 0; }

    int countItems() {
        int nItems = 0;
        for (int y = 0; y < yMax; y++)      // 변수명 및 선언 수정
            for (int x = 0; x < xMax; x++)
                if (Map(x, y) > 0) nItems++;
        return nItems;
    }

    void print() {
        canvas.reset();
        for (int y = 0; y < yMax; y++)
            for (int x = 0; x < xMax; x++)
                if (Map(x, y) > 0) canvas.draw(x, y, std::string("■"));
        for (int i = 0; i < nMon; i++)
            pMon[i]->draw(canvas);
        canvas.print("[ Monster World (새로운 경쟁의 시작) ]");

        mvprintw(yMax + 2, 0, "전체 이동 횟수 = %d", nMove);
        mvprintw(yMax + 3, 0, "남은 아이템 수 = %d", countItems());
        for (int i = 0; i < nMon; i++) {
            mvprintw(yMax + 4 + i, 0, "%s%s: %d : %d",
                     pMon[i]->name.c_str(), pMon[i]->icon.c_str(), pMon[i]->nItem, pMon[i]->nSleep);
        }
        refresh();
    }

public:
    MonsterWorld(int w, int h) : world(h, w), canvas(w, h), xMax(w), yMax(h), nMon(0), nMove(0) {
        for (int i = 0; i < MAXMONS; i++)
            pMon[i] = nullptr;
        for (int y = 0; y < yMax; y++)
            for (int x = 0; x < xMax; x++)
                Map(x, y) = 1;
    }

    ~MonsterWorld() {
        for (int i = 0; i < nMon; i++)
            delete pMon[i];
    }

    void add(Monster* m) {
        if (nMon < MAXMONS)
            pMon[nMon++] = m;
    }

    void play(int maxwalk, int wait) {
        print();
        mvprintw(yMax + nMon + 5, 0, "엔터를 눌러주세요...");
        refresh();
        getch();
        for (int i = 0; i < maxwalk; i++) {
            for (int k = 0; k < nMon; k++)
                pMon[k]->move(world.Data(), xMax, yMax);

            nMove++;
            print();
            if (isDone()) break;
            std::this_thread::sleep_for(std::chrono::milliseconds(wait));
        }
    }
};
