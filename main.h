#include <stdio.h>

// platform dependency
#ifdef _WIN32
    #include <conio.h>
#elif __APPLE__
    #include <curses.h>
#endif

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
extern char scriptArray[][MAX_LENGTH];
extern char typingArray[][MAX_LENGTH];

extern void getScriptLine();
extern void getTyping();