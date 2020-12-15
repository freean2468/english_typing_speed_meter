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

#ifdef _WIN32
static DWORD stdin_mode;
#elif __APPLE__
#include <termios.h>
#include <unistd.h>
struct termios tty_attr;
static tcflag_t c_lflag = tty_attr.c_lflag;
#endif

int save_tty_attributes() {
#ifdef _WIN32
	HANDLE hstdin = GetStdHandle(STD_INPUT_HANDLE);

	if (!GetConsoleMode(hstdin, &mode))
		return -1;

	if (hstdin == INVALID_HANDLE_VALUE || !(SetConsoleMode(hstdin, 0)))
		return -1; /* Failed to disable buffering */
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

int restore_tty_attributes(){
#ifdef _WIN32
	if (!SetConsoleMode(hstdin, mode))
		return -1;
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

int zeroBufferGetchar(){
	int c = 0;
    int res = 0;
	if ((res = save_tty_attributes()) < 0) {
        return res;
    }
	c = getchar();
	if ((res = restore_tty_attributes()) < 0) {
        return res;
    }
	return c;
}

// ANSI escape codes
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