#include <iostream>
#include <string>

// (1) 계좌 관련 오류를 처리하기 위한 사용자 정의 예외 클래스
class AccountException {
private:
    std::string message; // 오류 메시지
    int amount;         // 오류와 관련된 금액
public:
    AccountException(const std::string& msg, int amt) : message(msg), amount(amt) {}
    std::string getMessage() const { return message; } // 오류 메시지 반환
    int getAmount() const { return amount; }           // 금액 반환
};

class CustomerAccount {
private:
    int balance; // 계좌 잔액
public:
    CustomerAccount(int b = 0) : balance(b) {} // 생성자, 초기 잔액 설정
    int getBalance() const { return balance; } // 잔액 조회

    // (2) 예외 처리를 사용한 입금 함수
    int deposit(int amount) {
        if (amount <= 0) {
            throw AccountException("입금 금액은 양수여야 합니다.", amount);
        }
        balance += amount;
        return balance;
    }

    // (2) 예외 처리를 사용한 출금 함수
    int withdraw(int amount) {
        if (amount > balance) {
            throw AccountException("잔액이 부족하여 출금할 수 없습니다.", amount);
        }
        balance -= amount;
        return balance;
    }
};

// (3) 예외 처리와 테스트 코드를 포함한 main 함수
int main() {
    CustomerAccount account(1000); // 초기 잔액 1000으로 계좌 생성

    // 테스트 1: 정상적인 입금
    try {
        std::cout << "500원 입금 시도..." << std::endl;
        int newBalance = account.deposit(500);
        std::cout << "입금 성공. 새 잔액: " << newBalance << "원" << std::endl;
    } catch (const AccountException& e) {
        std::cerr << "오류: " << e.getMessage() << ", 금액: " << e.getAmount() << "원" << std::endl;
    }

    // 테스트 2: 잘못된 입금 (음수 금액)
    try {
        std::cout << "\n-200원 입금 시도..." << std::endl;
        account.deposit(-200);
    } catch (const AccountException& e) {
        std::cerr << "오류: " << e.getMessage() << ", 금액: " << e.getAmount() << "원" << std::endl;
    }

    // 테스트 3: 정상적인 출금
    try {
        std::cout << "\n300원 출금 시도..." << std::endl;
        int newBalance = account.withdraw(300);
        std::cout << "출금 성공. 새 잔액: " << newBalance << "원" << std::endl;
    } catch (const AccountException& e) {
        std::cerr << "오류: " << e.getMessage() << ", 금액: " << e.getAmount() << "원" << std::endl;
    }

    // 테스트 4: 잘못된 출금 (잔액 초과)
    try {
        std::cout << "\n2000원 출금 시도..." << std::endl;
        account.withdraw(2000);
    } catch (const AccountException& e) {
        std::cerr << "오류: " << e.getMessage() << ", 금액: " << e.getAmount() << "원" << std::endl;
    }

    return 0;
}