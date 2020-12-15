#include "main.h"
#include "helper.h"

static char scriptArray[LINES_IN_PAGE][MAX_LENGTH] = { 0 };
static char typingArray[LINES_IN_PAGE][MAX_LENGTH] = { 0 };
static int currentLine = 0;

void getScriptLine();
void initCharArray(char*, int, int);
int getTyping();
void printTyping(char*);