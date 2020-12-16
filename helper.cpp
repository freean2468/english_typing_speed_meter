// Configure TeleTYpe STanDard INput attributes
// to have zero buffer
// so that it enables us to save input data from an user into an array without echoing.
// 플랫폼(Windows, or xnix)에 따라 이를 설정하는 방법이 달리지기 때문에 이에 대한 처리를 해줘야 함.
// Mac OS에서는 기대한 대로 동작 확인

/*
    사용 예제

	int c = zeroBufferGetchar();
	printf("you entered %c\n",c);

*/
#include "helper.h"

// 각 OS 호환을 위한 전처리
#ifdef _WIN32
#include <windows.h>
static DWORD stdin_mode;
#elif __APPLE__
#include <termios.h>
#include <unistd.h>
struct termios tty_attr;
static tcflag_t c_lflag = tty_attr.c_lflag;
#endif

// 각 OS에 따른 터미널 조작
int save_tty_attributes() {
#ifdef _WIN32
	HANDLE hstdin = GetStdHandle(STD_INPUT_HANDLE);

	if (!GetConsoleMode(hstdin, &stdin_mode))
		return ERR_SAVE_TTY_GETATTR;

	if (hstdin == INVALID_HANDLE_VALUE || !(SetConsoleMode(hstdin, 0)))
		return ERR_SAVE_TTY_GETATTR; /* Failed to disable buffering */
#elif __APPLE__
	struct termios tty_attr;

	if (tcgetattr(STDIN_FILENO, &tty_attr) < 0)
		return ERR_SAVE_TTY_GETATTR;

	tty_attr.c_lflag &= ~ICANON;
	tty_attr.c_lflag &= ~ECHO;

	if (tcsetattr(STDIN_FILENO, 0, &tty_attr) < 0)
		return ERR_SAVE_TTY_SETATTR;
#endif 

    return NO_ERR;
}

// 각 OS에 따른 터미널 기본값으로 다시 설정
int restore_tty_attributes(){
#ifdef _WIN32
	HANDLE hstdin = GetStdHandle(STD_INPUT_HANDLE);

	if (!SetConsoleMode(hstdin, stdin_mode))
		return ERR_RESTORE_TTY_SETATTR;
#elif __APPLE__
    struct termios tty_attr;
    if (tcgetattr(STDIN_FILENO, &tty_attr) < 0)
		return ERR_SAVE_TTY_GETATTR;
        
    tty_attr.c_lflag |= ICANON;
	tty_attr.c_lflag |= ECHO;

	if (tcsetattr(STDIN_FILENO, 0, &tty_attr) < 0)
		return ERR_RESTORE_TTY_SETATTR;
#endif 
    return NO_ERR;
}

// 터미널에서 입력 버퍼를 없애고 입력을 screen에 표시 없이 바로 프로그램 배열에 저장해 사용
int zeroBufferGetchar(){
	int c = 0;
    int res = 0;
	if ((res = save_tty_attributes()) < 0) {
		printf("error : %d", ERR_SAVE_TTY_GETATTR);
        return res;
    }
	c = getchar();
	if ((res = restore_tty_attributes()) < 0) {
		printf("error : %d", ERR_SAVE_TTY_GETATTR);
        return res;
    }
	return c;
}

//
// ANSI escape codes
//
void saveCursorPos() {
	printf("\033[s");
}

void rollBackCursorPos() {
	printf("\033[u");
}

void setRed() {
	printf("\033[1;31m");
}

void reset () {
  	printf("\033[0m");
}

void moveCursorLeftOneBlock(void) {
	printf("\033[1D");
}

void clearScreen() {
	system("cls");
}