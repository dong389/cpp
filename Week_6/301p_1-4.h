#ifndef MYTIME_H
#define MYTIME_H

#include <iostream>
#include <iomanip> // 입출력 조작자 사용을 위해

class MyTime {
private:
    int hours;
    int minutes;
    int seconds;

    // 시간 정규화를 위한 헬퍼 함수 (private)
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
        std::cout << std::setfill('0') << std::setw(2) << hours << ":"
                  << std::setfill('0') << std::setw(2) << minutes << ":"
                  << std::setfill('0') << std::setw(2) << seconds << "\n";
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

    // 사용자로부터 시간 입력 받기
    inline void read() {
        std::cout << "Enter aspett Enter hours (0-23): ";
        std::cin >> hours;
        std::cout << "Enter minutes (0-59): ";
        std::cin >> minutes;
        std::cout << "Enter seconds (0-59): ";
        std::cin >> seconds;
        normalize(); // 입력 후 정규화
    }
};

#endif