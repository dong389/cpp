#include "p248_4-3.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

// 인라인 함수 정의
inline int& mask(int x, int y) { return MineMapMask[y][x]; }
inline int& label(int x, int y) { return MineMapLabel[y][x]; }
inline bool isValid(int x, int y, int nx, int ny) { return (x >= 0 && x < nx && y >= 0 && y < ny); }
inline bool isBomb(int x, int y, int nx, int ny) { return isValid(x, y, nx, ny) && label(x, y) == static_cast<int>(LabelType::Bomb); }
inline bool isEmpty(int x, int y, int nx, int ny) { return isValid(x, y, nx, ny) && label(x, y) == static_cast<int>(LabelType::Empty); }

// 함수 구현
void dig(int x, int y, int nx, int ny) {
    if (isValid(x, y, nx, ny) && mask(x, y) != static_cast<int>(MaskType::Open)) {
        mask(x, y) = static_cast<int>(MaskType::Open);
        if (label(x, y) == 0) {
            dig(x - 1, y - 1, nx, ny);
            dig(x - 1, y, nx, ny);
            dig(x - 1, y + 1, nx, ny);
            dig(x, y - 1, nx, ny);
            dig(x, y + 1, nx, ny);
            dig(x + 1, y - 1, nx, ny);
            dig(x + 1, y, nx, ny);
            dig(x + 1, y + 1, nx, ny);
        }
    }
}

void mark(int x, int y, int nx, int ny) {
    if (isValid(x, y, nx, ny) && mask(x, y) == static_cast<int>(MaskType::Hide))
        mask(x, y) = static_cast<int>(MaskType::Flag);
}

int getBombCount(int nx, int ny) {
    int count = 0;
    for (int y = 0; y < ny; y++)
        for (int x = 0; x < nx; x++)
            if (mask(x, y) == static_cast<int>(MaskType::Flag)) count++;
    return count;
}

void print(int nx, int ny, int nBomb) {
    system("cls"); // Windows 전용
    std::cout << "   발견: " << getBombCount(nx, ny) << "   전체: " << nBomb << "\n";
    // 가로축(열) 번호 출력
    std::cout << "    "; // 왼쪽 여백
    for (int i = 0; i < nx; i++) {
        std::cout << (i + 1) % 10; // 열 번호 (1부터 시작, 10으로 나눈 나머지로 단일 숫자 표시)
    }
    std::cout << "\n";
    // 맵 출력 (세로축에 행 번호 추가)
    for (int y = 0; y < ny; y++) {
        std::cout << " " << (y + 1); // 행 번호 (1부터 시작)
        if (y + 1 < 10) std::cout << " "; // 한 자리 숫자일 경우 공백 추가로 정렬
        for (int x = 0; x < nx; x++) {
            if (mask(x, y) == static_cast<int>(MaskType::Hide)) std::cout << "■";
            else if (mask(x, y) == static_cast<int>(MaskType::Flag)) std::cout << "▲";
            else {
                if (isBomb(x, y, nx, ny)) std::cout << "★";
                else if (isEmpty(x, y, nx, ny)) std::cout << "  ";
                else std::cout << label(x, y);
            }
        }
        std::cout << "\n";
    }
}

int countNbrBombs(int x, int y, int nx, int ny) {
    int count = 0;
    for (int yy = y - 1; yy <= y + 1; yy++)
        for (int xx = x - 1; xx <= x + 1; xx++)
            if (isValid(xx, yy, nx, ny) && label(xx, yy) == static_cast<int>(LabelType::Bomb))
                count++;
    return count;
}

void init(int total, int nx, int ny) {
    std::srand(static_cast<unsigned>(std::time(nullptr))); // 난수 생성 초기화
    // 맵을 모두 빈칸으로 초기화
    for (int y = 0; y < ny; y++)
        for (int x = 0; x < nx; x++) {
            mask(x, y) = static_cast<int>(MaskType::Hide);
            label(x, y) = static_cast<int>(LabelType::Empty);
        }
    // 사용자가 입력한 개수만큼 지뢰를 무작위로 매설
    int nBomb = total;
    for (int i = 0; i < nBomb; i++) {
        int x, y;
        do {
            x = std::rand() % nx; // 가로 범위 내 무작위 위치
            y = std::rand() % ny; // 세로 범위 내 무작위 위치
        } while (label(x, y) != static_cast<int>(LabelType::Empty)); // 빈칸일 때까지 반복
        label(x, y) = static_cast<int>(LabelType::Bomb); // 지뢰 배치
    }
    // 주변 지뢰 개수 계산
    for (int y = 0; y < ny; y++)
        for (int x = 0; x < nx; x++)
            if (label(x, y) == static_cast<int>(LabelType::Empty))
                label(x, y) = countNbrBombs(x, y, nx, ny);
}

bool getPos(int& x, int& y, int nx, int ny) {
    std::cout << "\n지뢰(P)행 예: P13 (지뢰 표시 후 1행 3열), 13 (파내기)\n      입력 --> ";
    std::string input;
    std::cin >> input;
    bool isBomb = (input[0] == 'P' || input[0] == 'p');
    int pos = isBomb ? 1 : 0;
    // 행과 열 번호를 숫자로 파싱
    if (input.length() < pos + 2) return false; // 입력이 너무 짧으면 실패
    std::string rowStr, colStr;
    rowStr = input.substr(pos, 2); // 최대 두 자리 숫자
    colStr = input.substr(pos + 2); // 나머지
    y = std::stoi(rowStr) - 1; // 행 번호 (0부터 시작)
    x = std::stoi(colStr) - 1; // 열 번호 (0부터 시작)
    return isBomb;
}

int checkDone(int nx, int ny, int nBomb) {
    int count = 0;
    for (int y = 0; y < ny; y++)
        for (int x = 0; x < nx; x++) {
            if (mask(x, y) != static_cast<int>(MaskType::Open)) count++;
            else if (isBomb(x, y, nx, ny)) return -1;
        }
    return (count == nBomb) ? 1 : 0;
}

void playMineSweeper(int total, int width, int height) {
    int nx = width, ny = height, nBomb = total;
    int x, y, status;
    init(total, nx, ny); // 지뢰 무작위 매설 및 초기화
    do {
        print(nx, ny, nBomb);
        bool isBomb = getPos(x, y, nx, ny);
        if (isBomb) mark(x, y, nx, ny);
        else dig(x, y, nx, ny);
        status = checkDone(nx, ny, nBomb);
    } while (status == 0);
    print(nx, ny, nBomb);
    if (status < 0)
        std::cout << "\n실패: 지뢰 폭발!!!\n\n";
    else
        std::cout << "\n성공: 탐색 성공!!!\n\n";
}

int main() {
    int total, width, height;
    std::cout << " <Mine Sweeper>\n";
    std::cout << " 맵의 가로 크기 (최대 80): ";
    std::cin >> width;
    std::cout << " 맵의 세로 크기 (최대 40): ";
    std::cin >> height;
    if (width <= 0 || width > 80 || height <= 0 || height > 40) {
        std::cout << "잘못된 크기입니다. 가로는 1~80, 세로는 1~40 사이로 입력하세요.\n";
        return 1;
    }
    std::cout << " 매설할 총 지뢰의 개수 입력 (최대 " << width * height << "): ";
    std::cin >> total;
    if (total <= 0 || total > width * height) {
        std::cout << "잘못된 지뢰 개수입니다. 1에서 " << width * height << " 사이로 입력하세요.\n";
        return 1;
    }
    playMineSweeper(total, width, height);
    return 0;
}