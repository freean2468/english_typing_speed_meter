// 첫 화면 UI

#include <stdio.h>
#include "helper.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

void printMenu();

void printMenu() {
    printf("영타 속도를 측정하는 프로그램입니다. \n");
    printf("enter를 눌러 속도 측정을 시작합니다.\n\n");
    printf("걸리버 여행기 챕터 1\n\n");
    getchar();
    clearScreen();
}