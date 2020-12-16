#include "typingMeasure.h"

void initSystemVariables() {
    timeStarted = time(NULL);
    sysVal.typingCount = 0;
}

void getScriptLine() {
    int scriptArrayIndex = 0;
    int col = sizeof(scriptArray) / sizeof(scriptArray[0]);
    int row = sizeof(scriptArray[0]) / sizeof(scriptArray[0][0]);

    if (!(sysVal.currentLine % LINES_IN_PAGE)) {
        //printf("col : %d, row : %d\n", col, row);
        initCharArray(&scriptArray[0][0], col, row);
        initCharArray(&typingArray[0][0], col, row);

        if (sysVal.state == STARTED) {
            printResult();
            initSystemVariables();
        }

        clearScreen();

        sysVal.state = STARTED;
        sysVal.currentLine = 0;
    }

    //printf("currentLine : %d\n", currentLine);

    for (int i = 0; i < WORDS_IN_LINE; ++i) {
        while (script[scriptIndex] != ' ' && script[scriptIndex] != '\0') {
            // scriptArray[sysVal.currentLine][scriptArrayIndex++]
            *((char*)((char*)(scriptArray+ sysVal.currentLine))+scriptArrayIndex++)
                = *((char*)script+scriptIndex++);
        }

        if (*(script+scriptIndex++) == '\0') {
            break;
        }

        // scriptArray[sysVal.currentLine][scriptArrayIndex++]
        *((char*)((char*)(scriptArray+ sysVal.currentLine))+scriptArrayIndex++) = ' ';
    }

    // scriptArray[sysVal.currentLine][scriptArrayIndex++]
    *((char*)((char*)(scriptArray+ sysVal.currentLine))+scriptArrayIndex++) = '\0';

    // print ScriptArray
    //printCharArray(&scriptArray[0][0], col, row);

    // scriptArray[sysVal.currentLine][i]
    for (int i = 0; *((char*)((char*)(scriptArray + sysVal.currentLine)) + i); i++) {
        // scriptArray[sysVal.currentLine][i]
        printf("%c", *((char*)((char*)(scriptArray + sysVal.currentLine)) + i));
    }

    printf("\n");
    saveCursorPos();
}

void printCharArray(char* p, int col, int row) {
    //printf("print : ");
    for (int i = 0; i < col; ++i) {
        for (int j = 0; j < row; ++j) {
            printf("%c", *((char*)((char*)(p + i)) + j));
        }
    }
}

void initCharArray(char* p, int col, int row) {
    for (int i = 0; i < col; ++i) {
        for (int j = 0; j < row; ++j) {
            *((char *)((char *)(p+i))+j) = '\0';
        }
    }
}

int getTyping() {
    sysVal.typingArrayIndex = 0;

    // 시작 전 입력, 출력 버퍼를 모두 삭제
    rewind(stdin);
    rewind(stdout);

    while (1) {
        int c = zeroBufferGetchar();

#ifdef _WIN32
        // backspace와 enter가 아니면
        if (c != 8 && c != 13)
#else
        if (c != 127 && c != 13)
#endif
            sysVal.typingCount++;

        if (c < -1) {
            printf("Something Bad happened : %d\n", c);
            return c;
        }
#ifdef _WIN32
        else if (c == 8 && sysVal.typingArrayIndex > 0) { // backspace 
#else
        else if (c == 127 && typingArrayIndex > 0) { // backspace 
#endif
            // typingArray[sysVal.currentLine][--sysVal.typingArrayIndex];
            *((char*)((char*)(typingArray+ sysVal.currentLine)+--sysVal.typingArrayIndex)) = '\0';
        }
        else if (c == 13) { // enter
            continue;
        }
        else {
            // typingArray[sysVal.currentLine][sysVal.typingArrayIndex++];
            *((char*)((char*)(typingArray + sysVal.currentLine) + sysVal.typingArrayIndex++)) = c;
        }

        // typingArray[sysVal.currentLine][sysVal.typingArrayIndex];
        if (*((char*)((char*)(scriptArray+ sysVal.currentLine)+ sysVal.typingArrayIndex)) == '\0') {
            sysVal.currentLine++;
            printf("\n\n\n");
            break;
        }
        printTyping((char*)(typingArray+ sysVal.currentLine), sysVal.typingArrayIndex);
    }

    return 0;
}

void printTyping(char* p, int until) {
    char* pScriptArray = (char*)(scriptArray+ sysVal.currentLine);
    int typingValue = 0;
    int scriptValue = 0;
    int index = 0;

    printf("\n타속 : %3d, 정확도 : %3d", calculateTypingSpeed(), calculateTypingAccuracy());

    rollBackCursorPos();

    // clean stdout screen out
    while (*pScriptArray++) {
        printf(" ");
    }
    
    pScriptArray = (char*)(scriptArray+ sysVal.currentLine);

    rollBackCursorPos();

    while(index++ < until) {
        if (*p != *pScriptArray++) {
            setRed();
        }
        printf("%c", *(p++));
        reset();
    }
}

int calculateTypingAccuracy() {
    int totalCount = 0;
    int differentCount = 0;

    for (int i = 0; i <= sysVal.currentLine; ++i) {
        int until = (i == sysVal.currentLine) ? sysVal.typingArrayIndex : MAX_LENGTH;
        for (int j = 0; j < until; ++j) {
            // *((char*)((char*)(typingArray + i) + j)) == '\0'
            if (!(*((char*)((char*)(typingArray + i) + j))))
                break;
            totalCount++;
            // typingArray[i][j] != scriptArray[i][j]
            if (*((char*)((char*)(typingArray + i) + j)) != *((char*)((char*)(scriptArray + i) + j)))
                differentCount++;
        }
    }
    return (int)(100 * (sysVal.typingCount-differentCount) / (double)sysVal.typingCount);
}

int calculateTypingSpeed() {
    time_t timeFlowing = time(NULL);
    int speed = (int)((double)sysVal.typingCount * 60.0 / (timeFlowing - timeStarted));
    return (speed > 1000 || speed < 0) ? 0 : speed;
}

void printResult() {
    printf("현재 페이지의 최종 타속: %d, 정확도 : %d 입니다\n", calculateTypingSpeed(), calculateTypingAccuracy());
    printf("다음 페이지를 진행하려면 enter를 누르세요.");
    getchar();
}