#include <iostream>
#include <cstdlib>
#include <ctime>

void randommap(int map[5][5]) {
    std::srand(static_cast<unsigned>(std::time(0))); // 랜덤 시드 초기화

    for (int i = 0; i < 5; ++i) {  // 5x5 배열을 0과 1로 임의로 채움
        for (int j = 0; j < 5; ++j) {
            map[i][j] = std::rand() % 2; // 0 또는 1
        }
    }
}

void printMap(int map[5][5]) {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            std::cout << map[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    int map[5][5];

    randommap(map); // 0과 1로 임의로 채움

    std::cout << "Generated 5x5 Map:" << std::endl;     // 배열 출력
    printMap(map);

    return 0;
}