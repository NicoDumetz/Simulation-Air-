/*
** EPITECH PROJECT, 2023
** settings.c
** File description:
** settinfs plane
*/

#include "../include/my_radar.h"

int compt_plane(char **settings)
{
    int compt = 0;

    for (int i = 0; settings[i]; i++) {
        compt += settings[i][0] == 'A' ? 1 : 0;
    }
    return compt;
}

int compt_tower(char **settings)
{
    int compt = 0;

    for (int i = 0; settings[i]; i++)
        compt += settings[i][0] == 'T' ? 1 : 0;
    return compt;
}

static int check_num(char *str)
{
    for (int i = 0; str[i]; i++) {
        if (str[i] >= 48 && str[i] <= 57)
            continue;
        else
            return 1;
    }
    return 0;
}

static int ver_plane(char **settings, int *i)
{
    if (check_num(settings[*i + 1]) == 1 || check_num(settings[*i + 2]) ==
    1 || check_num(settings[*i + 3]) == 1 || check_num(settings[*i + 4]) ==
    1 || check_num(settings[*i + 5]) == 1 || check_num(settings[*i + 6]) == 1)
        return 84;
    *i += 7;
    return 0;
}

static int ver_tower(char **settings, int *i)
{
    if (settings[*i] == NULL || settings[*i + 1] == NULL || settings[*i + 2]
    == NULL || settings[*i + 3] == NULL || check_num(settings[*i + 1]) ==
    1 || check_num(settings[*i + 2]) == 1 || check_num(settings[*i + 3]) == 1)
        return 84;
    *i += 4;
    return 0;
}

static int ver_plane_tower(char **settings, int *i)
{
    if (settings[*i][0] == 'A' && ver_plane(settings, i) == 84)
        return 84;
    if (settings[*i] == NULL)
        return 0;
    if (settings[*i][0] == 'T' && ver_tower(settings, i) == 84)
        return 84;
    return 0;
}

int verify_instr(char **settings)
{
    for (int i = 0; settings[i];) {
        if (settings[i][0] != 'A' && settings[i][0] != 'T') {
            write(0, "error with script", 17);
            return 84;
        }
        if (ver_plane_tower(settings, &i) == 84) {
            write(0, "error with script", 17);
            return 84;
        }
    }
    if (compt_plane(settings) > 10500) {
        write(0, "too many planes", 16);
        return 84;
    }
    return 0;
}
