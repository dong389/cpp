#include "301p_1-5.h"
#include <iostream>

int main() {
    MyTime t1;
    std::cout << "Initial time: ";
    t1.print();  // 00:00:00

    t1.convert(3723.5);  // 3723.5초 = 1시간 2분 3초
    std::cout << "After convert(3723.5): ";
    t1.print();  // 01:02:03

    MyTime t2(1, 30, 45);  // 1시간 30분 45초
    MyTime t3 = t2.add(MyTime(2, 45, 20));  // 2시간 45분 20초 더하기
    std::cout << "After add: ";
    t3.print();  // 04:16:05

    t3.reset();
    std::cout << "After reset: ";
    t3.print();  // 00:00:00

    return 0;
}