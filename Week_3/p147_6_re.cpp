#include "p147_6_re.h"

// 구구단 게임
void playGuguOnce() {
    while (true) {
        int a = rand() % 9 + 1;
        int b = rand() % 9 + 1;
        int answer;

        cout << a << " x " << b << " = ? ";
        cin >> answer;

        if (answer == a * b) {
            cout << "정답!\n";
            break;
        } else {
            cout << "틀렸습니다. 다시 시도하세요.\n";
        }
    }
}

// 두 자리 수 곱셈 게임
void playMultiplication() {
    while (true) {
        int a = rand() % 90 + 10;  // 10~99 사이의 숫자
        int b = rand() % 90 + 10;  // 10~99 사이의 숫자
        int answer;

        cout << a << " x " << b << " = ? ";
        cin >> answer;

        if (answer == a * b) {
            cout << "정답!\n";
            break;
        } else {
            cout << "틀렸습니다. 다시 시도하세요.\n";
        }
    }
}

// 여러 자리 수 덧셈 게임
void playAddition(int digits) {
    while (true) {
        int num1 = rand() % (int)pow(10, digits);  // digits 자리 수로 랜덤 숫자 생성
        int num2 = rand() % (int)pow(10, digits);  // digits 자리 수로 랜덤 숫자 생성
        int answer;

        cout << num1 << " + " << num2 << " = ? ";
        cin >> answer;

        if (answer == num1 + num2) {
            cout << "정답!\n";
            break;
        } else {
            cout << "틀렸습니다. 다시 시도하세요.\n";
        }
    }
}

// 게임 시작 함수
void startGame() {
    srand(time(0));  // 랜덤 시드 설정
    int choice;

    cout << "게임을 선택하세요: \n";
    cout << "1: 구구단 게임\n";
    cout << "2: 두 자리 수 곱셈\n";
    cout << "3~9: 해당 자리 수 덧셈\n";
    cin >> choice;

    if (choice == 1) {
        playGuguOnce();
    } else if (choice == 2) {
        playMultiplication();
    } else if (choice >= 3 && choice <= 9) {
        playAddition(choice);
    } else {
        cout << "잘못된 선택입니다.\n";
    }
}

int main() {
    startGame();  // 게임 시작
    return 0;
}
