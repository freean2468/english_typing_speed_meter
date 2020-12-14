#define WORDS_IN_LINE 10
#define LINES_IN_PAGE 4

#define IN  1
#define OUT 0

#define MAX_LENGTH 100 // 좀 더 적절한 수치를 측정해낼 수 없을까?

// script
extern int scriptIndex;
extern char script[];

// menu
extern void printMenu();

// typingMeasure
extern void getScriptLine();
extern int getTyping();