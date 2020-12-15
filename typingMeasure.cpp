#include "typingMeasure.h"

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
    saveCursorPos();
}

void initCharArray(char* p, int col, int row) {
    for (int i = 0; i < col; ++i) {
        for (int j = 0; j < row; ++j) {
            *((char *)((char *)(p+i)+j)) = 0;
        }
    }
}

int getTyping() {
    int typingArrayIndex = 0;
    while (1) {
        int c = zeroBufferGetchar();

        if (c < -1) {
            printf("Something Bad happened : %d\n", c);
            return c;
        }
#ifdef _WIN32
        else if (c == 8 && typingArrayIndex > 0) { // backspace 
#else
        else if (c == 127 && typingArrayIndex > 0) { // backspace 
#endif
            *((char*)((char*)(typingArray+currentLine)+--typingArrayIndex)) = '\0';
        }
        else if (c == 13) { // enter
            continue;
        }
        else 
            *((char*)((char*)(typingArray+currentLine)+typingArrayIndex++)) = c;           

        if (*((char*)((char*)(scriptArray+currentLine)+typingArrayIndex)) == '\0') {
            currentLine++;
            printf("\n\n");
            break;
        }
        printTyping((char*)(typingArray+currentLine));
    }

    return 0;
}

void printTyping(char* p) {
    char* pScriptArray = (char*)(scriptArray+currentLine);
    int typingValue = 0;
    int scriptValue = 0;

    rollBackCursorPos();

    // clean stdout screen out
    while (*pScriptArray++) {
        printf(" ");
    }
    
    pScriptArray = (char*)(scriptArray+currentLine);

    rollBackCursorPos();

    while(*p) {
        if (*p != *pScriptArray++)
            setRed();
        printf("%c", *(p++));
        reset();
    }
}