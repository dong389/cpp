#pragma once
#include "Monster.h"
#include <ncurses.h>
#include <iostream>
#include <string>

enum Direction { Left = 75, Right = 77, Up = 72, Down = 80 };

class Human : public Monster {
public:
    Human(std::string n = "미래인류", std::string i = "★", int px = 0, int py = 0)
        : Monster(n, i, px, py) {}
    ~Human() { std::cout << " [Human   ]"; }

    int getDirKey() {
        int ch = getch();
        return (ch == 27 && getch() == 91) ? getch() : 0; // Handle ANSI escape for arrow keys
    }

    void move(int** map, int maxx, int maxy) {
        nodelay(stdscr, TRUE); // Non-blocking input
        int ch = getch();
        if (ch != ERR) { // Check if a key was pressed
            ch = getDirKey();
            if (ch == Left) p[0]--;
            else if (ch == Right) p[0]++;
            else if (ch == Up) p[1]--;
            else if (ch == Down) p[1]++;
            else return;

            clip(maxx, maxy);
            eat(map);
        }
        nodelay(stdscr, FALSE); // Restore blocking mode
    }
};