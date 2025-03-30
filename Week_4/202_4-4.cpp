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
static clock_t tPause;      // 게임 중단 시각

struct PlayInfo {
    char name[200];  
    int nMove;        
    double tElapsed;  
};

static PlayInfo MVP[NUM_MVP];  
static int nMVP = NUM_MVP;     

// 게임 초기화 함수
static void init() {
    for (int i = 0; i < DIM * DIM - 1; i++)
        map[i / DIM][i % DIM] = i + 1;
    map[DIM - 1][DIM - 1] = 0;
    x = DIM - 1; y = DIM - 1;

    srand((unsigned)time(NULL));
    tStart = clock();
    tPause = 0;
    nMove = 0;
}

// 게임 화면 출력 함수
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
    if (tPause > 0) elapsed = (double)(tPause - tStart) / CLOCKS_PER_SEC;  // 중지된 시간 고려
    std::cout << "\t이동 횟수: " << nMove << "\n";
    std::cout << "\t소요 시간: " << elapsed << "초\n";
}

// 게임에서 실제로 움직이는 함수
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

// 퍼즐 섞기 함수
static void shuffle(int nShuffle) {
    char keys[] = { Left, Right, Up, Down };  // 가능한 이동 방향
    for (int i = 0; i < nShuffle; i++) {
        char key = keys[rand() % 4];          // 무작위 방향 선택
        if (move(key)) {                      // 움직임 성공 시만 처리
            display();                        // 상태 표시
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        } else {
            i--;  // 움직임 실패 시 루프 반복
        }
    }
}

// 게임 종료 여부 확인 함수
static bool isDone() {
    for (int r = 0; r < DIM; r++) {
        for (int c = 0; c < DIM; c++) {
            if (map[r][c] != r * DIM + c + 1)
                return (r == DIM - 1 && c == DIM - 1);
        }
    }
    return true;
}

// 방향키 입력 받는 함수
static char getDirKey() {
    char ch;
    std::cin >> ch;  // 방향키 입력 (WASD)
    return ch;
}

// 랭킹 파일 로드 함수
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

// 랭킹 파일 저장 함수
void storeRanking(const char* fname) {
    FILE* fp = fopen(fname, "w");
    if (!fp) return;
    for (int i = 0; i < nMVP; i++) {
        fprintf(fp, "%4d %-16s %5.1f\n", MVP[i].nMove, MVP[i].name, MVP[i].tElapsed);
    }
    fclose(fp);
}

// 랭킹 출력 함수
void printRanking() {
    std::cout << "\n\t[랭킹]\n";
    for (int i = 0; i < nMVP; i++) {
        std::cout << "\t[" << i + 1 << "위] " << MVP[i].nMove 
                  << " " << MVP[i].name << " " << MVP[i].tElapsed << "초\n";
    }
}

// 랭킹 추가 함수
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

// 저장된 게임 불러오기 함수
bool loadGame(const char* fname) {
    FILE* fp = fopen(fname, "r");
    if (!fp) return false;
    
    for (int r = 0; r < DIM; r++) {
        for (int c = 0; c < DIM; c++) {
            fscanf(fp, "%d", &map[r][c]);
        }
    }
    fscanf(fp, "%d %d %d", &nMove, &x, &y);
    fscanf(fp, "%ld", &tStart);  // 저장된 게임 시작 시각
    fclose(fp);
    return true;
}

// 게임 상태 저장 함수
void saveGame(const char* fname) {
    FILE* fp = fopen(fname, "w");
    if (!fp) return;
    
    for (int r = 0; r < DIM; r++) {
        for (int c = 0; c < DIM; c++) {
            fprintf(fp, "%d ", map[r][c]);
        }
    }
    fprintf(fp, "%d %d %d\n", nMove, x, y);
    fprintf(fp, "%ld\n", tStart);  // 현재 시작 시각 저장
    fclose(fp);
}

// 퍼즐 게임 진행 함수
int playFifteenPuzzle() {
    init();
    
    char choice;
    std::cout << "이전에 저장된 게임이 있으면 (Y/N): ";
    std::cin >> choice;
    
    if (choice == 'Y' || choice == 'y') {
        if (!loadGame("saved_game.txt")) {
            std::cout << "저장된 게임이 없습니다. 새로운 게임을 시작합니다.\n";
        } else {
            std::cout << "저장된 게임을 불러왔습니다.\n";
        }
    }

    display();
    printRanking();
    std::cout << "\n 아무 키나 눌러 시작하세요...";
    getchar();
    shuffle(100);  // 100번 섞기
    std::cout << "\n 게임이 시작됩니다...";
    getchar();

    nMove = 0;
    tStart = clock();
    while (!isDone()) {
        move(getDirKey());
        display();
    }

    double tElapsed = (double)(clock() - tStart) / CLOCKS_PER_SEC;
    addRanking(nMove, tElapsed);
    
    // 게임 종료 시 상태 저장
    saveGame("saved_game.txt");

    return 0;
}

// 메인 함수
int main() {
    loadRanking("ranking.txt");
    int rank = playFifteenPuzzle();
    printRanking();
    storeRanking("ranking.txt");
    return 0;
}