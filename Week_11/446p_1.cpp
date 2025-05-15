#include <iostream>

class Point {
protected:
    int x, y;
public:
    Point(int xx, int yy) : x(xx), y(yy) {}
    void draw() {
        std::cout << x << "," << y << "에 점을 그려라.\n";
    }
};

// (1) Point 클래스를 상속받아 Rectangle 클래스 정의, width와 height 멤버 추가
class Rectangle : public Point {
protected:
    int width, height;
public:
    // (2) 생성자에서 Point의 x, y와 Rectangle의 width, height를 멤버 초기화 리스트로 초기화
    Rectangle(int xx, int yy, int w, int h) : Point(xx, yy), width(w), height(h) {}

    // (3) Point의 draw 함수를 재정의하여 사각형 정보 출력
    void draw() {
        std::cout << x << "," << y << "에 가로 " << width << " 세로 " << height << "인 사각형을 그려라.\n";
    }
};

// (4) Point 클래스에서 protected를 private로 변경 시 영향
// 답변: Point 클래스에서 x, y의 protected를 private로 변경하면,
// Rectangle 클래스에서 x, y에 직접 접근할 수 없어 컴파일 오류가 발생합니다.
// 예: Rectangle의 draw 함수에서 std::cout << x << "," << y << ... 는
// "오류: 'x'는 Point의 private 멤버입니다" 같은 오류를 일으킵니다.
// 이유: private는 Point 클래스 내부에서만 접근 가능하고, 파생 클래스(Rectangle)에서는 접근 불가.
// 해결: Point에 getter 함수(예: int getX() const { return x; })를 추가하거나,
// x, y를 protected로 유지해야 함.
// Point 자체의 draw 함수는 x, y에 접근 가능하므로 정상 동작하나,
// Rectangle의 draw는 x, y 접근이 필요하므로 수정이 필요함.

int main() {
    // 테스트 코드
    Point p(1, 2);
    Rectangle r(2, 3, 100, 200);
    
    p.draw(); // Point의 draw 호출
    r.draw(); // Rectangle의 draw 호출
    
    return 0;
}