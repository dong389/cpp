#ifndef MYTIME_H
#define MYTIME_H

#include <iostream>

class MyTime {
private:
    int hours;
    int minutes;
    int seconds;

    // 시간 정규화를 위한 헬퍼 함수 (private로 내부에서만 사용)
    void normalize() {
        int totalSeconds = seconds;
        minutes += totalSeconds / 60;
        seconds = totalSeconds % 60;
        if (seconds < 0) {
            seconds += 60;
            minutes--;
        }

        int totalMinutes = minutes;
        hours += totalMinutes / 60;
        minutes = totalMinutes % 60;
        if (minutes < 0) {
            minutes += 60;
            hours--;
        }

        if (hours < 0) hours = 0; // 음수 시간 방지
    }

public:
    // 생성자
    inline MyTime() : hours(0), minutes(0), seconds(0) {}
    inline MyTime(int h, int m, int s) : hours(h), minutes(m), seconds(s) { normalize(); }

    // 초 단위 시간을 변환
    inline void convert(double duration) {
        hours = static_cast<int>(duration / 3600);
        minutes = static_cast<int>((duration - hours * 3600) / 60);
        seconds = static_cast<int>(duration - hours * 3600 - minutes * 60);
        normalize();
    }

    // 시간 출력 (형식: 01:02:34)
    inline void print() {
        std::cout << (hours < 10 ? "0" : "") << hours << ":"
                  << (minutes < 10 ? "0" : "") << minutes << ":"
                  << (seconds < 10 ? "0" : "") << seconds << "\n";
    }

    // 두 시간을 더함
    inline MyTime add(MyTime t) {
        MyTime result(hours + t.hours, minutes + t.minutes, seconds + t.seconds);
        return result;
    }

    // 시간 초기화
    inline void reset() {
        hours = 0;
        minutes = 0;
        seconds = 0;
    }
};

#endif