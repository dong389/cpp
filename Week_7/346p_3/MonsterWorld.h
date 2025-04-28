#pragma once
#include "Canvas.h"
#include "Monster.h"
#include <unistd.h>  // 리눅스에서 Sleep을 위해 usleep 사용
#define DIM  40
#define MAXMONS 5

class MonsterWorld {
    int map[DIM][DIM];
    int xMax, yMax, nMon, nMove;
    Monster mon[MAXMONS];  // 몬스터들을 저장하는 배열
    Canvas canvas;

    int& Map(int x, int y) { return map[y][x]; }
    bool isDone() { return countItems() == 0; }
    int countItems() {
        int nItems = 0;
        for (int y = 0; y < yMax; y++)
            for (int x = 0; x < xMax; x++)
                if (Map(x, y) > 0) nItems++;
        return nItems;
    }
    void print() {
        canvas.clear();
        for (int y = 0; y < yMax; y++)
            for (int x = 0; x < xMax; x++)
                if (Map(x, y) > 0) canvas.draw(x, y, "¡á");
        for (int i = 0; i < nMon; i++)
            mon[i].draw(canvas);
        canvas.print("[ Monster World (몬스터 월드) ]");

        cerr << " 이동 횟수 = " << nMove << endl;
        cerr << " 남은 아이템 = " << countItems() << endl;
        for (int i = 0; i < nMon; i++)
            mon[i].print();
    }
public:
    MonsterWorld(int w, int h) : canvas(w, h), xMax(w), yMax(h) {
        nMon = 0;
        nMove = 0;
        for (int y = 0; y < yMax; y++)
            for (int x = 0; x < xMax; x++) Map(x, y) = 1;
    }
    ~MonsterWorld() { }
    
    void add(Monster m) {  // 참조로 받지 않고 객체를 복사하여 넘김
        if (nMon < MAXMONS) mon[nMon++] = m;
    }
    
    void play(int maxwalk, int wait) {
        print();
        cerr << " 게임 시작 중...";
        getchar();
        for (int i = 0; i < maxwalk; i++) {
            for (int k = 0; k < nMon; k++)
                mon[k].move(map, xMax, yMax);
            nMove++;
            print();
            if (isDone()) break;
            usleep(wait * 1000);  // usleep은 마이크로초 단위로 시간을 지연시킴
        }
    }
};
