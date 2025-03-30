#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <thread>
#include <chrono>

#define DIM 4         // 4x4 퍼즐 크기
#define NUM_MVP 5     // 랭킹 최대 저장 개수

// 방향키 정의
enum Direction { Left = 'a', Right = 'd', Up = 'w', Down = 's' };
static int map[DIM][DIM];   // 퍼즐 맵
static int x, y;            // 빈 칸 위치
static int nMove;           // 이동 횟수
static clock_t tStart;      // 게임 시작 시간

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
    return true;
}

static void shuffle(int nShuffle) {
    char keys[] = { Left, Right, Up, Down };
    for (int i = 0; i < nShuffle; i++) {
        char key = keys[rand() % 4];
        if (!move(key)) { i--; continue; }
        display();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
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

void loadRanking(const char* fname) {
    FILE* fp = fopen(fname, "r");
    if (!fp) {
        for (int i = 0; i < nMVP; i++) {
            strcpy(MVP[i].name, "C++연습");
            MVP[i].nMove = 1000;
            MVP[i].tElapsed = 1000.0;
        }
    } else {
        for (int i = 0; i < nMVP; i++) {
            fscanf(fp, "%d %s %lf", &MVP[i].nMove, MVP[i].name, &MVP[i].tElapsed);
        }
        fclose(fp);
    }
}

void storeRanking(const char* fname) {
    FILE* fp = fopen(fname, "w");
    if (!fp) return;
    for (int i = 0; i < nMVP; i++) {
        fprintf(fp, "%4d %-16s %5.1f\n", MVP[i].nMove, MVP[i].name, MVP[i].tElapsed);
    }
    fclose(fp);
}

void printRanking() {
    std::cout << "\n\t[랭킹]\n";
    for (int i = 0; i < nMVP; i++) {
        std::cout << "\t[" << i + 1 << "위] " << MVP[i].nMove 
                  << " " << MVP[i].name << " " << MVP[i].tElapsed << "초\n";
    }
}

int addRanking(int nMove, double tElapsed) {
    if (nMove < MVP[nMVP - 1].nMove) {
        int pos = nMVP - 1;
        for (; pos > 0; pos--) {
            if (nMove >= MVP[pos - 1].nMove) break;
            MVP[pos] = MVP[pos - 1];
        }
        MVP[pos].nMove = nMove;
        MVP[pos].tElapsed = tElapsed;
        std::cout << pos + 1 << "위입니다. 이름을 입력하세요: ";
        std::cin >> MVP[pos].name;
        return pos + 1;
    }
    return 0;
}

int playFifteenPuzzle() {
    init();
    display();
    printRanking();
    std::cout << "\n 아무 키나 눌러 시작하세요...";
    getchar();
    shuffle(100);
    std::cout << "\n 게임이 시작됩니다...";
    getchar();

    nMove = 0;
    tStart = clock();
    while (!isDone()) {
        move(getDirKey());
        display();
    }

    double tElapsed = (double)(clock() - tStart) / CLOCKS_PER_SEC;
    return addRanking(nMove, tElapsed);
}

int main() {
    loadRanking("ranking.txt");
    int rank = playFifteenPuzzle();
    printRanking();
    storeRanking("ranking.txt");
    return 0;
}