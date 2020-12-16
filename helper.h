#include <stdio.h>
#include <stdlib.h>

// error codes
enum errors {
    NO_ERR = 0,
    ERR_SAVE_TTY_GETATTR = -2,
    ERR_SAVE_TTY_SETATTR = -3,
    ERR_RESTORE_TTY_SETATTR = -4
};

// 헬퍼 함수들은 바깥에서 쓸 수 있도록 extern처리.
int save_tty_attributes();
int restore_tty_attributes();
extern int zeroBufferGetchar();

extern void saveCursorPos();
extern void rollBackCursorPos();
extern void setRed();
extern void reset ();
extern void moveCursorLeftOneBlock(void);
extern void clearScreen();