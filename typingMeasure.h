#include "main.h"
#include "helper.h"

#define STARTED 1
#define NOT_STARTED 0

static char scriptArray[LINES_IN_PAGE][MAX_LENGTH] = { 0 };
static char typingArray[LINES_IN_PAGE][MAX_LENGTH] = { 0 };

typedef struct systemVariables {
	int currentLine;
	int typingCount;
	int typingArrayIndex;
	int state;
}SysVal;

static SysVal sysVal = { 0, 0, 0, NOT_STARTED };

void initSystemVariables();

void getScriptLine();
void printCharArray(char*, int, int);
void initCharArray(char*, int, int);
int getTyping(time_t);
void printTyping(char*, int);

int calculateTypingSpeed();
int calculateTypingAccuracy();
void printResult();