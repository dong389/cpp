#include <iostream>
#include <cstring>

class Sample {
    static int count; // 문제 1 정적 변수 count
    char *name;
public:
    Sample() { 
        name = nullptr; 
        count++; 
    }
    Sample(const char *name) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        count++;
        // 문제 2 name을 this와 new 키워드를 이용하여 초기화
    }
    Sample(const Sample &other) {
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
        count++;
        // 문제 4
    }
    ~Sample() {
        delete[] name;
        count--;
        // 문제 3 소멸자, char* name을 동적해제
    }
    static void printcount() {
        std::cout << "Current number of Sample objects: " << count << std::endl;
        // 문제 1 출력을 해주는 함수
    }
};

int Sample::count = 0; // 문제 1 정적 변수 초기화

int main() {
    Sample a("sample");
    Sample b(a);
    Sample::printcount(); // 객체 수 출력 (예: 2)
    return 0;
}