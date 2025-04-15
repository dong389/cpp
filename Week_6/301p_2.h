#ifndef MYDIC_H
#define MYDIC_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// (1) WordPair 구조체 정의
struct WordPair {
    string eng; // 영어 단어
    string kor; // 한글 설명
};

const int MAXWORDS = 100; // 최대 단어 수

// (2) MyDic 클래스 정의
class MyDic {
    WordPair words[MAXWORDS]; // 단어 배열
    int nWords;               // 현재 등록된 단어 수
public:
    MyDic() : nWords(0) {} // 생성자: nWords 초기화

    // 단어 추가
    inline void add(string eng, string kor) {
        if (nWords < MAXWORDS) {
            words[nWords].eng = eng;
            words[nWords].kor = kor;
            nWords++;
        } else {
            cout << "단어장이 가득 찼습니다!" << endl;
        }
    }

    // 파일에서 단어 읽기
    inline void load(string filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "파일을 열 수 없습니다: " << filename << endl;
            return;
        }
        nWords = 0; // 기존 단어 초기화
        string eng, kor;
        while (file >> eng >> kor && nWords < MAXWORDS) {
            words[nWords].eng = eng;
            words[nWords].kor = kor;
            nWords++;
        }
        file.close();
    }

    // 파일에 단어 저장
    inline void store(string filename) {
        ofstream file(filename);
        if (!file.is_open()) {
            cout << "파일을 열 수 없습니다: " << filename << endl;
            return;
        }
        for (int i = 0; i < nWords; i++) {
            file << words[i].eng << " " << words[i].kor << endl;
        }
        file.close();
    }

    // 단어장 출력
    inline void print() {
        cout << "=== 단어장 ===" << endl;
        cout << "번호\t영어\t한글" << endl;
        cout << "-----------------" << endl;
        for (int i = 0; i < nWords; i++) {
            cout << i + 1 << "\t" << words[i].eng << "\t" << words[i].kor << endl;
        }
        cout << "총 " << nWords << "개의 단어" << endl;
    }

    // id번째 영어 단어 반환
    inline string getEng(int id) {
        if (id >= 0 && id < nWords) {
            return words[id].eng;
        }
        return "유효하지 않은 ID";
    }

    // id번째 한글 설명 반환
    inline string getKor(int id) {
        if (id >= 0 && id < nWords) {
            return words[id].kor;
        }
        return "유효하지 않은 ID";
    }
};

#endif // MYDIC_H