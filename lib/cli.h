#if !defined(CLI_H)
#define CLI_H

#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <sys/select.h>


enum cli_color {
    CLI_BLACK,
    CLI_RED,
    CLI_GREEN,
    CLI_YELLOW,
    CLI_BLUE,
    CLI_MAGENTA,
    CLI_CYAN,
    CLI_WHITE,
};


#define cli_clear()             printf("\033[H\033[J")                  /* clear screen and put cursor at (0,0) */
#define cli_reset()             printf("\033[0m")                       /* reset formating */

#define cli_goto(R, C)          printf("\033[%d;%dH", R, C)             /* move cursor to row r and col c */

#define cli_set_fg(color)       printf("\033[3%dm", color)              /* set text color (basic terminal colors) */
#define cli_set_bg(color)       printf("\033[4%dm", color)              /* set backgroung color (basic terminal colors) */
#define cli_set_fg_rgb(R, G, B) printf("\033[38;2;%d;%d;%dm", R, G, B)  /* set text color (rgb) */
#define cli_set_bg_rgb(R, G, B) printf("\033[48;2;%d;%d;%dm", R, G, B)  /* set text color (rgb) */

#define cli_bold()              printf("\033[1m")                       /* next printed text will be bold */
#define cli_dimmed()            printf("\033[2m")                       /* next printed text will be dimmed */
#define cli_italic()            printf("\033[3m")                       /* next printed text will be in italic */
#define cli_underlined()        printf("\033[4m")                       /* next printed text will be underlined */


void cli_set_buffred_inputs(int enable);                                /* enable / disable the bufferring of terminal input */
int cli_kbhit();                                                        /* check if a key has been hit */


#endif /* CLI_H */
