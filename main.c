#include "minishell.h"

void    sighandler(int  sig)
{
    if (sig == SIGINT)
    {
        rl_on_new_line();
        write (1, "minishell>> ", 12);
        write (1, rl_line_buffer, strlen(rl_line_buffer));
        write (1, "  \b\b\n", 5);
        rl_replace_line("", 1);
        rl_redisplay();
    }
}

char *get_line()
{
    char    *buf;
    int     s;

    signal(SIGQUIT, SIG_IGN);
    signal(SIGINT, sighandler);
    buf = readline("minishell>> ");
    if (buf == NULL)
    {
        write(1, "exit\n", 5);
        exit(0);
    }
    if (strlen(buf) > 0) {
        add_history(buf);
    }

    write (1, buf, strlen(buf));
    write (1, "\n", 1);
    s = scan(buf);
    if (s == 0)
        write (1, "Minishell: Syntax error\n", 24);
    free(buf);
    return (buf);
}

int main() {
    signal(SIGQUIT, SIG_IGN);
    while (1) {
        signal(SIGINT, sighandler);
        get_line();
    }
    return 0;
}
