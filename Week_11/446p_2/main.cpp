#include "MonsterWorld.h"
#include "VariousMonsters.h"
#include <ctime>
#include <iostream>

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    int w = 16, h = 8;
    MonsterWorld game(w, h);

    game.add(new Zombie("허접한좀비", "★", rand() % w, rand() % h));
    game.add(new Vampire("뱀파이어짱", "♠", rand() % w, rand() % h));
    game.add(new Smombi("스몸비", "☎", rand() % w, rand() % h));
    game.add(new Siangshi("샹시", "♢", rand() % w, rand() % h, true));
    game.add(new Gumiho("구미호", "♡", rand() % w, rand() % h));
    game.play(500, 100); // 500번 이동, 100ms 대기 (테스트 용이성)
    std::cout << "------게임 종료-------------------\n";

    return 0;
}