/*
** EPITECH PROJECT, 2023
** colision tower
** File description:
** colision tower
*/

#include "../include/my_radar.h"

static int colision_tower(sfRectangleShape *plane, sfCircleShape *tower)
{
    float x;
    float y;
    float dist;
    sfVector2f pos1 = sfRectangleShape_getPosition(plane);
    sfVector2f pos2 = sfCircleShape_getPosition(tower);
    float radius = sfCircleShape_getRadius(tower);
    sfVector2f cornersrect[4] = {{pos1.x, pos1.y}, {pos1.x + 20.0f, pos1.y},
    {pos1.x + 20.0f, pos1.y + 20.0f}, {pos1.x, pos1.y + 20.0f}};

    set_rotation(cornersrect, sfRectangleShape_getRotation(plane), pos1);
    for (int i = 0; i < 4; i++) {
        x = cornersrect[i].x - (pos2.x + radius);
        y = cornersrect[i].y - (pos2.y + radius);
        dist = sqrt(x * x + y * y);
        if (dist <= radius) {
            return 1;
        }
    }
    return 0;
}

static void chek_plane_tower(struct game *game, int j, int i)
{
    if (game->plane[i].actif) {
        if (colision_tower(game->plane[i].hitbox.rect, game->tower[j].
        hitbox.circle) == 1) {
            game->plane[i].tower_check = 1;
        }
    }
}

void check_tower_col(struct game *game)
{
    for (int j = 0; j < game->nbr_tower; j++) {
        for (int i = 0; i < game->nbr_plane; i++) {
            chek_plane_tower(game, j, i);
        }
    }
}