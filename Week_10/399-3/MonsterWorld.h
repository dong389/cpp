#pragma once
#include "Canvas.h"
#include "Monster.h"
#include "Matrix.h"
#include <unistd.h> // usleep을 위해 추가 (리눅스 변경)
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
        for (int y = 0; y < yMax; y++)
            for (int x = 0; x < xMax; x++)
                if (Map(x, y) > 0) nItems++;
        return nItems;
    }
    void checkStarvation() { // 에너지가 0인 몬스터 제거 (문제 3)
        for (int i = 0; i < nMon; i++) {
            if (pMon[i] && pMon[i]->getEnergy() <= 0) {
                delete pMon[i];
                pMon[i] = nullptr;
            }
        }
        // 배열을 정리하여 null 항목을 뒤로 이동 (문제 3)
        int newNMon = 0;
        for (int i = 0; i < nMon; i++) {
            if (pMon[i] != nullptr) {
                pMon[newNMon++] = pMon[i];
            }
        }
        nMon = newNMon;
    }
    void print() {
        canvas.clear();
        for (int y = 0; y < yMax; y++)
            for (int x = 0; x < xMax; x++)
                if (Map(x, y) > 0) canvas.draw(x, y, "★");
        for (int i = 0; i < nMon; i++)
            if (pMon[i]) pMon[i]->draw(canvas); // null 체크 추가 (문제 3)
        canvas.print("[ Monster World ]");

        cerr << " 총 이동 횟수 = " << nMove << endl;
        cerr << " 남은 아이템 수 = " << countItems << endl;
        Monster::printCount(); // 몬스터 수 출력 (문제 4, 5)
        for (int i = 0; i < nMon; i++)
            if (pMon[i]) pMon[i]->print(); // null 체크 추가 (문제 3)
    }
public:
    MonsterWorld(int w, int h) : world(h, w), canvas(w, h), xMax(w), yMax(h) {
        nMon = 0;
        nMove = 0;
        for (int y = 0; y < yMax; y++)
            for (int x = 0; x < xMax; x++) Map(x, y) = 1;
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
        cerr << " Enter를 누르세요...";
        getchar();
        for (int i = 0; i < maxwalk; i++) {
            for (int k = 0; k < nMon; k++)
                if (pMon[k]) pMon[k]->move(world.Data(), xMax, yMax); // null 체크 추가 (문제 3)
            nMove++;
            checkStarvation(); // 아사 체크 (문제 3)
            print();
            if (isDone() || nMon == 0) break; // 몬스터 전멸 시 종료 (문제 3)
            usleep(wait * 1000); // 리눅스에서 대기 시간 설정 (리눅스 변경)
        }
    }
};