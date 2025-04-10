#include <iostream>
#include <string>

class MyTimeVisualizer {
public:
    static void drawUML() {
        std::string title = "MyTime";
        std::string privateMembers[] = {
            "- hours : int",
            "- minutes : int",
            "- seconds : int",
            "- normalize() : void"
        };
        std::string publicMembers[] = {
            "+ MyTime()",
            "+ MyTime(h : int, m : int, s : int)",
            "+ convert(duration : double) : void",
            "+ print() : void",
            "+ add(t : MyTime) : MyTime",
            "+ reset() : void"
        };

        // 다이어그램의 최대 너비 계산
        int maxWidth = title.length();
        for (const auto& member : privateMembers) {
            if (member.length() > maxWidth) maxWidth = member.length();
        }
        for (const auto& member : publicMembers) {
            if (member.length() > maxWidth) maxWidth = member.length();
        }
        maxWidth += 4; // 여백 추가

        // 상단 테두리
        std::cout << "+" << std::string(maxWidth - 2, '-') << "+\n";

        // 클래스 이름 출력
        std::cout << "| " << title << std::string(maxWidth - title.length() - 3, ' ') << "|\n";

        // 구분선
        std::cout << "+" << std::string(maxWidth - 2, '-') << "+\n";

        // private 멤버 출력
        for (const auto& member : privateMembers) {
            std::cout << "| " << member << std::string(maxWidth - member.length() - 3, ' ') << "|\n";
        }

        // 구분선
        std::cout << "+" << std::string(maxWidth - 2, '-') << "+\n";

        // public 멤버 출력
        for (const auto& member : publicMembers) {
            std::cout << "| " << member << std::string(maxWidth - member.length() - 3, ' ') << "|\n";
        }

        // 하단 테두리
        std::cout << "+" << std::string(maxWidth - 2, '-') << "+\n";
    }
};

int main() {
    std::cout << "UML Class Diagram for MyTime:\n\n";
    MyTimeVisualizer::drawUML();
    return 0;
}