#include "301p_1-5.h"
#include <iostream>
#include <iomanip>

void MyTime::normalize() {
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

    if (hours < 0) hours = 0;
}

MyTime::MyTime() : hours(0), minutes(0), seconds(0) {}

MyTime::MyTime(int h, int m, int s) : hours(h), minutes(m), seconds(s) {
    normalize();
}

void MyTime::convert(double duration) {
    hours = static_cast<int>(duration / 3600);
    minutes = static_cast<int>((duration - hours * 3600) / 60);
    seconds = static_cast<int>(duration - hours * 3600 - minutes * 60);
    normalize();
}

void MyTime::print() {
    std::cout << std::setfill('0') << std::setw(2) << hours << ":"
              << std::setfill('0') << std::setw(2) << minutes << ":"
              << std::setfill('0') << std::setw(2) << seconds << "\n";
}

MyTime MyTime::add(MyTime t) { // 반환형 'MyTime' 추가
    MyTime result(hours + t.hours, minutes + t.minutes, seconds + t.seconds);
    return result;
}

void MyTime::reset() {
    hours = 0;
    minutes = 0;
    seconds = 0;
}