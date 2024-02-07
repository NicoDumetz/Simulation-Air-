/*
** EPITECH PROJECT, 2023
** display all
** File description:
** display
*/

#include "../include/my_radar.h"

static float myabs(float a)
{
    return a < 0 ? -a : a;
}

static int calculate_traj(struct game *game, int i)
{
    sfTime deltaTime = sfClock_getElapsedTime(game->plane[i].clock);
    float seconds = sfTime_asSeconds(deltaTime);
    sfVector2f direction = { game->plane[i].posfin.x - game->plane[i].pos.x,
    game->plane[i].posfin.y - game->plane[i].pos.y};
    float distance = game->plane[i].speed * seconds;
    float longu = sqrt(direction.x * direction.x + direction.y * direction.y);

    if (longu != 0)
        direction = (sfVector2f){direction.x /= longu, direction.y /= longu};
    game->plane[i].pos.x += direction.x * distance;
    game->plane[i].pos.y += direction.y * distance;
    sfSprite_setPosition(game->plane[i].sprite, game->plane[i].pos);
    sfRectangleShape_setPosition(game->plane[i].hitbox.rect, game->plane[i].
    pos);
    if (myabs(game->plane[i].pos.x - game->plane[i].posfin.x) < 1.0f &&
        myabs(game->plane[i].pos.y - game->plane[i].posfin.y) < 1.0f)
        game->plane[i].actif = 0;
    sfClock_restart(game->plane[i].clock);
    return 0;
}

static void display_hitplane(struct game *game, int i)
{
    if (game->hit == 1)
        sfRenderWindow_drawRectangleShape(game->window, game->plane
        [i].hitbox.rect, NULL);
}

static void display_plane(struct game *game)
{
    for (int i = 0; i < game->nbr_plane; i++) {
        if (calculate_traj(game, i) == 0 && game->plane[i].actif == 1) {
            sfRenderWindow_drawSprite(game->window, game->plane[i].sprite,
            NULL);
            display_hitplane(game, i);
        }
    }
}

static void display_tower(struct game *game)
{
    for (int i = 0; i < game->nbr_tower; i++) {
        if (game->hit == 1)
            sfRenderWindow_drawCircleShape(game->window, game->tower[i].
            hitbox.circle, NULL);
        sfRenderWindow_drawSprite(game->window, game->tower[i].sprite, NULL);
    }
}

void display(struct game *game)
{
    sfRenderWindow_drawSprite(game->window, game->background.sprite, NULL);
    display_tower(game);
    display_plane(game);
    sfRenderWindow_display(game->window);
}
