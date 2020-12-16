#include <stdio.h>
#include <stdlib.h>

// error codes
enum errors {
    NO_ERR = 0,
    ERR_SAVE_TTY_GETATTR = -2,
    ERR_SAVE_TTY_SETATTR = -3,
    ERR_RESTORE_TTY_SETATTR = -4
};

// ���� �Լ����� �ٱ����� �� �� �ֵ��� externó��.
int save_tty_attributes();
int restore_tty_attributes();
extern int zeroBufferGetchar();

extern void saveCursorPos();
extern void rollBackCursorPos();
extern void setRed();
extern void reset ();
extern void moveCursorLeftOneBlock(void);
extern void clearScreen();