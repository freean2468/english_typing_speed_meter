#include <time.h>

// 한 줄에 몇 단어?
#define WORDS_IN_LINE 12
// 한 페이지에 몇 줄?
#define LINES_IN_PAGE 4

#define MAX_LENGTH 100 // 좀 더 적절한 수치를 측정해낼 수 없을까?

// 타자 속도 최초 측정 시점
extern time_t timeStarted;

// script
extern int scriptIndex;
extern char script[];

// menu
extern void printMenu();

// typingMeasure
extern void getScriptLine();
extern int getTyping();