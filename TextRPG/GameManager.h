#pragma once
#include <memory>

#include "Character.h"
#include "Monster.h"

class GameManager
{
public:
    void run();

private:
    void createPlayer();
    void mainMenu();
    std::unique_ptr<Monster> createMonster();
    void startBattle();
    void visitShop();

    /**
     * @brief 콘솔에 지정된 문자로 구분선을 출력합니다.
     * @details UI의 섹션을 시각적으로 나누기 위해 사용됩니다.
     * @param c 구분선을 구성할 문자 (기본값: '-')
     * @param length 구분선의 길이 (기본값: 50)
     */
    void printSeparator(char c = '-', int length = 50) const;
    /**
    * @brief 구분선으로 감싸진 제목 헤더를 깔끔하게 출력합니다.
    * @details 예를 들어, "=== 메인 메뉴 ===" 와 같은 형태의 제목을 만듭니다.
    * 내부적으로 printSeparator() 함수를 호출합니다.
    * @param title 헤더에 표시될 문자열
    */
    void printTitle(const std::string& title) const;
    /**
     * @brief 지정된 범위 내의 유효한 정수를 사용자로부터 안전하게 입력받습니다.
     * @details 사용자가 범위에 맞는 정수를 입력할 때까지 입력을 반복해서 요청합니다.
     * 숫자가 아닌 문자 등 잘못된 입력을 해도 프로그램이 중단되지 않도록
     * 입력 스트림의 에러 상태와 버퍼를 처리하는 예외 처리를 포함합니다.
     * @param min 입력받을 정수의 최솟값
     * @param max 입력받을 정수의 최댓값
     * @return 사용자가 입력한 min과 max 사이의 유효한 정수
     * @note 입력 실패 시 cin의 에러 상태를 clear()하고, 버퍼를 ignore()하여 완전히 초기화합니다.
     */
    int getInputRangeInt(int min, int max) const;
    /**
     * @brief 사용자로부터 Yes/No 형태의 답변을 안전하게 입력받습니다.
     * @details 사용자가 'y' 또는 'n' (대소문자 무관)을 입력할 때까지 반복해서 요청합니다.
     * @return 사용자가 'y' 또는 'Y'를 입력하면 true, 'n' 또는 'N'을 입력하면 false를 반환합니다.
     */
    bool getInputYesNo() const;

    std::unique_ptr<Character> player = nullptr;
    bool isGameOver = false;
};
