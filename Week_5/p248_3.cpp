#include "p248_3.h"
#include <iostream>

// 1. 반환값 방식
MyTime addTime(MyTime t1, MyTime t2) {
    MyTime result;
    result.setHours(t1.getHours() + t2.getHours());
    result.setMinutes(t1.getMinutes() + t2.getMinutes());
    result.setSeconds(t1.getSeconds() + t2.getSeconds());

    // 정규화
    int totalSeconds = result.getSeconds();
    result.setMinutes(result.getMinutes() + totalSeconds / 60);
    result.setSeconds(totalSeconds % 60);

    int totalMinutes = result.getMinutes();
    result.setHours(result.getHours() + totalMinutes / 60);
    result.setMinutes(totalMinutes % 60);

    return result;
}

// 2. 참조 방식
void addTime(MyTime t1, MyTime t2, MyTime& t3) {
    t3.setHours(t1.getHours() + t2.getHours());
    t3.setMinutes(t1.getMinutes() + t2.getMinutes());
    t3.setSeconds(t1.getSeconds() + t2.getSeconds());

    // 정규화
    int totalSeconds = t3.getSeconds();
    t3.setMinutes(t3.getMinutes() + totalSeconds / 60);
    t3.setSeconds(totalSeconds % 60);

    int totalMinutes = t3.getMinutes();
    t3.setHours(t3.getHours() + totalMinutes / 60);
    t3.setMinutes(totalMinutes % 60);
}

// 3. 포인터 방식
void addTime(MyTime t1, MyTime t2, MyTime* pt) {
    if (pt == nullptr) return;  // 포인터 유효성 검사

    pt->setHours(t1.getHours() + t2.getHours());
    pt->setMinutes(t1.getMinutes() + t2.getMinutes());
    pt->setSeconds(t1.getSeconds() + t2.getSeconds());

    // 정규화
    int totalSeconds = pt->getSeconds();
    pt->setMinutes(pt->getMinutes() + totalSeconds / 60);
    pt->setSeconds(totalSeconds % 60);

    int totalMinutes = pt->getMinutes();
    pt->setHours(pt->getHours() + totalMinutes / 60);
    pt->setMinutes(totalMinutes % 60);
}

// main 함수에서 테스트
int main() {
    // 테스트용 시간 객체 생성
    MyTime t1(1, 30, 45);  // 1시간 30분 45초
    MyTime t2(2, 45, 20);  // 2시간 45분 20초

    // 1. 반환값 방식 테스트
    MyTime result = addTime(t1, t2);
    std::cout << "Return value method: "
              << result.getHours() << "h "
              << result.getMinutes() << "m "
              << result.getSeconds() << "s\n";

    // 2. 참조 방식 테스트
    MyTime t3;
    addTime(t1, t2, t3);
    std::cout << "Reference method: "
              << t3.getHours() << "h "
              << t3.getMinutes() << "m "
              << t3.getSeconds() << "s\n";

    // 3. 포인터 방식 테스트
    MyTime t4;
    addTime(t1, t2, &t4);
    std::cout << "Pointer method: "
              << t4.getHours() << "h "
              << t4.getMinutes() << "m "
              << t4.getSeconds() << "s\n";

    return 0;
}