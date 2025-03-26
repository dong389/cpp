#ifndef MATH_GAME_H
#define MATH_GAME_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>  // pow 함수 사용을 위한 헤더

using namespace std;

// 함수 프로토타입 선언
void playGuguOnce();  // 구구단 게임
void playMultiplication();  // 두 자리 수 곱셈 게임
void playAddition(int digits);  // 여러 자리 덧셈 게임
void startGame();  // 게임 시작 함수

#endif // MATH_GAME_H