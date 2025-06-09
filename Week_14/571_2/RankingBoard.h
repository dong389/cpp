#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <ncurses.h>
#include <cstdlib>
#include "FileException.h"

#define NUM_MVP 5

struct PlayInfo { // 게임 정보 클래스
    std::string name;      // 게이머의 이름
    int nItem;             // 획득한 아이템의 수
    double itemPerMove;    // 이동 거리당 아이템 수
    PlayInfo(std::string na = "익명인류", int ni = 0, double ipm = 0.0)
        : name(na), nItem(ni), itemPerMove(ipm) {}
};

class RankingBoard { // 랭킹 관리 클래스
    PlayInfo MVP[NUM_MVP];
    int nMVP;

public:
    RankingBoard() : nMVP(0) {}

    void load(const std::string& filename) {
        std::ifstream is(filename);
        if (!is) {
            throw FileException(filename, true);
        }
        nMVP = 0;
        while (nMVP < NUM_MVP && is >> MVP[nMVP].nItem >> MVP[nMVP].name >> MVP[nMVP].itemPerMove) {
            nMVP++;
        }
        is.close();
    }

    void store(const std::string& filename) {
        try {
            std::ofstream os(filename);
            if (!os) {
                throw FileException(filename, false);
            }
            for (int i = 0; i < nMVP; i++) {
                os << MVP[i].nItem << " " << MVP[i].name << " "
                   << MVP[i].itemPerMove << "\n";
            }
            os.close();
        } catch (FileException& e) {
            // 문제 1: 관리자 비밀번호 입력
            std::string passwd, correct = "123456";
            clear();
            mvprintw(0, 0, "관리자 비밀번호를 입력하세요: ");
            refresh();
            while (true) {
                int ch = getch();
                mvprintw(1, passwd.length(), "*");
                refresh();
                if (ch == '\n') {
                    mvprintw(2, 0, "\n");
                    refresh();
                    break;
                }
                passwd += ch;
            }
            // 문제 2: 비밀번호가 틀리면 메시지 출력 및 프로그램 종료
            if (passwd != correct) {
                mvprintw(3, 0, "비밀번호가 맞지 않습니다. 랭킹 저장 실패.\n");
                refresh();
                getch();
                return; // endwin()은 main.cpp에서 처리
            }
            // 문제 3: 비밀번호가 맞으면 새 파일 이름 입력받아 저장
            mvprintw(3, 0, "새 랭킹 파일 이름을 입력하세요: ");
            refresh();
            std::string new_filename;
            echo(); // Enable echo for getline
            char input[256];
            getch(); // Clear any remaining newline
            getstr(input);
            new_filename = input;
            noecho(); // Disable echo
            refresh();

            // 새 파일에 저장
            std::ofstream os(new_filename);
            if (!os) {
                mvprintw(4, 0, "파일 열기 실패: %s\n", new_filename.c_str());
                refresh();
                getch();
                return; // endwin()은 main.cpp에서 처리
            }
            for (int i = 0; i < nMVP; i++) {
                os << MVP[i].nItem << " " << MVP[i].name << " "
                   << MVP[i].itemPerMove << "\n";
            }
            os.close();
        }
    }

    void print(const std::string& title = "게임 랭킹") {
        clear();
        mvprintw(0, 0, "%s\n", title.c_str());
        for (int i = 0; i < nMVP; i++) {
            mvprintw(i + 1, 0, "[%d위] %s\t%d %.2f\n",
                     i + 1, MVP[i].name.c_str(), MVP[i].nItem, MVP[i].itemPerMove);
        }
        mvprintw(nMVP + 1, 0, "엔터를 입력하세요.");
        refresh();
        getch();
    }

    int add(int nItem, double ipm) {
        if (nMVP == 0 || nItem <= MVP[nMVP - 1].nItem) {
            return 0;
        }

        int pos = nMVP < NUM_MVP ? nMVP : NUM_MVP - 1;
        if (nMVP < NUM_MVP) {
            nMVP++;
        }
        for (; pos > 0; pos--) {
            if (nItem <= MVP[pos - 1].nItem) break;
            MVP[pos] = MVP[pos - 1];
        }
        MVP[pos].nItem = nItem;
        MVP[pos].itemPerMove = ipm;
        clear();
        mvprintw(0, 0, "[%d위] 이름을 입력하세요: ", pos + 1);
        refresh();
        echo();
        std::string name;
        char input[256];
        getch(); // Clear any remaining newline
        getstr(input);
        name = input;
        MVP[pos].name = name;
        noecho();
        refresh();
        return pos + 1;
    }
};