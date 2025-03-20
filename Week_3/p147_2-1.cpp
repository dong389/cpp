#include <iostream>

int reverse(int n) {
    int reversed = 0;
    while (n != 0) {
        int digit = n % 10; // 마지막 자리 숫자 추출
        reversed = reversed * 10 + digit; // 뒤집은 숫자 구성
        n /= 10; // 마지막 자리 제거
    }
    return reversed;
}

int main() {
    int number;
    std::cout << "정수를 입력하세요: ";
    std::cin >> number;

    std::cout << "역순 결과: " << reverse(number) << std::endl;

    return 0;
}