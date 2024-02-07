/*
** EPITECH PROJECT, 2023
** colision
** File description:
** colision
*/

#include "../include/my_radar.h"

sfVector2f *set_rotation(sfVector2f *cornersrect, float get_angle,
    sfVector2f pos)
{
    float angle = get_angle * (PI / 180.0f);
    float x1;
    float y1;

    for (int i = 0; i < 4; ++i) {
        x1 = cos(angle) * (cornersrect[i].x - pos.x) - sin(angle) *
        (cornersrect[i].y - pos.y) + pos.x;
        y1 = sin(angle) * (cornersrect[i].x - pos.x) + cos(angle) *
        (cornersrect[i].y - pos.y) + pos.y;
        cornersrect[i] = (sfVector2f){x1, y1};
    }
    return cornersrect;
}

int var_orientation(sfVector2f start_seg, sfVector2f end_seg, sfVector2f
    point)
{
    int val = (end_seg.y - start_seg.y) * (point.x - end_seg.x) - (end_seg.x
    - start_seg.x) * (point.y - end_seg.y);

    if (val == 0)
        return 0;
    if (val > 0)
        return 1;
    return 2;
}

static int segments_intersection(sfVector2f start_seg1, sfVector2f end_seg1,
    sfVector2f start_seg2, sfVector2f end_seg2)
{
    int hor1 = var_orientation(start_seg1, end_seg1, start_seg2);
    int hor2 = var_orientation(start_seg1, end_seg1, end_seg2);
    int hor3 = var_orientation(start_seg2, end_seg2, start_seg1);
    int hor4 = var_orientation(start_seg2, end_seg2, end_seg1);

    if (hor1 != hor2 && hor3 != hor4)
        return 1;
    return 0;
}

static int check_corner(sfVector2f *cornersrect1, sfVector2f *cornersrect2,
    int i)
{
    for (int j = 0; j < 4; ++j) {
        if (segments_intersection(cornersrect1[i], cornersrect1[(i + 1) %
        4], cornersrect2[j], cornersrect2[(j + 1) % 4]))
            return 1;
    }
    return 0;
}

int colision_plane(sfRectangleShape *rect1, sfRectangleShape *rect2)
{
    sfVector2f pos1 = sfRectangleShape_getPosition(rect1);
    sfVector2f pos2 = sfRectangleShape_getPosition(rect2);
    sfVector2f size = (sfVector2f){20.0f, 20.0f};
    sfVector2f cornersrect1[4] = {{pos1.x, pos1.y}, {pos1.x + size.x, pos1.
    y}, {pos1.x + size.x, pos1.y + size.y}, {pos1.x, pos1.y + size.y}};
    sfVector2f cornersrect2[4] = {{pos2.x, pos2.y}, {pos2.x + size.x, pos2.y},
    {pos2.x + size.x, pos2.y + size.y}, {pos2.x, pos2.y + size.y}};

    set_rotation(cornersrect1, sfRectangleShape_getRotation(rect1), pos1);
    set_rotation(cornersrect2, sfRectangleShape_getRotation(rect2), pos2);
    for (int i = 0; i < 4; ++i) {
        if (check_corner(cornersrect1, cornersrect2, i) == 1)
            return 1;
    }
    return 0;
}

static void set_actif(struct game *game, int i, int j)
{
    if (game->plane[j].actif && game->plane[i].actif && (game->plane[j].
    tower_check == 0 || game->plane[i].tower_check == 0)) {
        if (colision_plane(game->plane[j].hitbox.rect, game->plane[i].
        hitbox.rect) == 1) {
            game->plane[j].actif = 0;
            game->plane[i].actif = 0;
            game->plane[i].delay = 0;
            game->plane[j].delay = 0;
        }
    }
}

void check_colision_plane(struct game *game)
{
    for (int j = 0; j < game->nbr_plane; j++) {
        for (int i = j + 1; i < game->nbr_plane; i++) {
            set_actif(game, i, j);
        }
    }
}
