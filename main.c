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

static int verify_file(char **av)
{
    int fd;
    char *str = malloc(get_size(av) + 1);

    for (int i = 0; i < get_size(av) + 1; i++)
        str[i] = '\0';
    fd = open(av[1], O_RDONLY);
    if (str == NULL || fd == -1) {
        write(0, "error with script", 17);
        return 84;
    }
    if (read(fd, str, get_size(av) + 1) == -1) {
        write(0, "error with script", 17);
        return 84;
    }
    close(fd);
    free(str);
}

static int readme(void)
{
    write(1, "Air traffic simulation panel\n\n", 30);
    write(1, "USAGE\n ./my_radar [OPTIONS] path_to_script\n", 43);
    write(1, "  path_to_script    The path to the script file.\n\n", 50);
    write(1, "OPTIONS\n -h                print the usage and quit.\n\n", 54);
    write(1, "USER INTERACTIONS\n", 18);
    write(1, " ‘L’ key enable/disable hitboxes and areas.\n", 48);
    write(1, " ‘S’ key enable/disable sprites.\n", 37);
    return 0;
}

void free_array(char **arr)
{
    for (int i = 0; arr[i]; ++i)
        free(arr[i]);
    free(arr);
}

int main(int ac, char **av, char **env)
{
    char **settings;

    if (ac == 2 && av[1][0] == '-' && av[1][1] == 'h')
        return readme();
    if (check_env(env) == 84 || ac != 2 || verify_file(av) == 84)
        return 84;
    settings = open_script(av);
    return my_radar(settings);
}
