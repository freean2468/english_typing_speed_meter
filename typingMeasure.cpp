#include "typingMeasure.h"

// 타자속도, 정확도 측정 변수 초기화
void initSystemVariables() {
    timeStarted = time(NULL);
    sysVal.typingCount = 0;
}

// script에서 한 줄을 읽어온다.
void getScriptLine() {
    int scriptArrayIndex = 0;
    int col = sizeof(scriptArray) / sizeof(scriptArray[0]);
    int row = sizeof(scriptArray[0]) / sizeof(scriptArray[0][0]);

    // 한 페이지가 끝나면 초기화
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

    // 스크립트로부터 한 줄을 한 글자씩 복사해온다.
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

    // 입력 받아 온 한 줄을 출력
    // scriptArray[sysVal.currentLine][i]
    for (int i = 0; *((char*)((char*)(scriptArray + sysVal.currentLine)) + i); i++) {
        // scriptArray[sysVal.currentLine][i]
        printf("%c", *((char*)((char*)(scriptArray + sysVal.currentLine)) + i));
    }
    printf("\n");

    // 현재 커서 위치에서부터 사용자의 입력이 출력되도록 위치 저장.
    saveCursorPos();
}

// 2차원 배열 출력
void printCharArray(char* p, int col, int row) {
    //printf("print : ");
    for (int i = 0; i < col; ++i) {
        for (int j = 0; j < row; ++j) {
            printf("%c", *((char*)((char*)(p + i)) + j));
        }
    }
}

// 2차원 배열 초기화
void initCharArray(char* p, int col, int row) {
    for (int i = 0; i < col; ++i) {
        for (int j = 0; j < row; ++j) {
            *((char *)((char *)(p+i))+j) = '\0';
        }
    }
}

// 사용자로부터 입력을 받고 속도 및 정확도를 측정
int getTyping() {
    sysVal.typingArrayIndex = 0;

    // 시작 전 입력, 출력 버퍼를 모두 삭제
    rewind(stdin);
    rewind(stdout);

    while (1) {
        // 한 글자씩 받아와서
        int c = zeroBufferGetchar();

#ifdef _WIN32
        // backspace와 enter가 아니면
        if (c != 8 && c != 13)
#else
        if (c != 127 && c != 13)
#endif
            sysVal.typingCount++;

        // 터미널 조작이 불가능한 경우.
        if (c < -1) {
            printf("Something Bad happened : %d\n", c);
            return c;
        }
#ifdef _WIN32
        else if (c == 8 && sysVal.typingArrayIndex > 0) { // backspace 
#else
        else if (c == 127 && typingArrayIndex > 0) { // backspace 
#endif
            // 삭제
            // typingArray[sysVal.currentLine][--sysVal.typingArrayIndex];
            *((char*)((char*)(typingArray+ sysVal.currentLine)+--sysVal.typingArrayIndex)) = '\0';
        }
        else if (c == 13) { // enter 무시
            continue;
        }
        else {
            // 입력
            // typingArray[sysVal.currentLine][sysVal.typingArrayIndex++];
            *((char*)((char*)(typingArray + sysVal.currentLine) + sysVal.typingArrayIndex++)) = c;
        }

        // 한 줄 끝
        // typingArray[sysVal.currentLine][sysVal.typingArrayIndex] == '\0';
        if (!(*((char*)((char*)(scriptArray+ sysVal.currentLine)+ sysVal.typingArrayIndex)))) {
            *((char*)((char*)(typingArray + sysVal.currentLine) + sysVal.typingArrayIndex)) = (*((char*)((char*)(scriptArray + sysVal.currentLine) + sysVal.typingArrayIndex)));
            sysVal.currentLine++;
            printf("\n\n\n");
            break;
        }
        // 입력 값 출력
        printTyping((char*)(typingArray+ sysVal.currentLine), sysVal.typingArrayIndex);
    }

    return 0;
}

// 입력값을 가진 배열을 출력
void printTyping(char* p, int until) {
    char* pScriptArray = (char*)(scriptArray+ sysVal.currentLine);
    int typingValue = 0;
    int scriptValue = 0;
    int index = 0;

    printf("\n타속 : %3d, 정확도 : %3d%%", calculateTypingSpeed(), calculateTypingAccuracy());

    // 커서 위치를 복구
    rollBackCursorPos();

    // clean stdout screen out
    while (*pScriptArray++) {
        printf(" ");
    }
    
    pScriptArray = (char*)(scriptArray+ sysVal.currentLine);

    rollBackCursorPos();

    while(index++ < until) {
        // 오타면
        if (*p != *pScriptArray++) {
            // 빨갛게
            setRed();
        }
        printf("%c", *(p++));
        reset();
    }
}

// 오타율 측정
int calculateTypingAccuracy() {
    int totalCount = 0;
    int differentCount = 0;

    for (int i = 0; i <= sysVal.currentLine; ++i) {
        int until = (i == sysVal.currentLine) ? sysVal.typingArrayIndex : MAX_LENGTH;
        until -= 1;
        for (int j = 0; j < until; ++j) {
            // *((char*)((char*)(scriptArray + i) + j)) == '\0'
            if (!(*((char*)((char*)(scriptArray + i) + j))))
                break;
            totalCount++;
            // typingArray[i][j] != scriptArray[i][j]
            if (*((char*)((char*)(typingArray + i) + j)) != *((char*)((char*)(scriptArray + i) + j)))
                differentCount++;
        }
    }

    int diff = sysVal.typingCount - differentCount;
    
    diff = (diff < 0) ? 0 : diff;

    return (int)(100 * diff / (double)sysVal.typingCount);
}

// 타자 속도 측정
int calculateTypingSpeed() {
    time_t timeFlowing = time(NULL);
    int speed = (int)((double)sysVal.typingCount * 60.0 / (timeFlowing - timeStarted));
    return (speed > 1000 || speed < 0) ? 0 : speed;
}

// 한 페이지 결과 출력
void printResult() {
    printf("현재 페이지의 최종 타속: %d, 정확도 : %d 입니다\n", calculateTypingSpeed(), calculateTypingAccuracy());
    printf("다음 페이지를 진행하려면 enter를 누르세요.");
    getchar();
}