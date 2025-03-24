#include "p147_6.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// 구구단 문제를 출제하는 함수
void PlayGuguOnce() {
    for (int i = 0; i < 10; ++i) {  // 10개의 문제를 출제
        int num1 = rand() % 9 + 1;  // 1부터 9까지의 랜덤 숫자 생성
        int num2 = rand() % 9 + 1;  // 1부터 9까지의 랜덤 숫자 생성
        int answer;

        cout << num1 << " x " << num2 << " = ? ";  // 문제 출력
        cin >> answer;  // 사용자로부터 답 입력 받기
        if (answer == num1 * num2) {  // 정답 확인
            cout << "Correct!" << endl;  // 정답일 경우
        } else {
            cout << "Wrong. The correct answer is " << num1 * num2 << endl;  // 오답일 경우 정답 출력
        }
    }
}

// 두 자리 수 곱셈 문제를 출제하는 함수
void PlayMultiplication() {
    for (int i = 0; i < 10; ++i) {  // 10개의 문제를 출제
        int num1 = rand() % 90 + 10;  // 10부터 99까지의 랜덤 두 자리 수 생성
        int num2 = rand() % 90 + 10;  // 10부터 99까지의 랜덤 두 자리 수 생성
        int answer;

        cout << num1 << " x " << num2 << " = ? ";  // 문제 출력
        cin >> answer;  // 사용자로부터 답 입력 받기

        if (answer == num1 * num2) {  // 정답 확인
            cout << "Correct!" << endl;  // 정답일 경우
        } else {
            cout << "Wrong. The correct answer is " << num1 * num2 << endl;  // 오답일 경우 정답 출력
        }
    }
}

// 덧셈 문제를 자릿수에 맞춰 출제하는 함수
void PlayAddition(int digits) {
    for (int i = 0; i < 10; ++i) {  // 10개의 문제를 출제
        int num1, num2;
        
        // 자릿수에 맞는 랜덤 덧셈 문제 생성
        if (digits == 3) {
            num1 = rand() % 900 + 100;  // 100부터 999까지의 랜덤 3자리 수 생성
            num2 = rand() % 900 + 100;  // 100부터 999까지의 랜덤 3자리 수 생성
        } else if (digits == 4) {
            num1 = rand() % 9000 + 1000;  
            num2 = rand() % 9000 + 1000;  
        } else if (digits == 5) {
            num1 = rand() % 90000 + 10000;  
            num2 = rand() % 90000 + 10000;  
        } else if (digits == 6) {
            num1 = rand() % 900000 + 100000;  
            num2 = rand() % 900000 + 100000;  
        } else if (digits == 7) {
            num1 = rand() % 9000000 + 1000000;  
            num2 = rand() % 9000000 + 1000000;  
        } else if (digits == 8) {
            num1 = rand() % 90000000 + 10000000;  
            num2 = rand() % 90000000 + 10000000;  
        } else if (digits == 9) {
            num1 = rand() % 900000000 + 100000000;  
            num2 = rand() % 900000000 + 100000000;  
        }
        
        int answer;
        cout << num1 << " + " << num2 << " = ? ";  // 문제 출력
        cin >> answer;  // 사용자로부터 답 입력 받기

        if (answer == num1 + num2) {  // 정답 확인
            cout << "Correct!" << endl;  // 정답일 경우
        } else {
            cout << "Wrong. The correct answer is " << num1 + num2 << endl;  // 오답일 경우 정답 출력
        }
    }
}

int main() {
    srand(time(0));  // 랜덤 시드를 시간으로 초기화하여 매번 다른 랜덤값을 생성

    int choice;
    cout << "Choose a game:\n";  // 게임 선택 안내 메시지 출력
    cout << "1: Speed GuguDan (Multiplication)\n";  // 게임 1
    cout << "2: Two-Digit Multiplication\n";  // 게임 2
    cout << "3: Three-Digit Addition\n";  // 게임 3
    cout << "4: Four-Digit Addition\n";  
    cout << "5: Five-Digit Addition\n";  
    cout << "6: Six-Digit Addition\n";  
    cout << "7: Seven-Digit Addition\n";  
    cout << "8: Eight-Digit Addition\n";  
    cout << "9: Nine-Digit Addition\n";  
    cout << "Enter the number of your choice: ";  // 사용자에게 선택을 입력하라는 메시지 출력
    cin >> choice;  // 사용자로부터 게임 번호 선택 받기

    // 게임 선택에 따른 함수 실행
    switch (choice) {
        case 1:
            PlayGuguOnce();  
            break;
        case 2:
            PlayMultiplication();  
            break;
        case 3:
            PlayAddition(3);  
            break;
        case 4:
            PlayAddition(4);  
            break;
        case 5:
            PlayAddition(5);  
            break;
        case 6:
            PlayAddition(6);  
            break;
        case 7:
            PlayAddition(7); 
            break;
        case 8:
            PlayAddition(8);  
            break;
        case 9:
            PlayAddition(9);  
            break;
        default:
            cout << "Invalid choice!" << endl;  // 잘못된 선택 입력 시 메시지 출력
            break;
    }

    return 0;  // 프로그램 종료
}