#include <stdio.h>
#include <stdlib.h>

enum errors {
    NO_ERR = 0,
    ERR_SAVE_TTY_GETATTR = -2,
    ERR_SAVE_TTY_SETATTR = -3,
    ERR_RESTORE_TTY_SETATTR = -4
};

extern int save_tty_attributes();
extern int restore_tty_attributes();
extern int zeroBufferGetchar();