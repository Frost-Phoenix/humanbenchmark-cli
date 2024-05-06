#include "cli.h"


void cli_set_buffred_inputs(int enable) {
    static int enabled = 1;
    static struct termios old;
    struct termios new;

    if (enable && !enabled) {
        tcsetattr(STDIN_FILENO, TCSANOW, &old);                         /* restore the former settings */
        printf("\033[?25h\033[m");                                      /* make cursor visible, reset all modes */
        enabled = 1;
    } else if (!enable && enabled) {
        tcgetattr(STDIN_FILENO, &new);                                  /* get the terminal settings for standard input */
        printf("\033[?25l\033[2J");                                     /* make cursor invisible, clear screen */
        old = new;                                                      /* keep old setting to restore them at the end */
        new.c_lflag &= (~ICANON & ~ECHO);                               /* disable canonical mode (buffeRED_CLI i/o) and local echo */
        tcsetattr(STDIN_FILENO, TCSANOW, &new);                         /* set the new settings immediately */
        enabled = 0;
    }
}

int cli_kbhit() {
    struct timeval timeout;
    fd_set rdset;

    FD_ZERO(&rdset);
    FD_SET(STDIN_FILENO, &rdset);
    timeout.tv_sec = 0;
    timeout.tv_usec = 0;

    return select(STDIN_FILENO + 1, &rdset, NULL, NULL, &timeout) > 0;
}
