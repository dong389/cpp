#include <iostream>
#include <string>
using namespace std;

void printKoreanNumber(int num) {
    string units[] = {"", "만 ", "천 ", "백 ", "십 "};
    string digits[] = {"", "1", "2", "3", "4", "5" "6", "7", "8", "9"}; // '영' 제거

    string result = "";
    int place = 0;

    while (num > 0) {
        int digit = num % 10;

        if (digit != 0 && !(digit == 1 && place > 0)) {
            result = digits[digit] + units[place] + result;
        } else if (digit == 1 && place > 0) {
            result = units[place] + result; 
        }

        num /= 10;
        place++;
    }

    cout << result << endl;
}

int main() {
    int num;

    cout << "10000 미만의 정수를 입력하세요: ";
    cin >> num;

    if (num < 0 || num >= 10000) {
        cout << "잘못된 입력입니다. 0 이상 10000 미만의 정수를 입력해주세요." << endl;
    } else {
        printKoreanNumber(num);
    }

    return 0;
}