#pragma once
#include <string>

// 파일 예외 클래스
struct FileException {
    std::string filename; // 파일 이름
    bool bRead;           // 파일 모드 (읽기/쓰기)
    
    FileException(std::string name, bool b) : filename(name), bRead(b) {}
};