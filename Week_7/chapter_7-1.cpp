#include <stdio.h>

class Complex {
public:
    double real, imag;

    Complex(double r = 0, double i = 0) : real(r), imag(i) {}

    // 멤버 함수(void, 참조 전달): c = a + b
    void addMemberVoid(const Complex& other, Complex& result) {
        result.real = real + other.real;
        result.imag = imag + other.imag;
    }

    // 멤버 함수(return, 참조 전달): c = a + b
    Complex addMemberReturn(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }

    // 연산자 오버로딩: c = a + b
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }

    void print() const {
        printf("%.0f + %.0fi\n", real, imag);
    }
};

// 일반 함수(void, 참조 전달): c = a + b
void addVoid(const Complex& a, const Complex& b, Complex& result) {
    result.real = a.real + b.real;
    result.imag = a.imag + b.imag;
}

// 일반 함수(return, 값 전달): c = a + b
Complex addReturn(Complex a, Complex b) {
    return Complex(a.real + b.real, a.imag + b.imag);
}

int main() {
    Complex a(1, 2); // a = 1 + 2i
    Complex b(3, 4); // b = 3 + 4i
    Complex c;       // 결과 저장용

    // 1. 일반 함수(void, 참조 전달) 검증
    addVoid(a, b, c);
    printf("일반 함수(void, 참조 전달): ");
    c.print(); // 기대 출력: 4 + 6i

    // 2. 일반 함수(return, 값 전달) 검증
    c = addReturn(a, b);
    printf("일반 함수(return, 값 전달): ");
    c.print(); // 기대 출력: 4 + 6i

    // 3. 멤버 함수(void, 참조 전달) 검증
    a.addMemberVoid(b, c);
    printf("멤버 함수(void, 참조 전달): ");
    c.print(); // 기대 출력: 4 + 6i

    // 4. 멤버 함수(return, 참조 전달) 검증
    c = a.addMemberReturn(b);
    printf("멤버 함수(return, 참조 전달): ");
    c.print(); // 기대 출력: 4 + 6i

    // 5. 연산자 오버로딩 검증
    c = a + b;
    printf("연산자 오버로딩: ");
    c.print(); // 기대 출력: 4 + 6i

    return 0;
}