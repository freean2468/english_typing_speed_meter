#include "main.h"
#include "helper.h"

static char scriptArray[LINES_IN_PAGE][MAX_LENGTH] = {0};
static char typingArray[LINES_IN_PAGE][MAX_LENGTH] = {0};
static int currentLine = 0;

void getScriptLine();
void initCharArray(char*, int, int);
void getTyping();

void getScriptLine() {
    int scriptArrayIndex = 0;

    if (!(currentLine % LINES_IN_PAGE)) {
        currentLine = 0;

        int col = sizeof(scriptArray) / sizeof(scriptArray[0]);
        int row = sizeof(scriptArray[0]) / sizeof(scriptArray[0][0]);
        initCharArray(&scriptArray[0][0], col, row);
    }

    for (int i = 0; i < WORDS_IN_LINE; ++i) {
        while (script[scriptIndex] != ' ' && script[scriptIndex] != '\0') {
            *((char*)((char*)(scriptArray+currentLine))+scriptArrayIndex++) 
                = *((char*)script+scriptIndex++);
        }

        if (*(script+scriptIndex++) == '\0') {
            break;
        }

        *((char*)((char*)(scriptArray+currentLine))+scriptArrayIndex++) = ' ';
    }

    *((char*)((char*)(scriptArray+currentLine))+scriptArrayIndex++) = '\0';

    // print ScriptArray
    for (int i = 0; *((char*)((char*)(scriptArray+currentLine))+i); i++)
        printf("%c", *((char*)((char*)(scriptArray+currentLine))+i));

    printf("\n");
}

void initCharArray(char* p, int col, int row) {
    for (int i = 0; i < col; ++i) {
        for (int j = 0; j < row; ++j) {
            *((char *)((char *)(p+i)+j)) = 0;
        }
    }
}

void getTyping() {
    int typingArrayIndex = 0;
    while (1) {
        int c = zeroBufferGetchar();

        if (c < -1) {
            printf("Something Bad happened : %d\n", c);
            return ;
        }
        else if (c == 8) // backspace 
            *((char*)((char*)(typingArray+currentLine)+--typingArrayIndex)) = ' ';
        else 
            *((char*)((char*)(typingArray+currentLine)+typingArrayIndex++)) = c;           

        if (*((char*)((char*)(scriptArray+currentLine)+typingArrayIndex)) == '\0') {
            currentLine++;
            break;
        }
        printf("%c", c);
    }
}