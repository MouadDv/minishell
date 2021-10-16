#include "minishell.h"

int scan(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == 34)
        {
            while (str[i + 1] != '\0' && str[i + 1] != 34)
                i++;
            if (str[i + 1] == 34)
                i += 2;
        }
        if (str[i] == '<' || str[i] == '>')
        {
            if (str[i] == str[i + 1])
                i++;
            while (str[i + 1] != '\0' && str[i + 1] == ' ')
                i++;
            if (str[i + 1] == '>' || str[i + 1] == '<' || str[i + 1] == '|' || str[i + 1] == '\0')
                return (0);
        }
        if (str[i] == '|' && str[i] == '|')
            return (0);
        i++;
    }
    return (1);
}