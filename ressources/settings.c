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
