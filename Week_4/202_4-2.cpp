#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <thread>
#include <chrono>
#include <vector>

#define DIM 4         // 4x4 퍼즐 크기
#define NUM_MVP 5     // 랭킹 최대 저장 개수

// 방향키 정의
enum Direction { Left = 'a', Right = 'd', Up = 'w', Down = 's' };
static int map[DIM][DIM];         // 현재 퍼즐 맵
static int initialMap[DIM][DIM];  // 섞인 초기 퍼즐 맵
static int x, y;                  // 빈 칸 위치
static int nMove;                 // 이동 횟수
static clock_t tStart;            // 게임 시작 시간
static std::vector<char> moves;   // 플레이어의 움직임 기록

struct PlayInfo {
    char name[200];  
    int nMove;        
    double tElapsed;  
};

static PlayInfo MVP[NUM_MVP];  
static int nMVP = NUM_MVP;     

static void init() {
    for (int i = 0; i < DIM * DIM - 1; i++)
        map[i / DIM][i % DIM] = i + 1;
    map[DIM - 1][DIM - 1] = 0;
    x = DIM - 1; y = DIM - 1;

    srand((unsigned)time(NULL));
    tStart = clock();
    nMove = 0;
    moves.clear();  // 움직임 기록 초기화
}

static void copyMap(int dest[DIM][DIM], int src[DIM][DIM]) {
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            dest[i][j] = src[i][j];
        }
    }
}

static void display() {
    system("clear");
    std::cout << "\tFifteen Puzzle\n";
    std::cout << "\t----------------\n";
    for (int r = 0; r < DIM; r++) {
        for (int c = 0; c < DIM; c++) {
            if (map[r][c] > 0)
                std::cout << " " << map[r][c] << " ";
            else
                std::cout << "    ";
        }
        std::cout << "\n";
    }
    std::cout << "\t----------------\n";
    double elapsed = (double)(clock() - tStart) / CLOCKS_PER_SEC;
    std::cout << "\t이동 횟수: " << nMove << "\n";
    std::cout << "\t소요 시간: " << elapsed << "초\n";
}

static bool move(char dir) {
    if (dir == Right && x > 0) {        
        map[y][x] = map[y][x - 1];
        map[y][--x] = 0;
    } else if (dir == Left && x < DIM - 1) {  
        map[y][x] = map[y][x + 1];
        map[y][++x] = 0;
    } else if (dir == Up && y < DIM - 1) {    
        map[y][x] = map[y + 1][x];
        map[++y][x] = 0;
    } else if (dir == Down && y > 0) {  
        map[y][x] = map[y - 1][x];
        map[--y][x] = 0;
    } else {
        return false;
    }
    nMove++;
    moves.push_back(dir);  // 움직임 기록
    return true;
}

static void shuffle(int nShuffle) {
    char keys[] = { Left, Right, Up, Down };
    for (int i = 0; i < nShuffle; i++) {
        char key = keys[rand() % 4];
        if (!move(key)) { i--; continue; }
    }
    copyMap(initialMap, map);  // 섞인 상태 저장
}

static bool isDone() {
    for (int r = 0; r < DIM; r++) {
        for (int c = 0; c < DIM; c++) {
            if (map[r][c] != r * DIM + c + 1)
                return (r == DIM - 1 && c == DIM - 1);
        }
    }
    return true;
}

static char getDirKey() {
    char ch;
    std::cin >> ch;  // 방향키 입력 (WASD)
    return ch;
}

void replay() {
    system("clear");
    std::cout << "\n\t리플레이 시작!\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));

    copyMap(map, initialMap);  // 초기 맵 복사
    display();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    for (char dir : moves) {
        move(dir);
        display();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    std::cout << "\n\t리플레이 완료!\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

int playFifteenPuzzle() {
    init();
    display();
    std::cout << "\n 아무 키나 눌러 시작하세요...";
    getchar();
    shuffle(100);
    display();
    std::cout << "\n 게임이 시작됩니다...";
    getchar();

    nMove = 0;
    tStart = clock();
    while (!isDone()) {
        move(getDirKey());
        display();
    }

    double tElapsed = (double)(clock() - tStart) / CLOCKS_PER_SEC;
    replay();  // 게임 종료 후 리플레이 실행
    return 0;
}

int main() {
    playFifteenPuzzle();
    return 0;
}