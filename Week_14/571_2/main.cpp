#include "MonsterWorld.h"
#include "Human.h"
#include "RankingBoard.h"
#include <ncurses.h>
#include <time.h>
#include <iostream>
#include <string>

int main() {
    // Initialize ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    std::srand((unsigned int)std::time(nullptr));
    RankingBoard rank;
    try {
        rank.load("MonsterWorld.rnk");
    } catch (FileException& e) {
        std::string passwd, correct = "123456";
        printw("관리자 비밀번호를 입력하세요: ");
        refresh();
        while (true) {
            int ch = getch();
            printw("*");
            refresh();
            if (ch == '\n') {
                printw("\n");
                refresh();
                break;
            }
            passwd += ch;
        }
        if (passwd != correct) {
            printw("비밀번호가 맞지 않습니다. 게임 종료.\n\n");
            refresh();
            getch();
            endwin();
            return 0;
        }
        // 비밀 번호가 맞으면 기본 랭킹으로 게임을 계속 진행함.
    }
    rank.print("[게임 랭킹: 시작]");

    int w = 16, h = 8;
    MonsterWorld game(w, h);
    game.add(new Zombie("허접한좀비", "×", rand() % w, rand() % h));
    game.add(new Vampire("뱀파이어짱", "⊙", rand() % w, rand() % h));
    game.add(new KGhost("악마다귀신", "♠", rand() % w, rand() % h));
    game.add(new Jiangshi("멍멍이도고", "♣", rand() % w, rand() % h, true));
    game.add(new Jiangshi("멍멍이서로", "♥", rand() % w, rand() % h, false));

    Human* human = new Human("미래의인류", "★", rand() % w, rand() % h);
    game.add(human);
    game.play(500, 10);
    printw("------게임 종료-------------------\n");
    refresh();

    rank.add(human->nItem, human->nItem / human->total);
    rank.print("[게임 랭킹: 종료]");
    rank.store("MonsterWorld.rnk");

    delete human;
    endwin(); // Terminate ncurses
    return 0;
}