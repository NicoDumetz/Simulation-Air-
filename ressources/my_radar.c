/*
** EPITECH PROJECT, 2023
** my radar project
** File description:
** my radar
*/

#include "../include/my_radar.h"

void pop_event(struct game *game)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(game->window, &event)) {
        if (event.type == sfEvtClosed || (event.type == sfEvtKeyPressed &&
        event.key.code == sfKeyEscape))
            sfRenderWindow_close(game->window);
        if (event.type == sfEvtKeyPressed && event.key.code == sfKeyL)
            game->hit = game->hit == 1 ? 0 : 1;
            if (game->hit == 1)
                sfText_setString(game->onhit, "Hitboxes: ON");
            else
                sfText_setString(game->onhit, "Hitboxes: OFF");
        if (event.type == sfEvtKeyPressed && event.key.code == sfKeyS)
            game->spr = game->spr == 1 ? 0 : 1;
            if (game->spr == 1)
                sfText_setString(game->onspr, "Sprite: ON");
            else
                sfText_setString(game->onspr, "Sprite: OFF");
    }
}

static void check_delay(struct game *game)
{
    sfTime elapsed = sfClock_getElapsedTime(game->clock);
    float seconds = sfTime_asSeconds(elapsed);
    int end = 1;

    for (int i = 0; i < game->nbr_plane; i++) {
        if (game->plane[i].actif == 0 && game->plane[i].delay > 0 &&
            game->plane[i].delay < (int)seconds) {
            game->plane[i].actif = 1;
            sfClock_restart(game->plane[i].clock);
        }
        if (game->plane[i].actif == 1 || game->plane[i].delay > 0)
            end = 0;
        game->plane[i].tower_check = 0;
    }
    if (end == 1)
        sfRenderWindow_close(game->window);
}

static void game_loop(struct game *game)
{
    while (sfRenderWindow_isOpen(game->window)) {
        pop_event(game);
        check_delay(game);
        check_tower_col(game);
        check_colision_plane(game);
        sfRenderWindow_clear(game->window, sfBlack);
        display(game);
    }
}

void cleanup_game(struct game *g)
{
    sfTexture_destroy(g->background.texture);
    sfSprite_destroy(g->background.sprite);
    for (int i = 0; i < g->nbr_tower; i++) {
        sfSprite_destroy(g->tower[i].sprite);
        sfCircleShape_destroy(g->tower[i].hitbox.circle);
    }
    free(g->tower);
    for (int i = 0; i < g->nbr_plane; i++) {
        sfSprite_destroy(g->plane[i].sprite);
        sfClock_destroy(g->plane[i].clock);
        sfRectangleShape_destroy(g->plane[i].hitbox.rect);
    }
    free(g->plane);
    sfText_destroy(g->time);
    sfText_destroy(g->onspr);
    sfText_destroy(g->onhit);
    sfRenderWindow_destroy(g->window);
    sfClock_destroy(g->clock);
}

int my_radar(char **settings)
{
    struct game game = set_game(settings);

    sfRenderWindow_setFramerateLimit(game.window, 60);
    game_loop(&game);
    cleanup_game(&game);
    return 0;
}
