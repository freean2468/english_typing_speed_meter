/*
프로그램 : 영타 속도 측정기
개발자 : 송훈일(Neil Son)
개발 기간 : Dec 13, 2020 ~ 
문의 : https://www.youtube.com/channel/UC5yZGtDDMZDe3jmCDUB_rJA
*/
#include "main.h"

time_t timeStarted = time(NULL);

int main(void) {
    printMenu();

    timeStarted = time(NULL);

    /*
        while (1) {
            완료 // script로부터 특정 단어 갯수를 출력 후 (배열에 따로 저장해 두자)
            완료 // 사용자로부터 한 글자씩 입력을 받는다. 각 OS에따라 입력 버퍼를 없애고 표준함수인 getchar를 사용하는 방향으로 가야 한다.
            완료 // 사용자로부터 입력받은 글자들은 배열에 저장하고,
            완료 // 사용자가 backspace로 삭제하면 배열에서도 삭제 (배열2)
            완료 // 그리고 이 모든 과정(입력, 삭제, 오탈자 표시 등) 터미널 화면에 그대로 보여져야 한다.
            완료 // 타자 속도 실시간 중계 -> 계산 방식은? 타수*60/시간(초)
            완료 // 한 페이지를 모두 쳤을 때 로직 처리
            완료 // 오타율 계산
            완료 // 디버깅
        }
    */
    while (script[scriptIndex]) {
        getScriptLine();
        getTyping();
    }

    return 0;
}