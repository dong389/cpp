#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <thread>
#include <chrono>

#define DIM 4         // 4x4 퍼즐 크기
#define NUM_MVP 10    // 상위 랭킹 10개 기록

// 방향키 정의 (WASD 방식)
enum Direction { Left = 'a', Right = 'd', Up = 'w', Down = 's' };

static int map[DIM][DIM];   // 퍼즐 맵 (1~15: 조각, 0: 빈 칸)
static int x, y;            // 빈 칸의 위치 (행, 열)
static int nMove;           // 이동 횟수
static clock_t tStart;      // 게임 시작 시간
static clock_t tPause;      // 게임 중단 시각 (사용 시)

struct PlayInfo {
    char name[200];  
    int nMove;        
    double tElapsed;  
};

static PlayInfo MVP[NUM_MVP];  // 랭킹 배열 (상위 10개)
static int nMVP = NUM_MVP;

// 게임 초기화 함수: 보드를 4x4 퍼즐로 초기화
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

// 아스키 아트 형식의 보드 출력 함수
static void display() {
    system("clear"); // Linux: 화면 지우기
    std::cout << "\tFifteen Puzzle\n";
    std::cout << "\t----------------\n";
    
    // 각 행마다 상단 경계 및 내용 출력
    for (int r = 0; r < DIM; r++) {
        // 상단 경계
        for (int c = 0; c < DIM; c++) {
            std::cout << "+----";
        }
        std::cout << "+" << std::endl;
        // 각 셀 내용 출력 (숫자 대신 'A'~'O'; 빈 칸은 공백)
        for (int c = 0; c < DIM; c++) {
            char ch;
            if (map[r][c] == 0) {
                ch = ' '; // 빈 칸
            } else {
                ch = 'A' + (map[r][c] - 1); // 1->'A', 2->'B', ..., 15->'O'
            }
            std::cout << "| " << ch << "  ";
        }
        std::cout << "|" << std::endl;
    }
    // 마지막 행 하단 경계 출력
    for (int c = 0; c < DIM; c++) {
        std::cout << "+----";
    }
    std::cout << "+" << std::endl;
    
    std::cout << "\t----------------\n";
    double elapsed = (double)(clock() - tStart) / CLOCKS_PER_SEC;
    if (tPause > 0) elapsed = (double)(tPause - tStart) / CLOCKS_PER_SEC;
    std::cout << "\t이동 횟수: " << nMove << "\n";
    std::cout << "\t소요 시간: " << elapsed << "초\n";
}

// 실제 퍼즐 조각 이동 함수
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

// 퍼즐 섞기 함수: 무작위로 nShuffle번 이동
static void shuffle(int nShuffle) {
    char keys[] = { Left, Right, Up, Down };
    for (int i = 0; i < nShuffle; i++) {
        char key = keys[rand() % 4];
        if (move(key)) {
            display();
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        } else {
            i--; // 이동 실패 시 다시 시도
        }
    }
}

// 퍼즐 완료 여부 확인 함수
static bool isDone() {
    for (int r = 0; r < DIM; r++) {
        for (int c = 0; c < DIM; c++) {
            if (map[r][c] != r * DIM + c + 1)
                return (r == DIM - 1 && c == DIM - 1);
        }
    }
    return true;
}

// 사용자로부터 방향 입력 받는 함수 (WASD)
static char getDirKey() {
    char ch;
    std::cin >> ch;
    return ch;
}

// 랭킹 파일("ranking.dat") 이진 모드로 불러오기 함수
void loadRanking(const char* fname) {
    FILE* fp = fopen(fname, "rb");
    if (!fp) {
        // 파일이 없으면 기본값으로 초기화
        for (int i = 0; i < nMVP; i++) {
            strcpy(MVP[i].name, "C++연습");
            MVP[i].nMove = 1000;
            MVP[i].tElapsed = 1000.0;
        }
    } else {
        fread(MVP, sizeof(PlayInfo), nMVP, fp);
        fclose(fp);
    }
}

// 랭킹 파일("ranking.dat") 이진 모드로 저장하기 함수
void storeRanking(const char* fname) {
    FILE* fp = fopen(fname, "wb");
    if (!fp) return;
    fwrite(MVP, sizeof(PlayInfo), nMVP, fp);
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

// 랭킹 추가 함수: 기록이 기존 상위 랭킹보다 좋으면 삽입
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

// 퍼즐 게임 진행 함수
int playFifteenPuzzle() {
    init();
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
    return 0;
}

// 메인 함수
int main() {
    loadRanking("ranking.dat");
    int rank = playFifteenPuzzle();
    printRanking();
    storeRanking("ranking.dat");
    return 0;
}
