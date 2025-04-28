#include "MonsterWorld.h"
#include <time.h>
int main()
{
    srand((unsigned int)time(NULL));
    int w = 16, h = 8;

    MonsterWorld game(w, h);
    Monster m("몬스터1", "X", rand() % w, rand() % h);
    game.add(m);
    game.add(Monster("몬스터2", "O", rand() % w, rand() % h));
    game.add(Monster("몬스터3", "P", rand() % w, rand() % h));
    game.add(Monster("몬스터4", "Q", rand() % w, rand() % h));
    game.play(500, 10);
    printf("------게임 종료-------------------\n");
}
