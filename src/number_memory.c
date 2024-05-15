#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <math.h>
#include <time.h>
#include <sys/ioctl.h>
#include <signal.h>

#include "../include/number_memory.h"
#include "../lib/cli.h"


#define TRUE  1
#define FALSE 0


static void quit() {
    cli_set_buffred_inputs(TRUE);

    exit(EXIT_SUCCESS);
}

static void init() {
    cli_clear();
    cli_set_buffred_inputs(FALSE);

    signal(SIGINT, quit);

    srand(time(NULL));
}

static int get_term_width() {
    struct winsize sz;
    ioctl(0, TIOCGWINSZ, &sz);
    return sz.ws_col;
}

static int get_term_height() {
    struct winsize sz;
    ioctl(0, TIOCGWINSZ, &sz);
    return sz.ws_row;
}

static void get_nb(char* out, size_t n) {
    for (size_t i = 0; i < n; i++) {
        out[i] = (rand() % 10) + 48;
    }
    out[n] = '\0';
}

void number_memory() {
    init();

    int len = 1;    
    int width = get_term_width(), 
        height = get_term_height();

    while (TRUE) {
        int posx = height / 2, 
            posy = width / 2 - len / 2;
        char nb[len + 1];
        get_nb(nb, len);

        cli_clear();
        cli_reset();

        cli_goto(posx, posy);
        printf("%s\n", nb);

        usleep(2 * 1000000 + len * 300000);
        cli_clear();
        cli_set_fg(CLI_GREEN);
        cli_goto(posx, posy);

        for (int i = 0; i < len; i++) {
            int digit = getchar();
            
            if (digit != nb[i]) {
                cli_set_fg(CLI_RED);
                printf("%d\n", digit - 48);

                quit();
            }
            printf("%d", digit - 48);
        }

        puts("");
        sleep(1);

        len++;
    }
}
