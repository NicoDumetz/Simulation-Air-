/*
** EPITECH PROJECT, 2023
** display all
** File description:
** display
*/

#include "../include/my_radar.h"

static void check_destroy(struct game *game, int i, float longu)
{
    if (longu < 5) {
        game->plane[i].actif = 0;
        game->plane[i].delay = 0;
    }
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
    check_destroy(game, i, longu);
    sfClock_restart(game->plane[i].clock);
    return 0;
}

static void display_hitplane(struct game *game, int i)
{
    if (game->spr == 1)
        sfRenderWindow_drawSprite(game->window, game->plane[i].sprite,
        NULL);
    if (game->hit == 1)
        sfRenderWindow_drawRectangleShape(game->window, game->plane
        [i].hitbox.rect, NULL);
}

static void display_plane(struct game *game)
{
    for (int i = 0; i < game->nbr_plane; i++) {
        if (game->plane[i].actif == 1 && calculate_traj(game, i) == 0) {
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
        if (game->spr == 1)
            sfRenderWindow_drawSprite(game->window, game->tower[i].sprite,
            NULL);
    }
}

static void display_time(struct game *game)
{
    sfTime elapsed = sfClock_getElapsedTime(game->clock);
    float val = sfTime_asSeconds(elapsed);
    char buffer[100];
    int min = (int)(val / 60);
    int sec = (int)(val) % 60;

    buffer[0] = '\0';
    my_strcat(buffer, "Time ");
    my_strcat(buffer, int_to_str(min));
    my_strcat(buffer, ":");
    my_strcat(buffer, int_to_str(sec));
    sfText_setString(game->time, buffer);
    sfRenderWindow_drawText(game->window, game->time, NULL);
}

void display(struct game *game)
{
    sfRenderWindow_drawSprite(game->window, game->background.sprite, NULL);
    display_tower(game);
    display_plane(game);
    display_time(game);
    sfRenderWindow_drawText(game->window, game->onspr, NULL);
    sfRenderWindow_drawText(game->window, game->onhit, NULL);
    sfRenderWindow_display(game->window);
}
