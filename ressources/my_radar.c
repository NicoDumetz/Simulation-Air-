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
        if (event.type == sfEvtKeyPressed && event.key.code == sfKeyS)
            game->spr = game->spr == 1 ? 0 : 1;
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

int my_radar(char **settings)
{
    struct game game = set_game(settings);

    sfRenderWindow_setFramerateLimit(game.window, 60);
    game_loop(&game);
    sfRenderWindow_destroy(game.window);
    return 0;
}
