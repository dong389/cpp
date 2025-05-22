#ifndef CANVAS_H
#define CANVAS_H

#include <iostream>
#include <string>
#define MAXLINES 100

class Canvas {
    std::string line[MAXLINES]; // 화면 출력을 위한 문자열 배열
    int xMax, yMax;            // 캔버스의 크기

public:
    Canvas(int nx = 10, int ny = 10) : xMax(nx), yMax(ny) {
        if (ny > MAXLINES) {
            yMax = MAXLINES; // MAXLINES 초과 시 제한
            std::cout << "Warning: yMax is limited to " << MAXLINES << std::endl;
        }
        for (int y = 0; y < yMax; y++) {
            line[y] = std::string(xMax * 2, ' '); // 각 줄을 공백으로 초기화
        }
    }

    void draw(int x, int y, const std::string& val) {
        if (x >= 0 && y >= 0 && x < xMax && y < yMax) {
            line[y].replace(x * 2, 2, val); // 지정된 위치에 문자열 그리기
        }
    }

    void clear(const std::string& val = ". ") { // 디폴트 매개변수: 공백 2개
        for (int y = 0; y < yMax; y++) {
            for (int x = 0; x < xMax; x++) {
                draw(x, y, val); // 캔버스 전체를 지정된 값으로 채움
            }
        }
    }

    void print(const std::string& title = "<My Canvas>") {
        system("clear"); // 리눅스에서 화면 지우기
        std::cout << title << std::endl;
        for (int y = 0; y < yMax; y++) {
            std::cout << line[y] << std::endl; // 캔버스 출력
        }
        std::cout << std::endl;
    }
};

#endif // CANVAS_H