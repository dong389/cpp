#ifndef MYTIME_H
#define MYTIME_H

class MyTime {
private:
    int hours;
    int minutes;
    int seconds;

    // 시간 정규화를 위한 헬퍼 함수 (private)
    void normalize();

public:
    MyTime();                    // 기본 생성자
    MyTime(int h, int m, int s); // 매개변수 생성자
    void convert(double duration);
    void print();
    MyTime add(MyTime t);
    void reset();
};

#endif