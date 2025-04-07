#pragma once
#include <iostream>
#include <string>

enum class LabelType { Empty = 0, Bomb = 9 };
enum class MaskType { Hide = 0, Open, Flag };
static int MineMapMask[40][80];
static int MineMapLabel[40][80];

// 함수 선언
inline int& mask(int x, int y);
inline int& label(int x, int y);
inline bool isValid(int x, int y, int nx, int ny);
inline bool isBomb(int x, int y, int nx, int ny);
inline bool isEmpty(int x, int y, int nx, int ny);

void dig(int x, int y, int nx, int ny);
void mark(int x, int y, int nx, int ny);
int getBombCount(int nx, int ny);
void print(int nx, int ny, int nBomb);
int countNbrBombs(int x, int y, int nx, int ny);
void init(int total, int nx, int ny);
bool getPos(int& x, int& y, int nx, int ny);
int checkDone(int nx, int ny, int nBomb);
void playMineSweeper(int total = 13, int width = 9, int height = 9);