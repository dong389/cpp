#include "301p_2.h"

// (3) main 함수로 기능 테스트
int main() {
    MyDic dic;

    // 단어 추가 테스트
    cout << "1. 단어 추가 테스트" << endl;
    dic.add("apple", "사과");
    dic.add("book", "책");
    dic.add("cat", "고양이");
    dic.print();

    // 파일 저장 테스트
    cout << "\n2. 파일 저장 테스트" << endl;
    dic.store("vocab.txt");
    cout << "단어장을 vocab.txt에 저장했습니다." << endl;

    // 단어장 비우고 파일에서 읽기 테스트
    cout << "\n3. 파일 읽기 테스트" << endl;
    MyDic newDic; // 새 단어장
    newDic.load("vocab.txt");
    newDic.print();

    // getEng, getKor 테스트
    cout << "\n4. getEng, getKor 테스트" << endl;
    cout << "1번째 단어 영어: " << newDic.getEng(0) << endl;
    cout << "1번째 단어 한글: " << newDic.getKor(0) << endl;
    cout << "유효하지 않은 ID(10): " << newDic.getEng(10) << endl;

    return 0;
}