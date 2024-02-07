/*
** EPITECH PROJECT, 2023
** my radar main
** File description:
** my radar
*/
#include "include/my_radar.h"

static int my_strcmp_for_radar(char *s1, char *s2)
{
    for (int i = 0; s1[i] != '\0' && s2[i] != '\0'; i++) {
        if (s1[i] != s2[i])
            return 1;
    }
    return 0;
}

static int check_env(char **env)
{
    for (int i = 0; env[i]; i++) {
        if (my_strcmp_for_radar(env[i], "DISPLAY=") == 0)
            return 0;
    }
    return 84;
}

static int get_size(char **av)
{
    struct stat file;
    int size;

    if (stat(av[1], &file) == -1)
        return 84;
    size = file.st_size;
    return size;
}

static char **open_script(char **av)
{
    int fd;
    char *str = malloc(get_size(av) + 1);
    char **settings;

    for (int i = 0; i < get_size(av) + 1; i++)
        str[i] = '\0';
    fd = open(av[1], O_RDONLY);
    read(fd, str, get_size(av) + 1);
    settings = my_str_to_word_array(str);
    close(fd);
    free(str);
    return settings;
}

int main(int ac, char **av, char **env)
{
    char **settings;

    if (check_env(env) == 84)
        return 84;
    settings = open_script(av);
    return my_radar(settings);
}
