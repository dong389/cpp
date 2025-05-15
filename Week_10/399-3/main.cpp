#include "MonsterWorld.h"
#include <ctime>

int main() {
    srand((unsigned int)time(NULL));
    int w = 16, h = 8;
    MonsterWorld game(w, h);

    game.add(new Monster("고블린", "G", rand() % w, rand() % h));
    game.add(new Monster("오우거", "O", rand() % w, rand() % h));
    game.add(new Monster("드래곤", "D", rand() % w, rand() % h));
    game.add(new Monster("유니콘", "U", rand() % w, rand() % h));
    game.play(500, 10);
    printf("------ 게임 종료 ------\n");
    return 0;
}