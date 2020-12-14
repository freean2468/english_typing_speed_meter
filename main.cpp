/*
프로그램 : 영타 속도 측정기
개발자 : 송훈일(Neil Son)
개발 기간 : Dec 13, 2020 ~ 
문의 : https://www.youtube.com/channel/UC5yZGtDDMZDe3jmCDUB_rJA
*/
#include "main.h"

int main(void) {
    
    printMenu();

    while (scriptArray[scriptIndex]) {
        getScriptLine();
        getTyping();

        break;   
    }

    /*
        while (1) {
            완료 // script로부터 특정 단어 갯수를 출력 후 (배열에 따로 저장해 두자)
            -> // 사용자로부터 한 글자씩 입력을 받는다. 각 OS에따라 입력 버퍼를 없애고 표준함수인 getchar로 입력 받아야 한다.
            사용자로부터 입력받은 글자들은 배열에 저장하고, 사용자가 backspace로 삭제하면 배열에서도 삭제 (배열2)
            한 줄 입력이 끝나면 타자 속도가 출력된다.
        }
    */
    return 0;
}